#include "PhysicsScene.hpp"
#include "Common/PlayerScript.hpp"
#include "Components/SphereCollider.hpp"
#include "Components/BoxCollider.hpp"
#include "Physics/Physics.hpp"
#include "glm/gtx/string_cast.hpp"

PhysicsScene::PhysicsScene()
{
	m_sceneName = "Reset";
}

void PhysicsScene::PhysicsTest1()
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

void PhysicsScene::PhysicsTest2()
{
	m_objectManager.GetObject(Ball2)->GetComponent<SphereCollider>()->SetLinearVelocity(glm::dvec3(0.5, 0, 0));
	m_objectManager.GetObject(Ball2)->GetComponent<SphereCollider>()->SetAngularVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Ball2)->GetComponent<SphereCollider>()->SetMass(2.0);
	m_objectManager.GetObject(Ball2)->GetComponent<SphereCollider>()->SetIsStaticObject(false);
	m_objectManager.GetObject(Ball2)->GetComponent<SphereCollider>()->SetInertiaTensor();
	m_objectManager.GetObject(Ball2)->GetComponent<SphereCollider>()->SetOrientation(glm::quat(1, 0, 0, 0));
	m_objectManager.GetObject(Ball2)->GetComponent<SphereCollider>()->SetCollisionCategory(Physics::CATEGORY2);
	m_objectManager.GetObject(Ball2)->GetComponent<SphereCollider>()->SetCollisionMaskBits(Physics::CATEGORY1 | Physics::CATEGORY2);
	//m_objectManager.GetObject(Ball2)->GetComponent<SphereCollider>()->SetGravityAffected(true);

	m_objectManager.GetObject(Ball3)->GetComponent<SphereCollider>()->SetLinearVelocity(glm::dvec3(-0.5, 0, 0));
	m_objectManager.GetObject(Ball3)->GetComponent<SphereCollider>()->SetAngularVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Ball3)->GetComponent<SphereCollider>()->SetMass(20.0);
	m_objectManager.GetObject(Ball3)->GetComponent<SphereCollider>()->SetIsStaticObject(false);
	m_objectManager.GetObject(Ball3)->GetComponent<SphereCollider>()->SetInertiaTensor();
	m_objectManager.GetObject(Ball3)->GetComponent<SphereCollider>()->SetOrientation(glm::quat(1, 0, 0, 0));
	m_objectManager.GetObject(Ball3)->GetComponent<SphereCollider>()->SetCollisionCategory(Physics::CATEGORY2);
	m_objectManager.GetObject(Ball3)->GetComponent<SphereCollider>()->SetCollisionMaskBits(Physics::CATEGORY1 | Physics::CATEGORY2);
	//m_objectManager.GetObject(Ball2)->GetComponent<SphereCollider>()->SetGravityAffected(true);
}

