#include "AffordanceSystem.hpp"

AffordanceSystem::AffordanceSystem(GameObject* parent)
	:
	Component(parent)
{

}

void AffordanceSystem::Update(float deltaTime)
{
	for (int i = m_affordances.size() - 1; i >= 0; i--)
	{
		m_affordances[i]->Update(deltaTime);
	}
}