#include "../include/TestTableEntry.h"
#include "../include/TestTable.h"
#include <vector>

TestTableEntry::TestTableEntry(std::string name, int age, unsigned long long id) 
    : Entity(id), name {name}, age {age} { }

void TestTableEntry::Print(std::ostream& os) const
{
    const std::vector<std::string> column_names =  TestTable::GetInstance().GetColumnNames();
    os << column_names[0] << ": " << id << '\n';
    os << column_names[1] << ": " << name << '\n';
    os << column_names[2] << ": " << age << '\n';
}

std::istream& operator>>(std::istream& is, TestTableEntry& entry)
{
    std::cout << "Add a new entry to the table\n";
    std::cout << "Name: ";
    is >> entry.name;
    std::cout << "Age: ";
    is >> entry.age;
    return is;
}