#ifndef ENTITY_H_
#define ENTITY_H_

#include <ostream>
class Entity {
protected:
    unsigned long long id;
public:
    Entity(unsigned long long id) : id {id} { }
    unsigned long long GetID() { return id; }
    virtual void Print(std::ostream& os) const = 0;
};

#endif /* ENTITY_H_ */