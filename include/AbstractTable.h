#ifndef ABSTRACT_TABLE_H_
#define ABSTRACT_TABLE_H_

#include "Entity.h"
#include <mysql.h>
#include <string>
#include <vector>

class AbstractTable {
protected:
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int num_columns;
    std::string table_name;
    std::vector<std::string> column_names;
private:
    std::vector<std::string> FetchColumnNames(int& numFields);
protected:
    std::string StringToDb(std::string s);
public:
    AbstractTable(std::string table_name = "");
    std::string InsertQuery();
    MYSQL_RES* ExecuteSelectQuery(const std::string& query);
    bool ExecuteQuery(std::string query);
    const std::vector<std::string>& GetColumnNames() const;
    // virtual std::vector<Entity*> Select() = 0;
};

#endif /* ABSTRACT_TABLE_H_ */