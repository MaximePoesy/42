#!/bin/bash

mkdir -p /run/php

cd /var/www/html

while ! mysqladmin ping -h"mariadb" --silent; do
	echo "Waiting for MariaDB..."
	sleep 2
done

echo "MariaDB is ready!"

sleep 10

if [ ! -f wp-config.php ]; then
	wp core download --allow-root
	wp config create --dbname=${WORDPRESS_DB_NAME} --dbuser=${WORDPRESS_DB_USER} --dbpass=${WORDPRESS_DB_PASSWORD} --dbhost=${WORDPRESS_DB_HOST} --allow-root --skip-check --allow-root
	wp core install --url=https://${DOMAIN_NAME} --title=Inception --admin_user=${WP_ADMIN_USER} --admin_password=${WP_ADMIN_PASSWORD} --admin_email=${WP_ADMIN_EMAIL} --allow-root
	wp user create ${WP_USER} ${WP_USER_EMAIL} --role=author --user_pass=${WP_USER_PASSWORD} --allow-root
fi

chown -R www-data:www-data /var/www/html

exec php-fpm8.2 -F
