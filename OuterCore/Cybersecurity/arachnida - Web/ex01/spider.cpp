#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <curl/curl.h>
#include <set>
#include <libxml/HTMLparser.h>
#include <sys/stat.h>
#include <filesystem>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <cctype>

static char errorBuffer[CURL_ERROR_SIZE];
static std::string buffer;
static std::string url;
std::set<std::string> urls; //urls of the images

struct Options
{
    bool recursive;
    int maxDepth;
    std::string path;
    std::string url;

    Options()
        : recursive(false), maxDepth(5), path("./data/")
    {}
};

//
// libcurl write callback function
//
static size_t writer(char *data, size_t size, size_t nmemb,
                     std::string *writerData)
{
  if(!writerData)
    return 0;
 
  writerData->append(data, size * nmemb);
 
  return size * nmemb;
}

//
// libcurl connection initialization
//
static bool init(CURL *&curl, const char *url)
{
  CURLcode result;
 
  curl = curl_easy_init();
 
  if(!curl) {
    fprintf(stderr, "Failed to create CURL handle\n");
    return false;
  }
 
  result = curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
  if(result != CURLE_OK) {
    fprintf(stderr, "Failed to set error buffer [%d]\n", result);
    return false;
  }
 
  result = curl_easy_setopt(curl, CURLOPT_URL, url);
  if(result != CURLE_OK) {
    fprintf(stderr, "Failed to set URL [%s]\n", errorBuffer);
    return false;
  }
 
  result = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
  if(result != CURLE_OK) {
    fprintf(stderr, "Failed to set redirect option [%s]\n", errorBuffer);
    return false;
  }
 
  result = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
  if(result != CURLE_OK) {
    fprintf(stderr, "Failed to set writer [%s]\n", errorBuffer);
    return false;
  }
 
  result = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
  if(result != CURLE_OK) {
    fprintf(stderr, "Failed to set write data [%s]\n", errorBuffer);
    return false;
  }
 
  // define descriptive User Agent (otherwise Wikipedia doesnt give page)
  curl_easy_setopt(curl, CURLOPT_USERAGENT, "spider/1.0 42 school");
  
  return true;
}

int IsGoodExtension(const std::string &url)
{
    std::string::size_type dot = url.rfind('.');
    if (dot == std::string::npos)
        return 0;

    std::string end = url.substr(dot);  // from the dot to the end
    std::string::size_type ext = end.find_first_of("#?");
    if (ext != std::string::npos)
    	end = end.substr(0, ext);
    std::transform(end.begin(), end.end(), end.begin(), [](unsigned char c)
    {
    	return std::tolower(c);
    });
    if (end == ".jpg" || end == ".jpeg" || end == ".png"
                      || end == ".gif" || end == ".bmp")
        return 1;
    return 0;
}

static size_t writeFile(void *ptr, size_t size, size_t nmemb, void *stream)
{
    return fwrite(ptr, size, nmemb, (FILE *)stream);
}

bool downloadImage(const std::string &url)
{
    CURL *curl = curl_easy_init();
    if (!curl)
        return false;

    static int counter = 0;

    std::string cleanUrl = url;

    auto pos = cleanUrl.find_first_of("?#");
    if (pos != std::string::npos)
        cleanUrl = cleanUrl.substr(0, pos);

    std::string filename =
        std::to_string(counter++) + "_" +
        std::filesystem::path(cleanUrl).filename().string();

    FILE *fp = fopen(filename.c_str(), "wb");
    if (!fp)
    {
        curl_easy_cleanup(curl);
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFile);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "spider/1.0 42 school");

    CURLcode res = curl_easy_perform(curl);

    fclose(fp);
    curl_easy_cleanup(curl);

    return res == CURLE_OK;
}

