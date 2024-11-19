#include "actor.h"
#include "game.h"
#include "component.h"

#include <algorithm>

actor::actor(game* gameInstance)
: mState(state::EActive), mGame(gameInstance), mScale(1.0f), mRotation(0.0f)
{
    mPosition = Vector2(0,0);
    mGame -> addActor(this);
}

actor::~actor()
{
    mGame -> removeActor(this);
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}

}

void actor::update(float deltaTime)
{
	if (mState == state::EActive)
	{
		updateComponents(deltaTime);
		updateActor(deltaTime);
	}
}

void actor::updateComponents(float deltaTime)
{
	for (auto comp : mComponents)
	{
		comp->update(deltaTime);
	}
}

void actor::updateActor(float deltaTime)
{
}

void actor::addComponent(component* compToAdd)
{
    // Find the insertion point in the sorted vector
	// i.e. first element with a higher order
	int myOrder = compToAdd->getUpdateOrder();
	auto iter = mComponents.begin();
	for ( ; iter != mComponents.end() ; ++iter)
	{
		if (myOrder < (*iter)->getUpdateOrder())
		{
			break;
		}
	}

	// Insert component before position of iterator
	mComponents.insert(iter, compToAdd);
}

void actor::removeComponent(component* compToRemove)
{
    auto iter = std::find(mComponents.begin(), mComponents.end(), compToRemove);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}