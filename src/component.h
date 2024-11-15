#pragma once

class component
{
public:
    component(class actor* owner, int updateOrder = 100); // The lower the update order, the earlier the component updates
    virtual ~component();

    virtual void update(float deltaTime);

    int getUpdateOrder() const { return mUpdateOrder; }

    actor* getOwner();

protected:
    class actor* mOwner;
    int mUpdateOrder;

};