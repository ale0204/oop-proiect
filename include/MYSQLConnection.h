#ifndef MYSQL_CONNECTION_H_
#define MYSQL_CONNECTION_H_
#include <iostream>
#include <mysql.h>
class MySQLConnection {
private:
    std::string host;
    std::string user;
    std::string password;
    std::string db_name;
    unsigned short port;
    MYSQL *conn;
    static MySQLConnection *instance;
private:
    MySQLConnection(std::string host = "alexandra-neamtu.ro", std::string user = "alexandra",
                      std::string password = "alexandra", std::string db_name = "alexandra", unsigned int port = 3306);
public:
    static MySQLConnection& GetInstance();
public:
    MYSQL* GetConnection();
    std::string GetDbName();
    ~MySQLConnection();
};
#endif /* MYSQL_CONNECTION_H_ */