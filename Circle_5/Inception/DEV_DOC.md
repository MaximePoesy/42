1. Introduction

This documentation provides developers with the necessary steps to set up and manage the environment from scratch,
build the project, and interact with the containers.

2. Setting Up the Environment

Clone the project repository to your local machine:

git clone <repository_url>


3. Install Prerequisites

Make sure Docker and Docker Compose are installed.
If not, run:

sudo apt-get update && sudo apt-get -y docker docker-compose

--- Building and Launching the Project ---

Run make to build the Docker images using:

make

4. Launch the Containers

Start the services using Docker Compose:

docker-compose up

This will start all the services (NGINX, WordPress, and MariaDB) and make the website accessible at https://[yourlogin].42.fr.

5. Managing Containers and Volumes

You can check the status of the containers with:

docker-compose ps

6. Stop the Containers

To stop the containers, run:

make clean
OR
make fclean

7. View Logs

To see the logs for a specific container ( inside /srcs/ ):

docker logs <container_name>
(nginx, wordpress or mariadb)

8. Data Persistence

--- Volumes ---

WordPress database and website files are stored in Docker named volumes.

The data is persisted in /home/[yourlogin]/data on the host machine.

--- Customizing the Configuration ---

a. Environment Variables

The .env file contains environment variables like MYSQL_USER, MYSQL_PASSWORD, and DOMAIN_NAME for configuring the services.

b. Docker Compose File

The docker-compose.yml file defines the services, networks, and volumes.
You can customize this file to modify configurations like ports or resource allocation.

10. Rebuild the Images

If you’ve made changes to the Dockerfiles, rebuild the images:

make re

11. Updating the Project

To update your local copy of the project:

git pull origin main

After pulling, rebuild the images with:

make re
