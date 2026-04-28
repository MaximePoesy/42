#include <cstring>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <fcntl.h>
#include <poll.h>
#include <netinet/in.h>

std::map<int, std::string> client_buffers;

void handleClientRead(int client_fd)
{
    char buf[1024];
    ssize_t bytes = recv(client_fd, buf, sizeof(buf), 0);

    if (bytes <= 0)
    	return;

    client_buffers[client_fd].append(buf, bytes);

    // check if we have a complete message yet ( need \r\n )
    std::string& data = client_buffers[client_fd];
    size_t pos;
    while ((pos = data.find("\r\n")) != std::string::npos)
    {
        std::string message = data.substr(0, pos);
        data.erase(0, pos + 2);
        //processMessage(client_fd, message); // <<-------
    }
}


void handleNewConnection(int server_fd, std::vector<pollfd>& fds)
{
    sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    int client_fd = accept(server_fd, (sockaddr*)&client_addr, &client_len);
    if (client_fd < 0)
    {
        perror("accept");
        return;
    }

    // Make the new client fd non-blocking too
    if (fcntl(client_fd, F_SETFL, O_NONBLOCK) < 0)
        perror("fcntl");

    // Add to poll watchlist
    pollfd client_poll;
    client_poll.fd = client_fd;
    client_poll.events = POLLIN;  // start by just listening to the fd
    client_poll.revents = 0;
    fds.push_back(client_poll);

    std::cout << "New client connected: fd=" << client_fd << std::endl;
}

void handleClientWrite(int client_fd, std::vector<pollfd>& fds)
{
	const std::string& str = "yooooo\n";
	ssize_t sent = send(client_fd, &str, str.size(), 0);
}

int	main(int argc, char **argv)
{
	int port = 8080;
	// AF_INET <=> IPv4 -- SOCK_STREAM <=> TCP
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
		perror("socket");
		std::cout << "server_fd : " << server_fd << std::endl;
	if (fcntl(server_fd, F_SETFL, O_NONBLOCK) < 0) // make the fd non blocking
    		perror("fcntl");
	
	sockaddr_in addr; // struct to handle socket with IPv4
	memset(&addr, 0, sizeof(addr)); // zero out padding bytes to avoid garbage
	addr.sin_family = AF_INET; // IPv4
	addr.sin_port = htons(port); // converts hostshort to network byte order (switch endians)
	addr.sin_addr.s_addr = INADDR_ANY; // listen to any address
	if (bind(server_fd, (sockaddr*)&addr, sizeof(addr)) < 0) // bind socket to address/port
    		perror("bind");
	
	if (listen(server_fd, SOMAXCONN) < 0) // mark socket as passive, SOMAXCONN = max pending connections
    		perror("listen");
	
	std::vector<pollfd> fds; // poll watches multiple fds at once
	pollfd server_poll;
	server_poll.fd = server_fd;
	server_poll.events = POLLIN; // notify when data is ready to read
	server_poll.revents = 0; // kernel writes here what actually happened
	fds.push_back(server_poll);
	
	while (true)
	{
		int ret = poll(&fds[0], fds.size(), -1); // blocks until any fd is ready, -1 = no timeout
		if (ret < 0)
			continue; // TODO : handle error properly
		
		for (size_t i = 0; i < fds.size(); ++i)
		{
			if (fds[i].revents & POLLIN) // fd has incoming data
			{
				if (fds[i].fd == server_fd)
					handleNewConnection(server_fd, fds); // new client trying to connect
				else
					handleClientRead(fds[i].fd); // TODO : existing client sent data
			}
			if (fds[i].revents & POLLOUT) // fd is ready to receive the data without blocking
			{
				handleClientWrite(fds[i].fd, fds); // TODO: finish it
			}
		}
	}
}
