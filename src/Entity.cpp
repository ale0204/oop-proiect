#include "../include/Entity.h"

std::ostream& operator<<(std::ostream& os, const Entity& entry)
{
    entry.Print(os);
    return os;
}