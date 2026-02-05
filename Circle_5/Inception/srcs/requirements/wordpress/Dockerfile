FROM debian:bookworm

# install PHP-FPM and PHP extensions
RUN apt-get update && apt-get install -y iputils-ping php8.2-fpm php8.2-mysql curl mariadb-client && rm -rf /var/lib/apt/lists/*

# install WP-CLI
RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && chmod +x wp-cli.phar && mv wp-cli.phar /usr/local/bin/wp

# copy conf files
COPY conf/www.conf /etc/php/8.2/fpm/pool.d/
COPY tools/setup.sh /setup.sh

RUN chmod +x /setup.sh

EXPOSE 9000

CMD ["/setup.sh"]
