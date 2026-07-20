#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <curl/curl.h>
#include <libxml/HTMLparser.h>
#include <filesystem>
#include <algorithm>
#include <cctype>
#include <utility>

//
// Program options
//
struct Options
{
	bool recursive;
	int maxDepth;
	std::string path;
	std::string url;

	Options() : recursive(false), maxDepth(5), path("./data/")
	{
	}
};

//
// Pages already visited (normalized URLs)
//
std::set<std::string> visitedPages;

//
// Images already attempted, successfully or not, so we never try twice
//
std::set<std::string> processedImages;

//
// libcurl callback for HTML downloads
//
static size_t writer(char *data, size_t size, size_t nmemb, std::string *output)
{
	if (!output)
	    return 0;

	output->append(data, size * nmemb);

	return size * nmemb;
}

//
// libcurl callback for binary image downloads
//
static size_t writeFile(char *data, size_t size, size_t nmemb, void *stream)
{
	return fwrite(data, size, nmemb, (FILE *)stream);
}

//
// Remove the fragment so "page" and "page#section" count as one page
//
std::string normalizeUrl(const std::string &url)
{
	std::string::size_type pos = url.find('#');

	if (pos != std::string::npos)
	    return url.substr(0, pos);

	return url;
}

//
// Check image extension
//
bool IsGoodExtension(const std::string &url)
{
	std::string clean = url;

	// Remove query and fragment
	std::string::size_type pos = clean.find_first_of("?#");

	if (pos != std::string::npos)
	    clean = clean.substr(0, pos);

	std::string::size_type dot = clean.rfind('.');

	if (dot == std::string::npos)
	    return false;

	std::string ext = clean.substr(dot);

	std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c)
	{
	    return std::tolower(c);
	});

	return ext == ".jpg" || ext == ".jpeg" || ext == ".png" || ext == ".gif" || ext == ".bmp";
}

//
// Check if two URLs belong to the same website
//
bool SameDomain(const std::string &a, const std::string &b)
{
	CURLU *first = curl_url();

	if (!first)
	    return false;

	CURLU *second = curl_url();

	if (!second)
	{
	    curl_url_cleanup(first);
	    return false;
	}

	curl_url_set(first, CURLUPART_URL, a.c_str(), 0);

	curl_url_set(second, CURLUPART_URL, b.c_str(), 0);

	char *host1 = NULL;
	char *host2 = NULL;

	CURLUcode r1 = curl_url_get(first, CURLUPART_HOST, &host1, 0);

	CURLUcode r2 = curl_url_get(second, CURLUPART_HOST, &host2, 0);

	bool result = false;

	if (r1 == CURLUE_OK && r2 == CURLUE_OK && host1 && host2)
	{
	    result = std::string(host1) == std::string(host2);
	}

	if (host1)
	    curl_free(host1);

	if (host2)
	    curl_free(host2);

	curl_url_cleanup(first);
	curl_url_cleanup(second);

	return result;
}

//
// Download one HTML page
//
bool fetchPage(const std::string &pageUrl, std::string &html, std::string &finalUrl)
{
	CURL *curl = curl_easy_init();

	if (!curl)
	    return false;

	// If no redirect happens, the final URL is the requested one
	finalUrl = pageUrl;

	char errorBuffer[CURL_ERROR_SIZE];
	errorBuffer[0] = '\0';

	html.clear();

	curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
	curl_easy_setopt(curl, CURLOPT_URL, pageUrl.c_str());
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "spider/1.0 42 school");
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);

	CURLcode result = curl_easy_perform(curl);

	if (result != CURLE_OK)
	{
	    std::cerr << "    error: " << (errorBuffer[0] ? errorBuffer : curl_easy_strerror(result)) << std::endl;

	    curl_easy_cleanup(curl);
	    return false;
	}

	long response = 0;

	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response);

	if (response != 200)
	{
	    std::cerr << "    error: HTTP " << response << std::endl;

	    curl_easy_cleanup(curl);
	    return false;
	}

	//
	// A link may point to a PDF or an archive.
	// Only hand real HTML to the parser.
	//
	char *contentType = NULL;

	curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &contentType);

	bool isHtml = true;

	if (contentType != NULL)
	{
	    std::string type(contentType);

	    isHtml = type.find("text/html") != std::string::npos ||
	             type.find("application/xhtml") != std::string::npos;
	}

	//
	// Redirects mean the HTML may come from another URL.
	// Relative links must be resolved against that one.
	// Both pointers below belong to the handle, so copy
	// what we need BEFORE curl_easy_cleanup().
	//
	char *effective = NULL;

	curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &effective);

	if (effective != NULL)
	    finalUrl = effective;

	curl_easy_cleanup(curl);

	return isHtml;
}

