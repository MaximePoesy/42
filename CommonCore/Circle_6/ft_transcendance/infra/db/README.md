# Database CLI Access

To access the PostgreSQL database directly from your terminal, run the following command:

```bash
docker exec -it ft_db psql -U transcendance -d transcendance_db
```

Once connected, you can interact with the database using SQL queries. Here are some useful commands:
* `\dt` : List all tables in the database.
* `SELECT * FROM users;` : Display the contents of the users table.
* `SELECT * FROM auth_attempts;` : Display the connection attempts logs.
* `\q` : Quit the `psql` client.
