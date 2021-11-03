#include "ConnorsPhysicsScene.hpp"
#include "Common/PlayerScript.hpp"
#include "Components/SphereCollider.hpp"
#include "Components/BoxCollider.hpp"
#include "Physics/Physics.hpp"
#include "glm/gtx/string_cast.hpp"

ConnorsPhysicsScene::ConnorsPhysicsScene()
{
	m_sceneName = "ConnorsPhysicsDemo";
}

void ConnorsPhysicsScene::Reset()
{
	m_objectManager.GetObject(Plank1)->AddComponent<BoxCollider>()->SetPosition(glm::dvec3(10.5, 2.66, -4));
	m_objectManager.GetObject(Plank1)->GetComponent<BoxCollider>()->SetLinearVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Plank1)->GetComponent<BoxCollider>()->SetAngularVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Plank1)->GetComponent<BoxCollider>()->SetMass(2.0);
	m_objectManager.GetObject(Plank1)->GetComponent<BoxCollider>()->SetIsStaticObject(false);
	m_objectManager.GetObject(Plank1)->GetComponent<BoxCollider>()->SetInertiaTensor();
	m_objectManager.GetObject(Plank1)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(1, 0, 0, 0));

	m_objectManager.GetObject(Plank2)->AddComponent<BoxCollider>()->SetPosition(glm::dvec3(11.5, 2.66, -4));
	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetLinearVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetAngularVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetMass(2.0);
	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetIsStaticObject(false);
	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetInertiaTensor();
	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(1.0, 0, 0, 0));

	m_objectManager.GetObject(Table)->AddComponent<BoxCollider>()->SetPosition(glm::dvec3(11.3, 2.36, -4));
	m_objectManager.GetObject(Table)->GetComponent<BoxCollider>()->SetLinearVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Table)->GetComponent<BoxCollider>()->SetAngularVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Table)->GetComponent<BoxCollider>()->SetMass(9999999999.0);
	m_objectManager.GetObject(Table)->GetComponent<BoxCollider>()->SetIsStaticObject(true);
	m_objectManager.GetObject(Table)->GetComponent<BoxCollider>()->SetInertiaTensor();
	m_objectManager.GetObject(Table)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(1.0, 0, 0, 0));
}

