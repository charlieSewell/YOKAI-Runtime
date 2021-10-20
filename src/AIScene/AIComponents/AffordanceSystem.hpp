#pragma once

#include "IAffordance.hpp"
#include "Components/Component.hpp"
#include <vector>
#include <memory>

class GameObject;

class AffordanceSystem : public Component
{
public:
	AffordanceSystem(GameObject* parent);

	void Update(float deltaTime) override;

	template <typename T> std::shared_ptr<T> AddAffordance()
	{
		static_assert(std::is_base_of<IAffordance, T>::value, "T must derive from IAffordance");

		// Check that we don't already have an affordance of this type.
		for (auto& exisitingAffordance : m_affordances)
		{
			if (std::dynamic_pointer_cast<T>(exisitingAffordance))
			{
				return std::dynamic_pointer_cast<T>(exisitingAffordance);
			}
		}
		std::shared_ptr<T> newAffordance = std::make_shared<T>();
		m_affordances.push_back(newAffordance);

		return newAffordance;
	};

	template <typename T> std::shared_ptr<T> GetAffordance()
	{
		static_assert(std::is_base_of<IAffordance, T>::value, "T must derive from IAffordance");
		for (auto& exisitingAffordance : m_affordances)
		{
			if (std::dynamic_pointer_cast<T>(exisitingAffordance))
			{
				return std::dynamic_pointer_cast<T>(exisitingAffordance);
			}
		}
		return nullptr;
	};

private:

	std::vector<std::shared_ptr<IAffordance>> m_affordances;

};