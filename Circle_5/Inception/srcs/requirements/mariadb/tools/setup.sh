#!/bin/bash
#
echo "Starting database config..."

mysqld_safe & 
until mysqladmin ping \
	-u root \
	--silent; do
	echo "waiting for MariaDB..."
	sleep 2
done
echo "Starting..."
env -u MYSQL_HOST mysql -u root -h localhost << EOF
CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`;
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';
ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}' WITH GRANT OPTION;
FLUSH PRIVILEGES;
EOF

echo "Database setup finished!"
#service mariadb stop

wait
