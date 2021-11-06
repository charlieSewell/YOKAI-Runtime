#include "CharliePhysics.hpp"
#include "Common/PlayerScript.hpp"
#include "Components/SphereCollider.hpp"
#include "Components/BoxCollider.hpp"
#include "Physics/Physics.hpp"
#include "glm/gtx/string_cast.hpp"

CharliePhysics::CharliePhysics()
{
	m_sceneName = "PhysicsDemo";
}

void CharliePhysics::PhysicsTest1()
{
	m_objectManager.GetObject(Plank1)->GetComponent<BoxCollider>()->SetLinearVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Plank1)->GetComponent<BoxCollider>()->SetAngularVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Plank1)->GetComponent<BoxCollider>()->SetMass(2.0);
	m_objectManager.GetObject(Plank1)->GetComponent<BoxCollider>()->SetIsStaticObject(false);
	m_objectManager.GetObject(Plank1)->GetComponent<BoxCollider>()->SetInertiaTensor();
	m_objectManager.GetObject(Plank1)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(1, 0, 0, 0));
	m_objectManager.GetObject(Plank1)->GetComponent<BoxCollider>()->SetCollisionCategory(Physics::CATEGORY2);
	m_objectManager.GetObject(Plank1)->GetComponent<BoxCollider>()->SetCollisionMaskBits(Physics::CATEGORY1 | Physics::CATEGORY2);
	//m_objectManager.GetObject(Plank1)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.707, 0, 0, 0.707));
	//m_objectManager.GetObject(Plank1)->GetComponent<BoxCollider>()->SetGravityAffected(true);

	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetLinearVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetAngularVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetMass(2.0);
	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetIsStaticObject(false);
	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetInertiaTensor();
	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(1.0, 0, 0, 0));
	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetCollisionCategory(Physics::CATEGORY2);
	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetCollisionMaskBits(Physics::CATEGORY1 | Physics::CATEGORY2);
	//m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.854, 0.354, -0.146, 0.354));
	//m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetGravityAffected(true);

	m_objectManager.GetObject(Ball)->GetComponent<SphereCollider>()->SetLinearVelocity(glm::dvec3(-1, 0, 0));
	m_objectManager.GetObject(Ball)->GetComponent<SphereCollider>()->SetAngularVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Ball)->GetComponent<SphereCollider>()->SetMass(2.0);
	m_objectManager.GetObject(Ball)->GetComponent<SphereCollider>()->SetIsStaticObject(false);
	m_objectManager.GetObject(Ball)->GetComponent<SphereCollider>()->SetInertiaTensor();
	m_objectManager.GetObject(Ball)->GetComponent<SphereCollider>()->SetOrientation(glm::quat(1, 0, 0, 0));

	m_objectManager.GetObject(Ball)->GetComponent<SphereCollider>()->SetCollisionCategory(Physics::CATEGORY2);
	m_objectManager.GetObject(Ball)->GetComponent<SphereCollider>()->SetCollisionMaskBits(Physics::CATEGORY1 | Physics::CATEGORY2);
	//m_objectManager.GetObject(Ball)->GetComponent<SphereCollider>()->SetGravityAffected(true);
}


void CharliePhysics::Init()
{
	Player = m_objectManager.CreateObject("Player");
	m_objectManager.GetObject(Player)->AddComponent<PlayerScript>();
	m_objectManager.GetObject(Player)->GetComponent<Transform>()->SetPosition(11, 3, 1);
	m_objectManager.GetObject(Player)->Start();


	Wall1 = m_objectManager.CreateObject("Wall1");
	m_objectManager.GetObject(Wall1)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/Desk/gridwall.gltf");
	m_objectManager.GetObject(Wall1)->AddComponent<Transform>()->SetPosition(glm::dvec3(12.125, -0.8, -10));
	m_objectManager.GetObject(Wall1)->Start();
	m_objectManager.GetObject(Wall1)->GetComponent<Transform>()->SetScale(10);

	//Test 1 Init

	Ball = m_objectManager.CreateObject("Ball");
	Plank1 = m_objectManager.CreateObject("Plank 1");
	Plank2 = m_objectManager.CreateObject("Plank 2");

	m_objectManager.GetObject(Plank1)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/physicsblock.gltf");
	m_objectManager.GetObject(Plank2)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/physicsblock.gltf");
	m_objectManager.GetObject(Ball)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/physicsbullet.gltf");

	glm::mat4 offset = glm::mat4(1.0);
	offset = glm::translate(offset, glm::vec3(0.0, -0.3, -0.00685));
	m_objectManager.GetObject(Plank1)->AddComponent<Transform>()->SetPosition(glm::dvec3(10.5, 2.66, -4));
	m_objectManager.GetObject(Plank1)->GetComponent<DrawableEntity>()->SetOffset(offset);
	m_objectManager.GetObject(Plank1)->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(0.02, 0.16, 0.1));
	m_objectManager.GetObject(Plank1)->Start();

	m_objectManager.GetObject(Plank2)->AddComponent<Transform>()->SetPosition(glm::dvec3(11.5, 2.66, -4));
	m_objectManager.GetObject(Plank2)->GetComponent<DrawableEntity>()->SetOffset(offset);
	m_objectManager.GetObject(Plank2)->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(0.02, 0.16, 0.1));
	m_objectManager.GetObject(Plank2)->Start();

	glm::mat4 offset1 = glm::mat4(1.0);
	offset1 = glm::translate(offset1, glm::vec3(0.2075, -0.735, 0));
	offset1 = glm::scale(offset1, glm::vec3(2.5, 2.5, 2.5));
	m_objectManager.GetObject(Ball)->GetComponent<DrawableEntity>()->SetOffset(offset1);
	m_objectManager.GetObject(Ball)->AddComponent<Transform>()->SetPosition(glm::dvec3(14, 2.75, -3.9));
	m_objectManager.GetObject(Ball)->AddComponent<SphereCollider>()->SetRadius(0.041);
	m_objectManager.GetObject(Ball)->Start();


	// COLLIDERS
	InitColliders();
	UIInputObject = m_objectManager.CreateObject();
	UIinput = m_objectManager.GetObject(UIInputObject)->AddComponent<Input>();

}

