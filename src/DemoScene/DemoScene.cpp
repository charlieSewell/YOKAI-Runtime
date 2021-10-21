#include "DemoScene.hpp"
#include "Common/PlayerScript.hpp"
#include "Components/SphereCollider.hpp"
#include "Components/BoxCollider.hpp"

DemoScene::DemoScene()
{

}

void DemoScene::Init() 
{
	Player = m_objectManager.CreateObject();
	m_objectManager.GetObject(Player)->AddComponent<PlayerScript>();
	m_objectManager.GetObject(Player)->Start();

	LectureTheatre = m_objectManager.CreateObject();
	LectureTheatreCeiling = m_objectManager.CreateObject();
	LectureTheatreExtras = m_objectManager.CreateObject();
	//ClearDesk = objectManager.CreateObject();
	Bullet = m_objectManager.CreateObject();
	Plank = m_objectManager.CreateObject();
	Plank2 = m_objectManager.CreateObject();

	//objectManager.GetObject(LectureTheatre)->AddComponent<DrawableEntity>()->LoadModel("content/sponza/sponza.obj");
	m_objectManager.GetObject(LectureTheatre)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/please.gltf");
	m_objectManager.GetObject(LectureTheatreCeiling)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/ceiling.gltf");
	m_objectManager.GetObject(LectureTheatreExtras)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/extras.gltf");
	//objectManager.GetObject(ClearDesk)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/cleardesk.gltf");
	m_objectManager.GetObject(Bullet)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/physicsbullet.gltf");
	m_objectManager.GetObject(Plank)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/physicsblock.gltf");
	m_objectManager.GetObject(Plank2)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/physicsblock.gltf");

	m_objectManager.GetObject(LectureTheatreCeiling)->Start();
	m_objectManager.GetObject(LectureTheatreExtras)->Start();
	m_objectManager.GetObject(LectureTheatre)->Start();	// This line only exists to add a transform. Should come up with a better solution

	///////////////////////////////////////////////////////////////////////////////////
	// PHYSICS TESTING

	/*
	objectManager.GetObject(ClearDesk)->Start();
	objectManager.GetObject(ClearDesk)->AddComponent<Transform>()->setPosition(glm::vec3(5, 0.65, 12));
	objectManager.GetObject(ClearDesk)->Start();
	objectManager.GetObject(ClearDesk)->GetComponent<Transform>()->rotate(90, glm::vec3(0, 1, 0));
	objectManager.GetObject(ClearDesk)->Start();
	*/

	m_objectManager.GetObject(Bullet)->AddComponent<Transform>()->setPosition(glm::vec3(13, 0.675, -4));
	m_objectManager.GetObject(Bullet)->Start();

	//objectManager.GetObject(Plank)->AddComponent<Transform>()->setPosition(glm::vec3(12.5, 0.675 + 0.2, -4));
	m_objectManager.GetObject(Plank)->AddComponent<Transform>()->setPosition(glm::vec3(12.5, 0.675 + 0.5, -4 + 0.009));
	m_objectManager.GetObject(Plank)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(0.02, 0.16, 0.1));
	//objectManager.GetObject(Plank)->AddComponent<Transform>()->setPosition(glm::vec3(12.5, 0.675 + 0.5, -4 + 0.009));
	m_objectManager.GetObject(Plank)->Start();

	m_objectManager.GetObject(Plank2)->AddComponent<Transform>()->setPosition(glm::vec3(14, 0.675 + 0.5, -4 + 0.009));
	m_objectManager.GetObject(Plank2)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(0.02, 0.16, 0.1));
	m_objectManager.GetObject(Plank2)->Start();
	
	///////////////////////////////////////////////////////////////////////////////////

	//objectManager.GetObject(LectureTheatre)->GetComponent<Transform>()->scale(0.1);
	
	//unsigned int obj = objectManager.CreateObject();
	//objectManager.GetObject(obj)->AddComponent<DrawableEntity>()->LoadModel("content/Zombie/ZombieSmooth.gltf");
	//objectManager.GetObject(obj)->Start();

	// COLLIDERS
	InitColliders();
	UIInputObject = m_objectManager.CreateObject();
	UIinput = m_objectManager.GetObject(UIInputObject)->AddComponent<Input>();

	//Physics testing
	//objectManager.GetObject(Plank)->GetComponent<BoxCollider>()->getCollisionBody()->setLinearVelocity(glm::vec3(0.001, 0, 0));
	m_objectManager.GetObject(Plank)->GetComponent<BoxCollider>()->setLinearVelocity(glm::dvec3(0.001, 0, 0));
	m_objectManager.GetObject(Plank)->GetComponent<BoxCollider>()->setAngularVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Plank)->GetComponent<BoxCollider>()->setMass(2);
	m_objectManager.GetObject(Plank)->GetComponent<BoxCollider>()->setCentreOfMass(m_objectManager.GetObject(Plank)->GetComponent<Transform>()->getPosition());
	m_objectManager.GetObject(Plank)->GetComponent<BoxCollider>()->setIsStaticObject(false);
	m_objectManager.GetObject(Plank)->GetComponent<BoxCollider>()->setInertiaTensor();
	//glm::mat3x3 temp1 = YokaiPhysics::RectangleInertiaTensor(objectManager.GetObject(Plank)->GetComponent<BoxCollider>()->getExtents(), objectManager.GetObject(Plank)->GetComponent<BoxCollider>()->getMass());
	//objectManager.GetObject(Plank)->GetComponent<BoxCollider>()->setInertiaTensor(temp1);

	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->setLinearVelocity(glm::dvec3(-0.001, 0, 0));
	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->setAngularVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->setMass(2);
	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->setCentreOfMass(m_objectManager.GetObject(Plank2)->GetComponent<Transform>()->getPosition());
	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->setIsStaticObject(false);
	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->setInertiaTensor();
	//glm::mat3x3 temp2 = YokaiPhysics::RectangleInertiaTensor(objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->getExtents(), objectManager.GetObject(Plank)->GetComponent<BoxCollider>()->getMass());
	//objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->setInertiaTensor(temp2);
}