//
// Download image file
//
bool downloadImage(const std::string &imageUrl, const Options &opt)
{
	static int counter = 0;

	CURL *curl = curl_easy_init();

	if (!curl)
	    return false;

	std::string cleanUrl = imageUrl;

	std::string::size_type pos = cleanUrl.find_first_of("?#");

	if (pos != std::string::npos)
	    cleanUrl = cleanUrl.substr(0, pos);

	std::string base = std::filesystem::path(cleanUrl) .filename() .string();

	if (base.empty())
	    base = "image";

	std::string filename = std::to_string(counter++) + "_" + base;

	std::filesystem::path output = std::filesystem::path(opt.path) / filename;

	FILE *file = fopen(output.string().c_str(), "wb");

	if (!file)
	{
	    curl_easy_cleanup(curl);
	    return false;
	}

	curl_easy_setopt(curl, CURLOPT_URL, imageUrl.c_str());
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFile);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "spider/1.0 42 school");
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60L);

	CURLcode result = curl_easy_perform(curl);

	long response = 0;

	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response);

	fclose(file);

	bool success = result == CURLE_OK && response == 200;

	// Don't leave empty/broken files behind.
	if (!success)
	{
	    std::remove(output.string().c_str());
	}

	curl_easy_cleanup(curl);

	return success;
}

//
// Resolve a relative URL against a page URL
//
bool resolveURL(const std::string &base, const std::string &relative, std::string &absolute)
{
	CURLU *url = curl_url();

	if (!url)
	    return false;

	curl_url_set(url, CURLUPART_URL, base.c_str(), 0);

	CURLUcode result = curl_url_set(url, CURLUPART_URL, relative.c_str(), 0);

	if (result != CURLUE_OK)
	{
	    curl_url_cleanup(url);
	    return false;
	}

	char *temp = NULL;

	result = curl_url_get(url, CURLUPART_URL, &temp, 0);

	if (result != CURLUE_OK || !temp)
	{
	    curl_url_cleanup(url);
	    return false;
	}

	absolute = temp;

	curl_free(temp);
	curl_url_cleanup(url);

	return true;
}

//
// Parse an image URL
//
void parseImage(const std::string &pageUrl, xmlChar *src, std::vector<std::string> &images)
{
	std::string absolute;

	if (!resolveURL(pageUrl, (const char *)src, absolute))
	{
	    return;
	}

	if (IsGoodExtension(absolute))
	{
	    images.push_back(absolute);
	}
}

//
// Parse a link to another page
//
void parseLink(const std::string &pageUrl, xmlChar *href, std::vector<std::string> &links)
{
	std::string absolute;

	if (!resolveURL(pageUrl, (const char *)href, absolute))
	{
	    return;
	}

	if (SameDomain(pageUrl, absolute))
	{
	    links.push_back(absolute);
	}
}

//
// Walk HTML tree and collect images and links
//
void walk(_xmlNode *root, const std::string &pageUrl, std::vector<std::string> &images, std::vector<std::string> &links)
{
	for (_xmlNode *node = root; node != NULL; node = node->next)
	{
	    if (node->type == XML_ELEMENT_NODE)
	    {
	        //
	        // Images
	        //
	        if (xmlStrcmp(node->name, (const xmlChar *)"img") == 0)
	        {
	            xmlChar *src = xmlGetProp(node, (const xmlChar *)"src");

	            if (src)
	            {
	                parseImage(pageUrl, src, images);

	                xmlFree(src);
	            }
	        }

	        //
	        // Links
	        //
	        if (xmlStrcmp(node->name, (const xmlChar *)"a") == 0)
	        {
	            xmlChar *href = xmlGetProp(node, (const xmlChar *)"href");

	            if (href)
	            {
	                parseLink(pageUrl, href, links);

	                xmlFree(href);
	            }
	        }
	    }

	    if (node->children)
	    {
	        walk(node->children, pageUrl, images, links);
	    }
	}
}

//
// Parse one HTML page
//
void parseHtml(const std::string &pageUrl, const std::string &html, std::vector<std::string> &images, std::vector<std::string> &links)
{
	htmlDocPtr doc = htmlReadMemory(html.c_str(), html.size(), pageUrl.c_str(), NULL, HTML_PARSE_RECOVER | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);

	if (!doc)
	    return;

	walk(xmlDocGetRootElement(doc), pageUrl, images, links);

	xmlFreeDoc(doc);
}

