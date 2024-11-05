#include "../include/TestTable.h"
#include <iostream>

TestTable* TestTable::instance = nullptr;

TestTable& TestTable::GetInstance()
{
    if(instance == nullptr)
        instance = new TestTable();
    return *instance;
}

std::vector<TestTableEntry> TestTable::Select()
{
    std::vector<TestTableEntry> entries;
    std::string query;
    query = "SELECT * FROM " + table_name  + ";";
    res = ExecuteSelectQuery(query);
    if(res == NULL)
        return entries;

    while ((row = mysql_fetch_row(res))) 
    {
        entries.push_back(TestTableEntry(row[1], atoi(row[2]), atoll(row[0])));
    }
    return entries;
}

bool TestTable::Insert(TestTableEntry& entity)
{
    std::string query = InsertQuery();
    query += "(" + StringToDb(entity.name) + ", " + std::to_string(entity.age) + ");";
    std::cout << query << '\n';
    bool result = ExecuteQuery(query);
    if(result == true)
        entity.id = mysql_insert_id(conn);
    return result;
}