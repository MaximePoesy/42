This project has been created as part of the 42 curriculum by mpoesy.

--- Inception Project ---

1. Description

This project aims to deepen knowledge in system administration, specifically with Docker.
It involves creating and managing Docker containers for various services like NGINX, WordPress, and MariaDB.
The objective is to set up a complete infrastructure in a virtual machine using Docker and Docker Compose.

2. Instructions

--- Prerequisites ---

Docker: Ensure Docker and Docker Compose are installed on your machine.
Domain Name Setup: Make sure your domain points to your local IP (e.g., [yourlogin].42.fr).

--- Setup & Execution ---

Clone this repository to your computer.
Navigate to the project folder.
Create your Docker images and start the containers by running the Makefile with:

make

--- Accessing the Website ---

After running the project, you can access the website at https://[yourlogin].42.fr.

--- Stopping the Project ---

To stop all services:

make clean

and remove the images:

make fclean

--- Managing Services ---

You can check the status of your services with:

docker-compose ps

3. Resources

Docker Documentation: https://docs.docker.com/
Docker Compose Documentation: https://docs.docker.com/compose/
Nginx: https://hub.docker.com/_/nginx
       https://nginx.org/en/docs/
Wordpress: https://github.com/docker/awesome-compose/tree/master/wordpress-mysql
	   https://www.digitalocean.com/community/tutorials/how-to-install-wordpress-with-docker-compose
MariaDB: https://hub.docker.com/_/mariadb
	 https://homelab-alpha.nl/docker/compose-info/mariadb/
Use of AI: AI tools were used to assist in generating Dockerfiles, Docker Compose configurations, and troubleshooting related issues.

4. Design Choices

--- Virtual Machines vs Docker ----

Docker allows lightweight, isolated environments with fewer system resources compared to traditional virtual machines.

--- Secrets vs Environment Variables ---

Sensitive information is managed through environment variables and Docker secrets for security.

--- Docker Network vs Host Network ---

A dedicated Docker network is used to isolate services and improve security, rather than using the host's network.

--- Docker Volumes vs Bind Mounts ---

Volumes are used to persist data for WordPress and MariaDB to ensure data is not lost when containers are restarted.
