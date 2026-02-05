FROM debian:bookworm

# non interatcive because automated
ENV DEBIAN_FRONTEND=noninteractive

# installs mariadb and cleans cache (reduces image size)
RUN apt-get update && apt-get install -y mariadb-server && apt-get clean && rm -rf /var/lib/apt/lists/*

COPY conf/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf
COPY tools/setup.sh /usr/local/bin/setup.sh
ENTRYPOINT ["/usr/local/bin/setup.sh"]
RUN chmod +x /usr/local/bin/setup.sh

EXPOSE 3306 

#CMD ["mysqld_safe"]
