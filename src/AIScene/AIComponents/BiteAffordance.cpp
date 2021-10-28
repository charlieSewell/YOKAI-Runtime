#include "BiteAffordance.hpp"

#include "glm/gtc/matrix_transform.hpp"

void BiteAffordance::EnableAbility(std::shared_ptr<EmotionSystem> emotionSystem)
{
	m_emotionSystemPtr = emotionSystem;
	HasAbility = true;
}

void BiteAffordance::EnableAffordance(std::function<glm::vec3()> getPosition, std::shared_ptr<EmotionSystem> emotionSystem)
{
	GetPosition = getPosition;
	m_emotionSystemPtr = emotionSystem;
	HasAffordance = true;
}

void BiteAffordance::Interact(std::shared_ptr<BiteAffordance> other)
{
	IsUsing = true;
	m_otherBiteAffordance = other;
	//m_otherBiteAffordance->IsAffording = true;
	m_emotionSystemPtr->TriggerEmotionalResponse(0.5, 0.5);
	m_otherBiteAffordance->m_emotionSystemPtr->TriggerEmotionalResponse(-1, 1);
}
 
void BiteAffordance::Stop()
{
	IsUsing = false;
	//m_otherBiteAffordance = nullptr;
}

void BiteAffordance::Update(float deltaTime)
{
	if(IsAffording)
	{
		//m_emotionSystemPtr->TriggerEmotionalResponse(-1, 1);
	}
}