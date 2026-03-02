int	main(int argc, char **argv)
{
	// AF_INET <=> IPv4 -- SOCK_STREAM <=> TCP
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	fcntl(server_fd, F_SETFL, O_NONBLOCK); // make the fd non blocking
	
	sockaddr_in addr; // struct to handle socket with IPv4
	addr.sin_family = AF_INET; // IPv4
	addr.sin_port = htons(port); // converts hostshort to network byte order (switch endians)
	addr.sin_addr.s_addr = INADDR_ANY; // listen to any address
	memset(&addr, 0, sizeof(addr)); // zero out padding bytes to avoid garbage
	bind(server_fd, (sockaddr*)&addr, sizeof(addr)); // bind socket to address/port
	
	listen(server_fd, SOMAXCONN); // mark socket as passive, SOMAXCONN = max pending connections
	
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
					handleNewConnection(); // TODO : new client is knocking -- call accept()
				else
					handleClientRead(fds[i].fd); // TODO : existing client sent data
			}
			if (fds[i].revents & POLLOUT) // fd is ready to send data without blocking
			{
				handleClientWrite(fds[i].fd); //TODO
			}
		}
	}
}
