1. Introduction

This documentation provides end users with the necessary information to use and manage the services provided by the project.
The project consists of several Docker containers running services like NGINX,
WordPress, and MariaDB, which are configured to work together within a Docker network.

2. Services Provided

NGINX: Acts as the reverse proxy and entry point to your infrastructure, handling all HTTPS requests with TLSv1.2 or TLSv1.3.

WordPress: The content management system (CMS) for your website, powered by PHP-FPM.

MariaDB: The database server that stores the content for the WordPress site.

3. Starting the Project
Requirements

A machine with Docker and Docker Compose installed.

A domain name pointing to your local IP (e.g., [yourlogin].42.fr).

4. Step-by-step guide

Clone the repository to your local machine.

git clone [repository_url]

Build the Docker Images:

Navigate to the project folder and build the Docker images with the following command:

make

After starting the containers, your WordPress site will be available at:

https://[yourlogin].42.fr

The WordPress admin panel can be accessed at:

https://[yourlogin].42.fr/wp-admin

Use the administrator username and password provided in the .env file to log in.

To stop all services and containers, you can use the following command:

make clean OR make fclean

5. Managing Credentials

The credentials for the database and the WordPress admin account are stored in environment variables.
They must be set up in the .env file before running the containers.
These credentials are not stored in the Dockerfiles for security reasons.

--- Accessing the .env file ---

The .env file contains environment variables like:

MYSQL_USER: The WordPress database user.
MYSQL_PASSWORD: The password for the database user.
DOMAIN_NAME: The domain name for the site (e.g., [yourlogin].42.fr).

Make sure the .env file is correctly configured before starting the containers.

6. Checking the Status of Services

To check the status of all the containers, you can run inside /srcs/ :

docker-compose ps

This will show whether the containers are running and if any errors are occurring.

7. Troubleshooting

Website not loading:
Make sure the containers are running (docker-compose ps), and ensure your domain points to your IP address.

Admin login fails:
Ensure the credentials in the .env file are correct. If the database container isn't running, try restarting the containers with:

make re

8. Updating the Project

To pull the latest updates from the repository:

git pull origin main

After pulling, run "make re" to rebuild the images and restart the containers.
