#include "../include/MYSQLConnection.h"

MySQLConnection* MySQLConnection::instance = nullptr;

MySQLConnection::MySQLConnection(std::string host, std::string user,
                    std::string password, std::string db_name, unsigned int port)
{
    this->host = host;
    this->user = user;
    this->password = password;
    this->db_name = db_name;
    this->port = port;
    conn = mysql_init(NULL);
    if (conn == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(EXIT_FAILURE);
    }
    if(mysql_real_connect(conn, host.c_str(), user.c_str(), password.c_str(), db_name.c_str(), port, NULL, 0) == NULL)
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
std::string MySQLConnection::GetDbName() { return db_name; }

MySQLConnection::~MySQLConnection() 
{
    mysql_close(conn);
}