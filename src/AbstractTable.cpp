#include "../include/AbstractTable.h"
#include "../include/MYSQLConnection.h"

std::vector<std::string> AbstractTable::FetchColumnNames(int& numFields)
{
    MYSQL_RES *result;
    std::vector<std::string> cols;
    std::string query = "SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_SCHEMA = '" 
                        + MySQLConnection::GetInstance().GetDbName() + "' AND TABLE_NAME = '" + tableName + "' "
                        + "ORDER BY ORDINAL_POSITION;";
    result = ExecuteSelectQuery(query);
    if(result == NULL)
        return cols;
    numColumns = 0;
    while ((row = mysql_fetch_row(result))) {
        cols.push_back(row[0]);
        numColumns++;
    }
    printf("num_columns = %d\n", numColumns);
    numFields = numColumns;
    mysql_free_result(result);
    return cols;
}

AbstractTable::AbstractTable(std::string tableName) : res {NULL}, row {NULL}, tableName {tableName} 
{
    conn = MySQLConnection::GetInstance().GetConnection();
    columnNames = FetchColumnNames(numColumns);
}

std::string AbstractTable::StringToDb(std::string s)
{
    return "'" + s + "'";
}

std::string AbstractTable::InsertQuery()
{
    std::string query;
    query = "INSERT INTO " + tableName + "(";
    for(int i = 1; i < numColumns; i++)
    {
        query += columnNames[i];
        if(i != numColumns-1)
        {
            query += ", ";
        }
    }
    query += ") VALUES ";
    return query;
}

MYSQL_RES* AbstractTable::ExecuteSelectQuery(const std::string& query)
{
    MYSQL_RES *result = NULL;
    if (mysql_query(conn, query.c_str()) != 0) {
        fprintf(stderr, "query '%s' failed: %s\n", query.c_str(), mysql_error(conn));
        return NULL;
    }
    if ((result = mysql_store_result(conn)) == NULL) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(conn));
        return NULL;
    }
    return result;
}

bool AbstractTable::ExecuteQuery(std::string query)
{
    if (mysql_query(conn, query.c_str()) != 0) {
        fprintf(stderr, "query '%s' failed: %s\n", query.c_str(), mysql_error(conn));
        return false;
    }
    return true;
}

const std::vector<std::string>& AbstractTable::GetColumnNames() const
{
    return columnNames;
}