#include "LightingScene.hpp"
#include "Common/PlayerScript.hpp"
#include "Engine/JSONHelper.hpp"
LightingScene::LightingScene()
{
	m_sceneName = "ClusteredLightingDemo";
}

void LightingScene::Init()
{
	
	Player = m_objectManager.CreateObject();
    Scene =  m_objectManager.CreateObject();
	unsigned int test =  m_objectManager.CreateObject();
	unsigned int test2 =  m_objectManager.CreateObject();
	m_objectManager.GetObject(Scene)->AddComponent<DrawableEntity>()->LoadModel("content/new/Sponza/Sponza.gltf");
	m_objectManager.GetObject(test2)->AddComponent<DrawableEntity>()->LoadModel("content/FlightHelmet/FlightHelmet.gltf");
    m_objectManager.GetObject(test)->AddComponent<DrawableEntity>()->LoadModel("content/glTF-Sample-Models/2.0/MetalRoughSpheres/glTF/MetalRoughSpheres.gltf");
    m_objectManager.GetObject(Scene)->Start();	// This line only exists to add a transform. Should come up with a better solution
	m_objectManager.GetObject(test)->Start();	// This line only exists to add a transform. Should come up with a better solution
	m_objectManager.GetObject(test2)->Start();	// This line only exists to add a transform. Should come up with a better solution
	m_objectManager.GetObject(test2)->GetComponent<Transform>()->Translate(0,10,0);
	m_objectManager.GetObject(test2)->GetComponent<Transform>()->Scale(0.1);
	
	m_objectManager.GetObject(test)->GetComponent<Transform>()->Scale(4);
	m_objectManager.GetObject(test)->GetComponent<Transform>()->Translate(0,10,0);	
	m_objectManager.GetObject(Scene)->GetComponent<Transform>()->Scale(100);
	m_objectManager.GetObject(Player)->AddComponent<PlayerScript>();
	m_objectManager.GetObject(Player)->Start();
	m_lightManager.AddLight({0.1,1.5,-0.5},{1,1,1},0);
	UIInputObject = m_objectManager.CreateObject();
	UIinput = m_objectManager.GetObject(UIInputObject)->AddComponent<Input>();
	//YOKAI_PARSE::LoadScene("content/sponza.json", m_objectManager, m_lightManager);
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
		for (int i = 0; i < 1; i++) 
		{
			//m_lightManager.GetLight(i)->position.y = m_lightManager.GetLight(i)->position.y = fmod((m_lightManager.GetLight(i)->position.y + (-3.0f * 0.01) - 0.0f + 3.0f), 3.0f) + 0.0f;
		}
	}
	if(UIinput->GetKeyState(YOKAI_INPUT::G))
	{
		YOKAI_PARSE::SaveScene("content/sponza.json", m_objectManager, m_lightManager);
	}
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
PointLight LightingScene::RandomLight() 
{
	std::random_device rd;
    std::seed_seq seed = { rd() };
    std::mt19937 gen(seed);
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
	
	constexpr float POWER_MIN = 20.0f;
    constexpr float POWER_MAX = 100.0f;
	glm::vec3 scale {10,10,10};
	glm::vec3 position = glm::vec3(0.0);
	position += glm::vec3(dist(gen), dist(gen), dist(gen)) * scale - (scale * 0.5f);
    glm::vec3 color = glm::vec3(dist(gen), dist(gen), dist(gen));
    glm::vec3 power = color * glm::vec3(dist(gen) * (POWER_MAX - POWER_MIN) + POWER_MIN);

	return { position, power };
}