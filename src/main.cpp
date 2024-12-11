#define SDL_MAIN_HANDLED
#include <algorithm>
#include <memory>
#include <vector>
#include "../include/TestTable.h"
#include "../include/CandyCrush/CandyCrush.h"
#include "../include/CandyCrush/Candy.h"

void Demo()
{
    std::vector<DemoCandy*> candies;
    int numCandies = static_cast<int>(CandyType::NUM_CANDIES);
    for(int i = 0; i < numCandies; i++)
    {
        int tip;
        std::cout << "1. NormalCandy\n";
        std::cout << "2. HCandy\n";
        std::cout << "3. VCandy\n";
        std::cout << "4. BombCandy\n";
        std::cout << "5. WildCandy\n";
        std::cout << "Introduceti tipul: ";
        tip = 1 + rand() % (numCandies - 1);
        if(tip < 0 || tip >= numCandies)
        {
            std::cout << "Tip invalid\n";
            continue;
        }
        candies.push_back(CandyFactory::CreateCandy(static_cast<CandyType>(tip)));
    }
    for(DemoCandy *candy : candies)
    {
        HorizontalStripedCandy *hCandy;
        VerticalStripedCandy *vCandy;
        BombCandy *bombCandy;
        WildCandy *wildCandy;

        if((hCandy = dynamic_cast<HorizontalStripedCandy*>(candy)) != nullptr) {
            hCandy->FunctieHorizontalStripedCandy();
        }
        else if((vCandy = dynamic_cast<VerticalStripedCandy*>(candy)) != nullptr) {
            vCandy->FunctieVerticalStripedCandy();
        } 
        else if((bombCandy = dynamic_cast<BombCandy*>(candy)) != nullptr) {
            bombCandy->FunctieBombCandy();
        }
        else if((wildCandy = dynamic_cast<WildCandy*>(candy)) != nullptr) {
            wildCandy->FunctieWildCandy();
        }
    }
    for(DemoCandy *candy : candies)
        delete candy;
}

int main() 
{   
    // TestTable& testTable = TestTable::GetInstance();
    // std::vector<TestTableEntry> entries = testTable.Select();

    // std::for_each(entries.begin(), entries.end(), 
    //     [](const TestTableEntry& entry) {
    //         std::cout << entry << std::endl;
    //     }
    // );
    
    // TestTableEntry entry;
    // std::cin >> entry;
    // if(testTable.Insert(entry))
    // {
    //     std::cout << "Inserted with id " << entry.GetID() << '\n';
    // }
    
    // entries = testTable.Select();
    // std::cout << "Updated table:\n";
    // std::for_each(entries.begin(), entries.end(), 
    //     [](const TestTableEntry& entry) {
    //         std::cout << entry << std::endl;
    //     }
    // );
    
    Demo();
    try {
        std::unique_ptr<CandyCrush> candyCrush = std::make_unique<CandyCrush>();
        candyCrush->Play();
        std::cout << *candyCrush << '\n';
    }
    catch (const SDLInitException& e) {
        std::cerr << "Library init failed " << e.what() << " " << e.GetErrorCode();
    }
    catch (const IMGInitException& e) {
        std::cerr << "Font init failed " << e.what() << " " << e.GetErrorCode();
    }
    catch (const TTFInitException& e) {
        std::cerr << "Image init failed " << e.what() << " " << e.GetErrorCode();
    }
    
    return 0;
}