int	main(int argc, char **argv)
{
	// AF_INET <=> IPv4 -- SOCK_STREAM <=> TCP
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	fcntl(server_fd, F_SETFL, O_NONBLOCK); // make the fd non blocking
	
	sockaddr_in addr; // struct to handle socket with IPv4
	addr.sin_family = AF_INET; // IPv4
	addr.sin_port = htons(port); // converts hostshort to network byte order (switch endians)
	addr.sin_addr.s_addr = INADDR_ANY; // listen to any address

	memset(&addr, 0, sizeof(addr));
	bind(server_fd, (sockaddr*)&addr, sizeof(addr));
	
	listen(server_fd, SOMAXCONN);
	
	std::vector<pollfd> fds;
	pollfd server_poll;
	server_poll.fd = server_fd;
	server_poll.events = POLLIN;
	server_poll.revents = 0;

	fds.push_back(server_poll);
	
	while (true)
	{
		int ret = poll(&fds[0], fds.size(), -1);
		if (ret < 0)
		continue; // handle error properly
		
		for (size_t i = 0; i < fds.size(); ++i)
		{
			if (fds[i].revents & POLLIN)
			{
				if (fds[i].fd == server_fd)
					handleNewConnection();
				else
					handleClientRead(fds[i].fd);
			}

			if (fds[i].revents & POLLOUT)
			{
				handleClientWrite(fds[i].fd);
			}
		}
	}
}
