#ifndef ENTITY_H_
#define ENTITY_H_

#include <ostream>
#include <cstdint>
class Entity {
protected:
    uint64_t id;
public:
    Entity(uint64_t id) : id {id} { }
    uint64_t GetID() { return id; }
    virtual void Print(std::ostream& os) const = 0;
    friend std::ostream& operator<<(std::ostream& os, const Entity& entry);
};

#endif /* ENTITY_H_ */