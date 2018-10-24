#include "Entity.h"



Entity::Entity(const int level) : level_{level}, attack_{0}, defence_{0}, experiencepoints_{0}, healthpoints_{0}, name_{"monster"}
{
}


Entity::~Entity()
{
}