void DemoScene::Update(float frameRate)
{
    m_objectManager.Update(frameRate);
	PhysicsSystem::getInstance().IsDebugEnabled(m_physicsOn);
	//PhysicsSystem::getInstance().RendererUpdate();
	//m_physicsOn = UIinput->GetKeyToggle(YOKAI_INPUT::F);
	m_physicsOn = true;

	//PLANK 1
	glm::vec3 temp;
	temp.x = m_objectManager.GetObject(Plank)->GetComponent<Transform>()->getPosition().x;
	temp.y = m_objectManager.GetObject(Plank)->GetComponent<Transform>()->getPosition().y;
	temp.z = m_objectManager.GetObject(Plank)->GetComponent<Transform>()->getPosition().z;

	glm::vec3 lv;
	//lv = objectManager.GetObject(Plank)->GetComponent<BoxCollider>()->getCollisionBody()->getLinearVelocity();
	lv = m_objectManager.GetObject(Plank)->GetComponent<BoxCollider>()->getLinearVelocity();

	//lv = glm::dvec3(0.001, 0, 0);

	m_objectManager.GetObject(Plank)->GetComponent<Transform>()->translate(lv);
	//objectManager.GetObject(Plank)->GetComponent<Transform>()->setRotation(glm::quat(0, 0, 0, 0));
	m_objectManager.GetObject(Plank)->GetComponent<BoxCollider>()->SetPosition(temp);
	
	
	//PLANK 2
	glm::vec3 temp2;
	temp2.x = m_objectManager.GetObject(Plank2)->GetComponent<Transform>()->getPosition().x;
	temp2.y = m_objectManager.GetObject(Plank2)->GetComponent<Transform>()->getPosition().y;
	temp2.z = m_objectManager.GetObject(Plank2)->GetComponent<Transform>()->getPosition().z;

	glm::vec3 lv2;
	//lv = objectManager.GetObject(Plank)->GetComponent<BoxCollider>()->getCollisionBody()->getLinearVelocity();
	lv2 = m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->getLinearVelocity();

	//lv = glm::dvec3(0.001, 0, 0);

	m_objectManager.GetObject(Plank2)->GetComponent<Transform>()->translate(lv2);
	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetPosition(temp2);
	//
}

void DemoScene::Draw()
{
	m_objectManager.Draw();
}
void DemoScene::Enable()
{
    isEnabled = true;
}

void DemoScene::Disable()
{
    isEnabled = false;
}