static void parseImage(xmlChar* src)
{
	CURLU *h = curl_url();
	curl_url_set(h, CURLUPART_URL, url.c_str(), 0);           // seed with the PAGE url (the base)
	CURLUcode rc = curl_url_set(h, CURLUPART_URL, (const char*)src, 0);  // set the raw src as a relative ref
	if (rc == CURLUE_OK)
	{
		char *absolute = NULL;
		curl_url_get(h, CURLUPART_URL, &absolute, 0);         // read back the resolved absolute URL
		std::cout << absolute << std::endl;
		if (IsGoodExtension(absolute))
			urls.insert(absolute);
		curl_free(absolute);
	}
	curl_url_cleanup(h);
}

static void walk(_xmlNode *root)
{
    for(_xmlNode *node = root; node != NULL; node = node->next)
    {
        std::cout << "node: " << node->name << std::endl;

        if (node->type == XML_ELEMENT_NODE)
        {
            if (xmlStrcmp(node->name, (const xmlChar*)"img") == 0)
            {
                std::cout << "FOUND IMG" << std::endl;

                xmlChar *src = xmlGetProp(node, (const xmlChar*)"src");
                if (src)
                {
                    parseImage(src);
                    xmlFree(src);
                }
            }
        }

        if (node->children)
            walk(node->children);
    }
}
static void parseHtml(const std::string &html)
{
	/*
	std::string::size_type n;
	
	n = html.find("img");
	if (n == std::string::npos) {
        	std::cout << "no image" << std::endl;
        	return;
        }
	std::cout << "n is : " << n << std::endl;
	*/
	htmlDocPtr docptr;
	docptr =  htmlReadMemory(html.c_str(), html.size(),
				url.c_str(), NULL,
				HTML_PARSE_RECOVER | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
	if (!docptr) {
		// parse failed
		return;
	}
	walk(xmlDocGetRootElement(docptr));
	for (std::set<std::string>::const_iterator it = urls.begin(); it != urls.end(); ++it)
	{
		if (!downloadImage(*it))
        		std::cerr << "FAILED: " << *it << std::endl;
    		else
        		std::cout << "DOWNLOADED: " << *it << std::endl;
	}
	xmlFreeDoc(docptr);
}

bool parseArgs(int argc, char **argv, Options &opt)
{
    for (int i = 1; i < argc; ++i)
    {
        std::string arg(argv[i]);

        if (arg == "-r")
            opt.recursive = true;

        else if (arg == "-l")
        {
            if (++i >= argc)
                return false;
            opt.maxDepth = atoi(argv[i]);
        }

        else if (arg == "-p")
        {
            if (++i >= argc)
                return false;
            opt.path = argv[i];
        }

        else
        {
            // Assume the remaining non-option is the URL
            opt.url = arg;
        }
    }

    return !opt.url.empty();
}

int main(int argc, char *argv[])
{
	CURL *curl = NULL;
	CURLcode result;
	
	Options opt;

	if (!parseArgs(argc, argv, opt))
	{
	    std::cerr << "Usage: ./spider [-r] [-l N] [-p PATH] <url>\n";
	    return 1;
	}

	result = curl_global_init(CURL_GLOBAL_ALL);
	if(result != CURLE_OK)
		return (int)result;
		
	// Initialize CURL handle
	
	if(!init(curl, opt.url.c_str()))
	{
		fprintf(stderr, "Handle initialization failed\n");
		curl_global_cleanup();
		return EXIT_FAILURE;
	}
	
	url = opt.url;
	// Retrieve content for the URL
	buffer.clear();
	result = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	
	if(result != CURLE_OK)
	{
		fprintf(stderr, "Failed to get '%s' [%s]\n", argv[1], errorBuffer);
		return EXIT_FAILURE;
	}
	
	//std::cout << buffer.substr(0, 1000) << std::endl;
	// Parse the HTML code
	
	std::filesystem::path path = std::filesystem::current_path();
	//std::cout << "path : " << path.c_str() << std::endl;
	
	std::error_code ec;

	std::filesystem::create_directories(opt.path, ec);
	if (ec)
	{
		std::cerr << "Cannot create directory: " << ec.message() << std::endl;
		return 1;
	}
	
	std::filesystem::current_path(path / opt.path);
	//std::cout << "path : " << std::filesystem::current_path().c_str() << std::endl;
	parseHtml(buffer);
	return (int)result;
}
