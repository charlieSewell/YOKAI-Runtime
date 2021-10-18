#pragma once

#include <memory>

class Affordance
{
public:

	Affordance(){}

	virtual void Update(float deltaTime) {};

	bool HasAffordance = false;
	bool HasAbility = false;
	bool IsAvailable = false;
	bool IsActive = false;
	
	template <typename T> void Interact(std::shared_ptr<T> otherAffordance) = 0;

	virtual void Stop() = 0;

protected:

};