void DemoScene::InitColliders()
{
	Colliders = m_objectManager.CreateObject();
	
	// Floor
	m_objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(20, 0.4, 20));
	m_objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(15, 0, -15));
	m_objectManager.GetObject(Colliders)->Start();
	m_objectManager.GetObject(Colliders)->GetComponent<BoxCollider>()->setIsStaticObject(true);

	// Desk
	//objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(1.00, 0.75, 0.5));
	m_objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(1.00, 0.5, 0.5));
	m_objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(13.125, 0.5, -4.25));
	m_objectManager.GetObject(Colliders)->Start();
	m_objectManager.GetObject(Colliders)->GetComponent<BoxCollider>()->setIsStaticObject(true);

	// Left Stairs
	m_objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(20.00, 0.5, 11.0));
	m_objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(9.75, 0.25, -10));
	m_objectManager.GetObject(Colliders)->Start();
	m_objectManager.GetObject(Colliders)->GetComponent<BoxCollider>()->setIsStaticObject(true);

	//FloorCollider.GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.970, 0.171, 0.171, 0.030));
	m_objectManager.GetObject(Colliders)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.986, 0.165, 0.0, 0.0));

	// Left Wall
	m_objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(0.10, 5.0, 5.0));
	m_objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(7.0, 0.25, -6.5));
	m_objectManager.GetObject(Colliders)->Start();
	m_objectManager.GetObject(Colliders)->GetComponent<BoxCollider>()->setIsStaticObject(true);
	m_objectManager.GetObject(Colliders)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.966, 0, 0.259, 0));

	// Right Wall
	m_objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(0.10, 5.0, 5.0));
	m_objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(18.5, 0.25, -6.5));
	m_objectManager.GetObject(Colliders)->Start();
	m_objectManager.GetObject(Colliders)->GetComponent<BoxCollider>()->setIsStaticObject(true);
	m_objectManager.GetObject(Colliders)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.966, 0, -0.259, 0));

	// Back Wall
	m_objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(5.0, 5.0, 0.10));
	m_objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(12, 0.25, -1.775));
	m_objectManager.GetObject(Colliders)->Start();
	m_objectManager.GetObject(Colliders)->GetComponent<BoxCollider>()->setIsStaticObject(true);

	// Middle rows
	for(int i=0; i<14; ++i)
	{
		float y = 0.32 * i;
		float z = -1 * i;

		float extX = 0.3 * i;

		// To acount for diamond shape of rows
		if(i > 7)
			extX -= (0.21 * (i-7)) * 1.5;	// don't think about it lol

		m_objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(2.2 + extX, 0.55, 0.20));
		m_objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(13.125, 0.1 + y, -8.75 + z));
		m_objectManager.GetObject(Colliders)->Start();
		m_objectManager.GetObject(Colliders)->GetComponent<BoxCollider>()->setIsStaticObject(true);

	}

	// Left rows
	for (int i = 0; i < 14; ++i)
	{
		// offsets
		float x = -0.3 * i;
		float y = 0.32 * i;
		float z = -1 * i;

		float extX = -0.01 * i;

		// To account for shorter rows at top and bottom
		if(i == 0)
			extX = -0.85;

		if (i == 13)
			x -= 1;

		// To acount for diamond shape of rows
		if (i > 7)
			x += 0.325 * (i-7);

		m_objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(1.35 + extX, 0.55, 0.20));
		m_objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(8.0 + x, 0.1 + y, -7.75 + z));
		m_objectManager.GetObject(Colliders)->Start();
		m_objectManager.GetObject(Colliders)->GetComponent<BoxCollider>()->setIsStaticObject(true);
		m_objectManager.GetObject(Colliders)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.991, 0, 0.131, 0));
	}

	// Right rows
	for (int i = 0; i < 14; ++i)
	{
		// offsets
		float x = +0.3 * i;
		float y = 0.32 * i;
		float z = -1 * i;

		float extX = -0.01 * i;

		// To account for shorter rows at top and bottom
		if (i == 0)
			extX = -0.85;

		if (i == 13)
			x += 1;

		// To acount for diamond shape of rows
		if (i > 7)
			x -= 0.325 * (i - 7);

		m_objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(1.35 + extX, 0.55, 0.20));
		m_objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(18.25 + x, 0.1 + y, -7.75 + z));
		m_objectManager.GetObject(Colliders)->Start();
		m_objectManager.GetObject(Colliders)->GetComponent<BoxCollider>()->setIsStaticObject(true);
		m_objectManager.GetObject(Colliders)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.991, 0, -0.131, 0));

		// Floor
		m_objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(20, 0.4, 1.5));
		m_objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(15, 3.8, -22.125));
		m_objectManager.GetObject(Colliders)->Start();
		m_objectManager.GetObject(Colliders)->GetComponent<BoxCollider>()->setIsStaticObject(true);

		//Physics testing
		//objectManager.GetObject(Colliders)->GetComponent<BoxCollider>()->setS(true);
	}
}