//
// Crawl website
//
void crawl(const std::string &startUrl, const Options &opt)
{
	std::queue< std::pair<std::string, int> > frontier;

	frontier.push( std::make_pair(normalizeUrl(startUrl), 0) );

	while (!frontier.empty())
	{
	    std::string current = frontier.front().first;

	    int depth = frontier.front().second;

	    frontier.pop();

	    if (visitedPages.count(current))
	        continue;

	    visitedPages.insert(current);

	    std::cout << "[depth " << depth << "] " << current << std::endl;

	    std::string html;
	    std::string finalUrl;

	    if (!fetchPage(current, html, finalUrl))
	    {
	        continue;
	    }

	    //
	    // Remember the redirect target too, so we don't
	    // fetch the same page again under its other name
	    //
	    std::string resolved = normalizeUrl(finalUrl);

	    if (resolved != current)
	        visitedPages.insert(resolved);

	    std::vector<std::string> images;
	    std::vector<std::string> links;

	    parseHtml(resolved, html, images, links);

	    //
	    // Download images found on this page
	    //
	    for (size_t i = 0; i < images.size(); i++)
	    {
	        if (processedImages.count(images[i]))
	            continue;

	        //
	        // Mark before trying, so a broken image
	        // is not retried on every following page
	        //
	        processedImages.insert(images[i]);

	        if (downloadImage(images[i], opt))
	        {
	            std::cout << "    saved  " << images[i] << std::endl;
	        }
	        else
	        {
	            std::cerr << "    failed " << images[i] << std::endl;
	        }
	    }

	    //
	    // Add next pages only when recursive mode is enabled
	    //
	    if (opt.recursive && depth < opt.maxDepth)
	    {
	        for (size_t i = 0; i < links.size(); i++)
	        {
	            std::string next = normalizeUrl(links[i]);

	            if (!visitedPages.count(next))
	            {
	                frontier.push( std::make_pair( next, depth + 1 ) );
	            }
	        }
	    }
	}
}

//
// Parse command line arguments
//
bool parseArgs(int argc, char **argv, Options &opt)
{
	bool depthGiven = false;

	for (int i = 1; i < argc; i++)
	{
	    std::string arg(argv[i]);

	    if (arg == "-r")
	    {
	        opt.recursive = true;
	    }
	    else if (arg == "-l")
	    {
	        depthGiven = true;
	        
	        if (i + 1 < argc)
	        {
	            std::string value(argv[i + 1]);
	            std::size_t consumed = 0;
	            int parsed = 0;
	            bool numeric = true;

	            try
	            {
	                parsed = std::stoi(value, &consumed);
	            }
	            catch (...)
	            {
	                numeric = false;
	            }

	            //
	            // stoi stops at the first non-digit, so "5abc" must
	            // not count as a number.
	            //
	            if (numeric && consumed == value.size())
	            {
	                if (parsed < 0)
	                {
	                    return false;
	                }

	                opt.maxDepth = parsed;
	                i++;
	            }
	        }
	    }
	    else if (arg == "-p")
	    {
	        i++;

	        if (i >= argc)
	        {
	            return false;
	        }

	        opt.path = argv[i];
	    }
	    else if (arg[0] == '-')
	    {
	        //
	        // Unknown option
	        //
	        return false;
	    }
	    else
	    {
	        //
	        // URL
	        //
	        if (!opt.url.empty())
	        {
	            //
	            // Two URLs given
	            //
	            return false;
	        }

	        opt.url = arg;
	    }
	}

	if (depthGiven && !opt.recursive)
	{
	    std::cerr << "spider: -l requires -r" << std::endl;
	    return false;
	}

	return !opt.url.empty();
}

int main(int argc, char **argv)
{
	Options opt;

	if (!parseArgs(argc, argv, opt))
	{
	    std::cerr << "Usage: ./spider [-r] [-l N] [-p PATH] URL" << std::endl;

	    return 1;
	}

	CURLcode result = curl_global_init(CURL_GLOBAL_ALL);

	if (result != CURLE_OK)
	{
	    return 1;
	}

	std::error_code ec;

	std::filesystem::create_directories( opt.path, ec );

	if (ec)
	{
	    std::cerr << "Cannot create directory: " << ec.message() << std::endl;

	    curl_global_cleanup();
	    return 1;
	}

	crawl(opt.url, opt);

	xmlCleanupParser();
	curl_global_cleanup();

	return 0;
}
