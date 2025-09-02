#include "../include/MYSQLConnection.h"

MySQLConnection* MySQLConnection::instance = nullptr;

MySQLConnection::MySQLConnection(std::string host, std::string user,
                    std::string password, std::string dbName, unsigned short port)
    : host {host}, user {user}, password {password}, dbName {dbName}, port {port}
{
    conn = mysql_init(NULL);
    if (conn == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(EXIT_FAILURE);
    }
    if(mysql_real_connect(conn, host.c_str(), user.c_str(), password.c_str(), dbName.c_str(), port, NULL, 0) == NULL)
    {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }
}

 MySQLConnection& MySQLConnection::GetInstance()
{
    if(instance == nullptr)
        instance = new MySQLConnection();
    return *instance;
}

MYSQL* MySQLConnection::GetConnection()  { return conn; }
std::string MySQLConnection::GetDbName() { return dbName; }

MySQLConnection::~MySQLConnection() 
{
    mysql_close(conn);
}