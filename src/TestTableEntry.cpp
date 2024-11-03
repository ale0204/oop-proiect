#include "../include/TestTableEntry.h"
#include "../include/TestTable.h"
#include <vector>

TestTableEntry::TestTableEntry(unsigned long long id, std::string name, int age) 
    : Entity(id), name {name}, age {age} { }
TestTableEntry::TestTableEntry(std::string name, int age, unsigned long long id) 
    : Entity(id), name {name}, age {age} { }

void TestTableEntry::Print(std::ostream& os) const
{
    const std::vector<std::string> column_names =  TestTable::GetInstance().GetColumnNames();
    os << column_names[0] << ": " << id << '\n';
    os << column_names[1] << ": " << name << '\n';
    os << column_names[2] << ": " << age << '\n';
}

std::ostream& operator<<(std::ostream& os, const TestTableEntry& entry)
{
    entry.Print(os);
    return os;
}
