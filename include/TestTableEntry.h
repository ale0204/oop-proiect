#ifndef TEST_TABLE_ENTRY_H_
#define TEST_TABLE_ENTRY_H_
#include "Entity.h"
#include <iostream>

class TestTableEntry : public Entity {
private:
    std::string name;
    int age;
public:
    TestTableEntry(std::string name = "", int age = -1, uint64_t id = 0);
    TestTableEntry(const TestTableEntry& testTableEntry);
    TestTableEntry& operator=(const TestTableEntry& testTableEntry);
    virtual ~TestTableEntry() = default;
    void Print(std::ostream& os) const override;
    friend std::istream& operator>>(std::istream& is, TestTableEntry& entry);
    friend class TestTable;
};

#endif /* TEST_TABLE_ENTRY_H_ */