void PhysicsScene::PhysicsTest3()
{
	m_objectManager.GetObject(Plank3)->GetComponent<BoxCollider>()->SetLinearVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Plank3)->GetComponent<BoxCollider>()->SetAngularVelocity(glm::dvec3(2, 2, 2));
	m_objectManager.GetObject(Plank3)->GetComponent<BoxCollider>()->SetMass(2.0);
	m_objectManager.GetObject(Plank3)->GetComponent<BoxCollider>()->SetIsStaticObject(false);
	m_objectManager.GetObject(Plank3)->GetComponent<BoxCollider>()->SetInertiaTensor();
	m_objectManager.GetObject(Plank3)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(1, 0, 0, 0));
	m_objectManager.GetObject(Plank3)->GetComponent<BoxCollider>()->SetCollisionCategory(Physics::CATEGORY2);
	m_objectManager.GetObject(Plank3)->GetComponent<BoxCollider>()->SetCollisionMaskBits(Physics::CATEGORY1 | Physics::CATEGORY2);
	//m_objectManager.GetObject(Plank3)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.707, 0, 0, 0.707));
	m_objectManager.GetObject(Plank3)->GetComponent<BoxCollider>()->SetGravityAffected(true);

	m_objectManager.GetObject(Plank4)->GetComponent<BoxCollider>()->SetLinearVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Plank4)->GetComponent<BoxCollider>()->SetAngularVelocity(glm::dvec3(-1, -1, -1));
	m_objectManager.GetObject(Plank4)->GetComponent<BoxCollider>()->SetMass(2.0);
	m_objectManager.GetObject(Plank4)->GetComponent<BoxCollider>()->SetIsStaticObject(false);
	m_objectManager.GetObject(Plank4)->GetComponent<BoxCollider>()->SetInertiaTensor();
	m_objectManager.GetObject(Plank4)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(1.0, 0, 0, 0));
	m_objectManager.GetObject(Plank4)->GetComponent<BoxCollider>()->SetCollisionCategory(Physics::CATEGORY2);
	m_objectManager.GetObject(Plank4)->GetComponent<BoxCollider>()->SetCollisionMaskBits(Physics::CATEGORY1 | Physics::CATEGORY2);
	//m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.854, 0.354, -0.146, 0.354));
	m_objectManager.GetObject(Plank4)->GetComponent<BoxCollider>()->SetGravityAffected(true);
}

