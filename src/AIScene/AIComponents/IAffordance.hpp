#pragma once

#include <memory>

class Affordance
{
public:

	Affordance(){}

	bool HasAffordance = false;
	bool HasAbility = false;
	bool IsAvailable = false;
	bool IsActive = false;
	
	template <typename T> void Interact(std::shared_ptr<T> otherAffordance) = 0;

	virtual void Afford() = 0;

protected:

};