#include "EmotionSystem.hpp"

EmotionSystem::EmotionSystem(GameObject* parent)
	:
	Component(parent)
{

}

void EmotionSystem::TriggerEmotionalResponse(double stimuliValence, double stimuliArousal)
{
	m_mood.Valence = stimuliValence;

	if(m_mood.Valence > 0)
	{
		m_mood.Arousal += stimuliArousal * (m_traits.Enthusiasm * 2);

		// Max Valence reaced
		if(m_mood.Valence > 1)
		{
			m_mood.Valence = 1;
		}
	}
	else
	{
		m_mood.Arousal += stimuliArousal * (m_traits.Meekness * 2);

		// Min valence reached
		if (m_mood.Valence < -1)
		{
			m_mood.Valence = -1;
		}
	}

	// Max arousal reached
	if(m_mood.Arousal > 1)
	{
		m_mood.Arousal = 1;
	}

	// Min arousal reached
	if (m_mood.Arousal < 0)
	{
		m_mood.Arousal = 0;
	}
}

void EmotionSystem::UpdateEmotionalState()
{
	//double moodDecay = 100 * deltaTime;	//TODO CONNOR: make this a meaningful number

	double moodDecay = 0.0005;

	if (m_mood.Valence > 0.01)
	{
		m_mood.Valence -= moodDecay;
	}
	else if (m_mood.Valence < 0)
	{
		m_mood.Valence += moodDecay;
	}

	if (m_mood.Arousal > 0.01)
	{
		m_mood.Arousal -= moodDecay;
	}

	if (m_mood.Valence > 0)
	{
		if (m_mood.Arousal > EXCITED_MIN)
		{
			m_currentEmotion = EMOTION::EXCITED;
		}
		else
		{
			m_currentEmotion = EMOTION::CALM;
		}
	}
	else
	{
		if (m_mood.Arousal > FEAR_MIN)
		{
			m_currentEmotion = EMOTION::FEAR;
		}
		else if (m_mood.Arousal > FRUSTRATED_MIN)
		{
			m_currentEmotion = EMOTION::FRUSTRATED;
		}
		else
		{
			m_currentEmotion = EMOTION::BORED;
		}
	}
}

#include <iostream>
void EmotionSystem::Update(float deltaTime)
{
	UpdateEmotionalState();

	std::cout << "Emotion: " << int(m_currentEmotion) << "  |  Valence: " << m_mood.Valence << ", Arousal: " << m_mood.Arousal << "\n";
}