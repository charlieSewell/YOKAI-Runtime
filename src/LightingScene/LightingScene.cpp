#include "LightingScene.hpp"
#include "Common/PlayerScript.hpp"
#include "Engine/JSONHelper.hpp"
LightingScene::LightingScene()
{
	m_sceneName = "ClusteredLightingDemo";
}

void LightingScene::Init()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);
	Player = m_objectManager.CreateObject();
    Scene =  m_objectManager.CreateObject();
    m_objectManager.GetObject(Scene)->AddComponent<DrawableEntity>()->LoadModel("content/sponza/sponza.obj");
    m_objectManager.GetObject(Scene)->Start();	// This line only exists to add a transform. Should come up with a better solution
	m_objectManager.GetObject(Scene)->GetComponent<Transform>()->Scale(0.1);

	m_objectManager.GetObject(Player)->AddComponent<PlayerScript>();
	m_objectManager.GetObject(Player)->Start();
	for (int i = 0; i < 1000; i++) 
	{
		m_lightManager.AddLight(glm::vec4(1.0f + dis(gen), 1.0f + dis(gen), 1.0f + dis(gen), 1.0f),glm::vec4(RandomPosition(dis, gen), 1.0f),glm::vec4(glm::vec3(0.0f), 40.0f));
	}
	UIInputObject = m_objectManager.CreateObject();
	UIinput = m_objectManager.GetObject(UIInputObject)->AddComponent<Input>();

}

void LightingScene::Update(double deltaTime)
{
    m_objectManager.Update(deltaTime);
	
 	if(UIinput->GetKeyToggle(YOKAI_INPUT::F))
	{
		m_physicsOn = !m_physicsOn;
	}	
	if(m_physicsOn)
	{
		for (int i = 0; i < 1000; i++) 
		{
			m_lightManager.GetLight(i)->position.y = m_lightManager.GetLight(i)->position.y = fmod((m_lightManager.GetLight(i)->position.y + (-4.5f * 0.1) - 0.0f + 170.0f), 170.0f) + 0.0f;
		}
	}
	if(UIinput->GetKeyState(YOKAI_INPUT::G))
	{
		YOKAI_PARSE::SaveScene("content/sponza.json", m_objectManager, m_lightManager);
	}
	m_lightManager.UpdateLights();
	//PhysicsSystem::getInstance().IsDebugEnabled(m_physicsOn);
}
void LightingScene::LateUpdate(double deltaTime)
{
	
}

void LightingScene::Draw()
{
	m_objectManager.Draw();
}

void LightingScene::Enable()
{
    isEnabled = true;
}

void LightingScene::Disable()
{
    isEnabled = false;
}
glm::vec3 LightingScene::RandomPosition(std::uniform_real_distribution<> dis, std::mt19937 gen) 
{
	const glm::vec3 LIGHT_MIN_BOUNDS = glm::vec3(-270.0f, 0.0f, -270.0f);
    const glm::vec3 LIGHT_MAX_BOUNDS = glm::vec3(270.0f, 170.0f, 270.0f);
	glm::vec3 position = glm::vec3(0.0);
	for (int i = 0; i < 3; i++) 
	{
		float min = LIGHT_MIN_BOUNDS[i];
		float max = LIGHT_MAX_BOUNDS[i];
		position[i] = (GLfloat)dis(gen) * (max - min) + min;
	}

	return position;
}