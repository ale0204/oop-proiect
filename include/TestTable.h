#ifndef TEST_TABLE_H_
#define TEST_TABLE_H_
#include "AbstractTable.h"
#include "TestTableEntry.h"

class TestTable : public AbstractTable {
private:
    static TestTable *instance;
    TestTable(std::string table_name = "test_table") : AbstractTable(table_name) {}
public:
    static TestTable& GetInstance();
    std::vector<TestTableEntry> Select();
    bool Insert(TestTableEntry& entity);
};

#endif /* TEST_TABLE_H_ */