#include "../include/TestTable.h"
#include <algorithm>
int main() 
{   
    TestTable& testTable = TestTable::GetInstance();
    std::vector<TestTableEntry> entries = testTable.Select();

    std::for_each(entries.begin(), entries.end(), 
        [](const TestTableEntry& entry) {
            std::cout << entry << std::endl;
        }
    );
    
    TestTableEntry entry;
    std::cin >> entry;
    if(testTable.Insert(entry))
    {
        std::cout << "Inserted with id " << entry.GetID() << '\n';
    }

    std::cout << "Updated table:\n";
    std::for_each(entries.begin(), entries.end(), 
        [](const TestTableEntry& entry) {
            std::cout << entry << std::endl;
        }
    );
    return 0;
}