void CharliePhysics::Update(double frameRate)
{
	m_objectManager.Update(frameRate);
	//PhysicsSystem::getInstance().IsDebugEnabled(m_physicsOn);
	//m_physicsOn = true;

	if (UIinput->GetKeyToggle(YOKAI_INPUT::NUM_1))
	{
		PhysicsTest1();
	}

	if (UIinput->GetKeyToggle(YOKAI_INPUT::NUM_2))
	{
		m_objectManager.GetObject(Ball)->GetComponent<SphereCollider>()->SetGravityAffected(true);
		m_objectManager.GetObject(Plank1)->GetComponent<BoxCollider>()->SetGravityAffected(true);
		m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetGravityAffected(true);
	}
	if(UIinput->GetKeyToggle(YOKAI_INPUT::Q))
	{
		unsigned int Bullet = m_objectManager.CreateObject("Bullet");
		m_objectManager.GetObject(Bullet)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/physicsbullet.gltf");

		glm::vec3 playerPos = m_objectManager.GetObject(Player)->GetComponent<Transform>()->GetPosition();
		glm::vec3 frontDirection = m_objectManager.GetObject(Player)->GetComponent<Camera>()->m_frontDirection;

		glm::mat4 offset1 = glm::mat4(1.0);
		offset1 = glm::translate(offset1, glm::vec3(0.2075, -0.735, 0));
		offset1 = glm::scale(offset1, glm::vec3(2.5, 2.5, 2.5));
		m_objectManager.GetObject(Bullet)->GetComponent<DrawableEntity>()->SetOffset(offset1);
		m_objectManager.GetObject(Bullet)->AddComponent<Transform>()->SetPosition(playerPos);
		m_objectManager.GetObject(Bullet)->AddComponent<SphereCollider>()->SetRadius(0.041);
		m_objectManager.GetObject(Bullet)->Start();

		m_objectManager.GetObject(Bullet)->GetComponent<SphereCollider>()->SetLinearVelocity(glm::normalize(frontDirection) * 4.0f);
		m_objectManager.GetObject(Bullet)->GetComponent<SphereCollider>()->SetAngularVelocity(glm::dvec3(0, 0, 0));
		m_objectManager.GetObject(Bullet)->GetComponent<SphereCollider>()->SetMass(1.0f);
		m_objectManager.GetObject(Bullet)->GetComponent<SphereCollider>()->SetIsStaticObject(false);
		m_objectManager.GetObject(Bullet)->GetComponent<SphereCollider>()->SetInertiaTensor();
		m_objectManager.GetObject(Bullet)->GetComponent<SphereCollider>()->SetOrientation(glm::quat(1, 0, 0, 0));
		m_objectManager.GetObject(Bullet)->GetComponent<SphereCollider>()->SetCollisionCategory(Physics::CATEGORY2);
		m_objectManager.GetObject(Bullet)->GetComponent<SphereCollider>()->SetCollisionMaskBits(Physics::CATEGORY1 | Physics::CATEGORY2);
	}
}
void CharliePhysics::LateUpdate(double frameRate)
{
	m_objectManager.LateUpdate(frameRate);
}
void CharliePhysics::Draw()
{
	m_objectManager.Draw();
}
void CharliePhysics::Enable()
{
    isEnabled = true;
}

void CharliePhysics::Disable()
{
    isEnabled = false;
}

void CharliePhysics::InitColliders()
{
	for (int i = 0; i < 1; i++)
	{
		Colliders.push_back(m_objectManager.CreateObject());
	}
	int counter = 0;
	
	// Floor
	m_objectManager.GetObject(Colliders[counter])->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(20, 0.2, 20));
	m_objectManager.GetObject(Colliders[counter])->AddComponent<Transform>()->SetPosition(glm::dvec3(15, 0, -15));
	m_objectManager.GetObject(Colliders[counter])->Start();
	m_objectManager.GetObject(Colliders[counter])->GetComponent<BoxCollider>()->StaticSet();
	++counter;
}