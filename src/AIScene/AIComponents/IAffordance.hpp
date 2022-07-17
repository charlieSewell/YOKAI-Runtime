#pragma once

#include <memory>

class IAffordance
{
public:

	IAffordance() = default;

	virtual void Update(float deltaTime) = 0;

	bool HasAffordance = false;
	bool HasAbility = false;
	bool IsUsing = false;
	bool IsAffording = false;
	
	template <typename T> void Interact(std::shared_ptr<T> otherAffordance) = 0;

	virtual void Stop() = 0;

protected:
};