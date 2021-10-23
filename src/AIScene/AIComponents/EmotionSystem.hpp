#pragma once

#include "Components/Component.hpp"

class GameObject;

enum class EMOTION
{
	FEAR,
	FRUSTRATION,
	BORED,
	EXCITED,
	CALM
};

class EmotionSystem : public Component
{
public:
	EmotionSystem(GameObject* parent);

private:

	struct
	{
		double Confidence = 0.5;
		double Enthusiasm = 0.5;
	} m_traits;
};