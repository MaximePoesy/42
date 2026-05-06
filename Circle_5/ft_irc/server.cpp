#include <string.h>
#include <cstring>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <fcntl.h>
#include <poll.h>
#include <netinet/in.h>

int main()
{
	int max_conn = 10;
	std::string port = "8080";
	struct addrinfo hints, *res;
	
	hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;     // auto fill the host's IP.
	
	if (getaddrinfo(NULL, MYPORT, &hints, &res) < 0) // NULL because same IP.
		perror("getaddrinfo");
	
	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (fcntl(sockfd, F_SETFL, O_NONBLOCK) < 0) // make the fd non blocking
    		perror("fcntl");
	if (bind(sockfd, res->ai_addr, res->ai_addrlen) < 0)
		perror("bind");
	if (listen(sockfd, max_conn) < 0)
		perror("listen");
	
	std::vector<pollfd> incoming_fds;
	pollfd server_fd;
	server_fd.fd = server_fd;
	server_fd.events = POLLIN; // ok to read
	server_fd.revents = 0; // kernel writes here
	fds.push_back(server_fd);
	return 0;
}