void PhysicsScene::Init()
{
	Player = m_objectManager.CreateObject("Player");
	m_objectManager.GetObject(Player)->AddComponent<PlayerScript>();
	m_objectManager.GetObject(Player)->GetComponent<Transform>()->setPosition(11, 3, 1);
	m_objectManager.GetObject(Player)->Start();

	//Walls and Box

	Box = m_objectManager.CreateObject("Box");
	m_objectManager.GetObject(Box)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/Desk/woodbox.gltf");
	m_objectManager.GetObject(Box)->AddComponent<Transform>()->setPosition(glm::dvec3(12.125, 0.66, -10));
	m_objectManager.GetObject(Box)->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(0.5, 0.5, 0.5));
	m_objectManager.GetObject(Box)->Start();
	m_objectManager.GetObject(Box)->GetComponent<BoxCollider>()->StaticSet();
	m_objectManager.GetObject(Box)->GetComponent<Transform>()->setScale(0.5);

	Wall1 = m_objectManager.CreateObject("Wall1");
	m_objectManager.GetObject(Wall1)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/Desk/gridwall.gltf");
	m_objectManager.GetObject(Wall1)->AddComponent<Transform>()->setPosition(glm::dvec3(12.125, -0.8, -10));
	m_objectManager.GetObject(Wall1)->Start();
	m_objectManager.GetObject(Wall1)->GetComponent<Transform>()->setScale(10);

	Wall2 = m_objectManager.CreateObject("Wall2");
	m_objectManager.GetObject(Wall2)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/Desk/gridwall.gltf");
	m_objectManager.GetObject(Wall2)->AddComponent<Transform>()->setPosition(glm::dvec3(6.6, 0.25, -6.5));
	m_objectManager.GetObject(Wall2)->Start();
	m_objectManager.GetObject(Wall2)->GetComponent<Transform>()->setScale(5);
	m_objectManager.GetObject(Wall2)->GetComponent<Transform>()->setRotation(glm::quat(0.5, 0.5, -0.5, 0.5));

	Wall3 = m_objectManager.CreateObject("Wall3");
	m_objectManager.GetObject(Wall3)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/Desk/gridwall.gltf");
	m_objectManager.GetObject(Wall3)->AddComponent<Transform>()->setPosition(glm::dvec3(17.4, 0.25, -6.5));
	m_objectManager.GetObject(Wall3)->Start();
	m_objectManager.GetObject(Wall3)->GetComponent<Transform>()->setScale(5);
	m_objectManager.GetObject(Wall3)->GetComponent<Transform>()->setRotation(glm::quat(0.5, 0.5, -0.5, 0.5));

	//Test 1 Init

	Ball = m_objectManager.CreateObject("Ball");
	Plank1 = m_objectManager.CreateObject("Plank 1");
	Plank2 = m_objectManager.CreateObject("Plank 2");

	m_objectManager.GetObject(Plank1)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/physicsblock.gltf");
	m_objectManager.GetObject(Plank2)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/physicsblock.gltf");
	m_objectManager.GetObject(Ball)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/physicsbullet.gltf");

	glm::mat4 offset = glm::mat4(1.0);
	offset = glm::translate(offset, glm::vec3(0.0, -0.3, -0.00685));
	m_objectManager.GetObject(Plank1)->AddComponent<Transform>()->setPosition(glm::dvec3(10.5, 2.66, -4));
	m_objectManager.GetObject(Plank1)->GetComponent<DrawableEntity>()->SetOffset(offset);
	m_objectManager.GetObject(Plank1)->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(0.02, 0.16, 0.1));
	m_objectManager.GetObject(Plank1)->Start();

	m_objectManager.GetObject(Plank2)->AddComponent<Transform>()->setPosition(glm::dvec3(11.5, 2.66, -4));
	m_objectManager.GetObject(Plank2)->GetComponent<DrawableEntity>()->SetOffset(offset);
	m_objectManager.GetObject(Plank2)->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(0.02, 0.16, 0.1));
	m_objectManager.GetObject(Plank2)->Start();

	glm::mat4 offset1 = glm::mat4(1.0);
	offset1 = glm::translate(offset1, glm::vec3(0.2075, -0.735, 0));
	offset1 = glm::scale(offset1, glm::vec3(2.5, 2.5, 2.5));
	m_objectManager.GetObject(Ball)->GetComponent<DrawableEntity>()->SetOffset(offset1);
	m_objectManager.GetObject(Ball)->AddComponent<Transform>()->setPosition(glm::dvec3(14, 2.75, -3.95));
	m_objectManager.GetObject(Ball)->AddComponent<SphereCollider>()->SetRadius(0.041);
	m_objectManager.GetObject(Ball)->Start();

	//Test 2 Init

	Ball2 = m_objectManager.CreateObject("Ball 2");
	Ball3 = m_objectManager.CreateObject("Ball 3");

	m_objectManager.GetObject(Ball2)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/physicsbullet.gltf");
	m_objectManager.GetObject(Ball3)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/physicsbullet.gltf");

	glm::mat4 offset2 = glm::mat4(1.0);
	offset2 = glm::translate(offset2, glm::vec3(0.2075, -0.735, 0));
	offset2 = glm::scale(offset2, glm::vec3(2.5, 2.5, 2.5));
	m_objectManager.GetObject(Ball2)->GetComponent<DrawableEntity>()->SetOffset(offset2);
	m_objectManager.GetObject(Ball2)->AddComponent<Transform>()->setPosition(glm::dvec3(10, 2.72, -7));
	m_objectManager.GetObject(Ball2)->AddComponent<SphereCollider>()->SetRadius(0.041);
	m_objectManager.GetObject(Ball2)->Start();


	glm::mat4 offset3 = glm::mat4(1.0);
	offset3 = glm::translate(offset3, glm::vec3(0.2075, -0.735, 0));
	offset3 = glm::scale(offset3, glm::vec3(2.5, 2.5, 2.5));
	m_objectManager.GetObject(Ball3)->GetComponent<DrawableEntity>()->SetOffset(offset3);
	m_objectManager.GetObject(Ball3)->AddComponent<Transform>()->setPosition(glm::dvec3(13, 2.70, -7));
	m_objectManager.GetObject(Ball3)->AddComponent<SphereCollider>()->SetRadius(0.041);
	m_objectManager.GetObject(Ball3)->Start();
	
	//Test 3 Init
	Plank3 = m_objectManager.CreateObject("Plank 3");
	Plank4 = m_objectManager.CreateObject("Plank 4");

	m_objectManager.GetObject(Plank3)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/physicsblock.gltf");
	m_objectManager.GetObject(Plank4)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/physicsblock.gltf");

	glm::mat4 offset4 = glm::mat4(1.0);
	offset4 = glm::translate(offset4, glm::vec3(0.0, -0.3, -0.00685));
	m_objectManager.GetObject(Plank3)->AddComponent<Transform>()->setPosition(glm::dvec3(11.5, 2.66, -10));
	m_objectManager.GetObject(Plank3)->GetComponent<DrawableEntity>()->SetOffset(offset4);
	m_objectManager.GetObject(Plank3)->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(0.02, 0.16, 0.1));
	m_objectManager.GetObject(Plank3)->Start();

	m_objectManager.GetObject(Plank4)->AddComponent<Transform>()->setPosition(glm::dvec3(12.7, 2.66, -10));
	m_objectManager.GetObject(Plank4)->GetComponent<DrawableEntity>()->SetOffset(offset4);
	m_objectManager.GetObject(Plank4)->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(0.02, 0.16, 0.1));
	m_objectManager.GetObject(Plank4)->Start();

	// COLLIDERS
	InitColliders();
	UIInputObject = m_objectManager.CreateObject();
	UIinput = m_objectManager.GetObject(UIInputObject)->AddComponent<Input>();

}