void ConnorsPhysicsScene::Init()
{
	Player = m_objectManager.CreateObject("Player");
	m_objectManager.GetObject(Player)->AddComponent<PlayerScript>();
	m_objectManager.GetObject(Player)->GetComponent<Transform>()->setPosition(11, 3, 1);
	m_objectManager.GetObject(Player)->GetComponent<PlayerScript>()->movementSpeed = 0.0125f;
	m_objectManager.GetObject(Player)->Start();
	

	glm::mat4 offset = glm::mat4(1.0);
	offset = glm::translate(offset, glm::vec3(0.0, -0.3, -0.00685));
	Plank1 = m_objectManager.CreateObject("Plank 1");
	m_objectManager.GetObject(Plank1)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/physicsblock.gltf");
	m_objectManager.GetObject(Plank1)->GetComponent<DrawableEntity>()->SetOffset(offset);
	m_objectManager.GetObject(Plank1)->AddComponent<Transform>()->setPosition(glm::dvec3(10.5, 2.66, -4));
	m_objectManager.GetObject(Plank1)->GetComponent<Transform>()->scale(0.75, 0.94, 1);								// scaled model to match collider requirements
	m_objectManager.GetObject(Plank1)->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(0.015, 0.15, 0.1));		// in cm
	m_objectManager.GetObject(Plank1)->Start();

	Plank2 = m_objectManager.CreateObject("Plank 2");
	m_objectManager.GetObject(Plank2)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/physicsblock.gltf");
	m_objectManager.GetObject(Plank2)->GetComponent<DrawableEntity>()->SetOffset(offset);
	m_objectManager.GetObject(Plank2)->AddComponent<Transform>()->setPosition(glm::dvec3(11.5, 2.66, -4));	
	m_objectManager.GetObject(Plank2)->GetComponent<Transform>()->scale(0.75, 0.94, 1);								// scaled model to match collider requirements
	m_objectManager.GetObject(Plank2)->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(0.015, 0.15, 0.1));		// in cm
	m_objectManager.GetObject(Plank2)->Start();

	Table = m_objectManager.CreateObject("Table");
	m_objectManager.GetObject(Table)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/physicsblock.gltf");
	m_objectManager.GetObject(Table)->GetComponent<DrawableEntity>()->SetOffset(offset);
	m_objectManager.GetObject(Table)->AddComponent<Transform>()->setPosition(glm::dvec3(11.3, 2.36, -4));
	m_objectManager.GetObject(Table)->GetComponent<Transform>()->scale(90.3, 00.94, 6.6);								// scaled model to match collider requirements
	m_objectManager.GetObject(Table)->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(1.4, 00.15, 0.66));		// in cm
	m_objectManager.GetObject(Table)->Start();
	
	offset = glm::mat4(1.0);
	offset = glm::translate(offset, glm::vec3(0.2075, -0.735, 0));
	offset = glm::scale(offset, glm::vec3(2.5));

	for(int i=0; i<NUM_BALLS; ++i)
	{
		Ball[i] = m_objectManager.CreateObject("Ball");
		m_objectManager.GetObject(Ball[i])->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/physicsbullet.gltf");
		m_objectManager.GetObject(Ball[i])->GetComponent<DrawableEntity>()->SetOffset(offset);
		m_objectManager.GetObject(Ball[i])->AddComponent<Transform>()->setPosition(glm::dvec3(0, 0, 0));
		m_objectManager.GetObject(Ball[i])->AddComponent<SphereCollider>()->SetRadius(0.041);
		m_objectManager.GetObject(Ball[i])->Start();
	}

	Reset();

	UIInputObject = m_objectManager.CreateObject();
	UIinput = m_objectManager.GetObject(UIInputObject)->AddComponent<Input>();

}

void ConnorsPhysicsScene::Shoot()
{
	glm::vec3 playerPosition = m_objectManager.GetObject(Player)->GetComponent<Transform>()->getPosition();
	glm::vec3 playerFrontDirection = m_objectManager.GetObject(Player)->GetComponent<Camera>()->m_frontDirection;

	m_objectManager.GetObject(Ball[ballIndex])->GetComponent<SphereCollider>()->SetPosition(playerPosition);
	m_objectManager.GetObject(Ball[ballIndex])->GetComponent<SphereCollider>()->SetLinearVelocity(glm::normalize(playerFrontDirection) * 2.0f);
	m_objectManager.GetObject(Ball[ballIndex])->GetComponent<SphereCollider>()->SetAngularVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Ball[ballIndex])->GetComponent<SphereCollider>()->SetMass(0.1);
	m_objectManager.GetObject(Ball[ballIndex])->GetComponent<SphereCollider>()->SetIsStaticObject(false);
	m_objectManager.GetObject(Ball[ballIndex])->GetComponent<SphereCollider>()->SetInertiaTensor();
	m_objectManager.GetObject(Ball[ballIndex])->GetComponent<SphereCollider>()->SetOrientation(glm::quat(1, 0, 0, 0));
	
	++ballIndex;
	if(ballIndex >= NUM_BALLS)
	{
		ballIndex = 0;
	}
}

void ConnorsPhysicsScene::Update(double frameRate)
{
	m_objectManager.Update(frameRate);

	if (UIinput->GetKeyToggle(YOKAI_INPUT::R))
	{
		Reset();
	}

	if (UIinput->GetKeyToggle(YOKAI_INPUT::C))
	{
		Shoot();
	}
}
void ConnorsPhysicsScene::LateUpdate(double frameRate)
{
	m_objectManager.LateUpdate(frameRate);
}
void ConnorsPhysicsScene::Draw()
{
	m_objectManager.Draw();
}
void ConnorsPhysicsScene::Enable()
{
    isEnabled = true;
}

void ConnorsPhysicsScene::Disable()
{
    isEnabled = false;
}