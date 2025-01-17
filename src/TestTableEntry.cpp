#include "../include/TestTableEntry.h"
#include "../include/TestTable.h"
#include <vector>

TestTableEntry::TestTableEntry(std::string name, int age, uint64_t id) 
    : Entity(id), name {name}, age {age} { }

TestTableEntry::TestTableEntry(const TestTableEntry& other)
    : Entity(other.id), name {other.name}, age {other.age} { }

TestTableEntry& TestTableEntry::operator=(const TestTableEntry& other)
{
    TestTableEntry temp = other;
    std::swap(*this, temp);
    return *this;
}

void TestTableEntry::Print(std::ostream& os) const
{
    const std::vector<std::string>& columnNames =  TestTable::GetInstance().GetColumnNames();
    os << columnNames[0] << ": " << id << '\n';
    os << columnNames[1] << ": " << name << '\n';
    os << columnNames[2] << ": " << age << '\n';
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