void PhysicsScene::Update(double frameRate)
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
		PhysicsTest2();
	}

	if (UIinput->GetKeyToggle(YOKAI_INPUT::NUM_3))
	{
		PhysicsTest3();
	}
}
void PhysicsScene::LateUpdate(double frameRate)
{
	m_objectManager.LateUpdate(frameRate);
}
void PhysicsScene::Draw()
{
	m_objectManager.Draw();
}
void PhysicsScene::Enable()
{
    isEnabled = true;
}

void PhysicsScene::Disable()
{
    isEnabled = false;
}

void PhysicsScene::InitColliders()
{
	for (int i = 0; i < 3; i++)
	{
		Colliders.push_back(m_objectManager.CreateObject());
	}
	int counter = 0;
	
	// Floor
	m_objectManager.GetObject(Colliders[counter])->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(20, 0.2, 20));
	m_objectManager.GetObject(Colliders[counter])->AddComponent<Transform>()->setPosition(glm::dvec3(15, 0, -15));
	m_objectManager.GetObject(Colliders[counter])->Start();
	m_objectManager.GetObject(Colliders[counter])->GetComponent<BoxCollider>()->StaticSet();
	++counter;

	// Left Wall
	m_objectManager.GetObject(Colliders[counter])->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(0.10, 5.0, 5.0));
	m_objectManager.GetObject(Colliders[counter])->AddComponent<Transform>()->setPosition(glm::dvec3(7.0, 0.25, -6.5));
	m_objectManager.GetObject(Colliders[counter])->Start();
	//m_objectManager.GetObject(Colliders[counter])->GetComponent<Transform>()->setRotation(glm::quat(0.966, 0, 0.259, 0));
	m_objectManager.GetObject(Colliders[counter])->GetComponent<BoxCollider>()->StaticSet();
	++counter;

	// Right Wall
	m_objectManager.GetObject(Colliders[counter])->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(0.10, 5.0, 5.0));
	m_objectManager.GetObject(Colliders[counter])->AddComponent<Transform>()->setPosition(glm::dvec3(17, 0.25, -6.5));
	m_objectManager.GetObject(Colliders[counter])->Start();
	//m_objectManager.GetObject(Colliders[counter])->GetComponent<Transform>()->setRotation(glm::quat(0.966, 0, -0.259, 0));
	m_objectManager.GetObject(Colliders[counter])->GetComponent<BoxCollider>()->StaticSet();
	++counter;

	//std::cout << counter;
}