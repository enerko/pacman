#pragma once

#include <vector>
#include "math.h"

class actor
{
public:
    enum class state
    {
        EActive, EPaused, EDead
    };

    actor(class game* gameInstance);
    virtual ~actor();

    void update(float deltaTime);
    void updateComponents(float deltaTime);
    virtual void updateActor(float deltaTime);

    void addComponent(class component* componentToAdd);
    void removeComponent(class component* componentToRemove);

    state getState() {return mState; }
    class game* getGame() { return mGame; }

    float getScale() { return mScale; }

    const Vector2& getPosition() const { return mPosition; }
    void setPosition(const Vector2& position) { mPosition = position; }

    float getRotation() const { return mRotation; }
    
private:
    class game* mGame;
    float mScale;

    Vector2 mPosition;
    float mRotation;

    state mState;
    std::vector<class component*> mComponents;
};