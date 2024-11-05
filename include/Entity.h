#ifndef ENTITY_H_
#define ENTITY_H_

#include <ostream>
#include <cstdint>
class Entity {
protected:
    unsigned long long id;
    // uint64_t
public:
    Entity(unsigned long long id) : id {id} { }
    unsigned long long GetID() { return id; }
    virtual void Print(std::ostream& os) const = 0;
    friend std::ostream& operator<<(std::ostream& os, const Entity& entry);
};

#endif /* ENTITY_H_ */