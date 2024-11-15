#include "component.h"
#include "actor.h"

component::component(actor* owner, int updateOrder)
: mOwner(owner)
{
    mOwner -> addComponent(this);
}

component::~component()
{
    mOwner -> removeComponent(this);
}

void component::update(float deltaTimer)
{

}