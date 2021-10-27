#pragma once

#include "Components/Component.hpp"

class GameObject;

constexpr double FEAR_MIN =			0.669;
constexpr double FRUSTRATED_MIN =	0.339;
constexpr double BORED_MIN =		0;
constexpr double EXCITED_MIN =		0.669;
constexpr double CALM_MIN =			0;

enum class EMOTION
{
	FEAR,
	FRUSTRATED,
	BORED,
	EXCITED,
	CALM
};

class EmotionSystem : public Component
{
public:

	EmotionSystem(GameObject* parent);

	void TriggerEmotionalResponse(double stimuliValence, double stimuliArousal);
	EMOTION GetCurrentEmotion();

	void Update(float deltaTime) override;

private:

	void UpdateEmotionalState();

	struct
	{
		double Meekness = 1.0;
		double Enthusiasm = 1.0;
	} m_traits;

	struct
	{
		double Arousal = 0.0;
		double Valence = 0.0;
	} m_mood;

	EMOTION m_currentEmotion = EMOTION::CALM;
};