#pragma once

#include "Components/Component.hpp"
#include <map>

class GameObject;

enum class AFFORDANCE_TYPE
{
	PICKUPABLE = 0
};

class AffordanceSystem : public Component
{
public:
	AffordanceSystem(GameObject* parent);

	void AddAffordance(AFFORDANCE_TYPE type);
	void CheckIsAvailable(AFFORDANCE_TYPE type);
	void Interact(AFFORDANCE_TYPE type);

private:

	std::map<AFFORDANCE_TYPE, bool> m_activeAffordances;

};