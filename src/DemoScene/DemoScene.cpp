#include "DemoScene.hpp"
#include "Common/PlayerScript.hpp"
#include "Components/SphereCollider.hpp"
#include "Components/BoxCollider.hpp"
#include "Physics/Physics.hpp"
#include "glm/gtx/string_cast.hpp"
DemoScene::DemoScene()
{

}

void DemoScene::Init() 
{
	//m_lightManager.AddLight(glm::vec4{4.0f,3.0f,1.0f,1.0f},glm::vec4{0.0f},glm::vec4{0.0f,0.0f,0.0f,30.0f});
	//m_lightManager.AddLight(glm::vec4{4.0f,3.0f,1.0f,1.0f},glm::vec4{0.0f},glm::vec4{0.0f,0.0f,0.0f,30.0f});
	Player = m_objectManager.CreateObject("Player");
	m_objectManager.GetObject(Player)->AddComponent<PlayerScript>();
	m_objectManager.GetObject(Player)->GetComponent<Transform>()->setPosition(11, 3, 0);
	m_objectManager.GetObject(Player)->Start();

	//LectureTheatre = m_objectManager.CreateObject("LectureTheatre");
	LectureTheatreEmpty = m_objectManager.CreateObject("LectureTheatreEmpty");
	//LectureTheatreCeiling = m_objectManager.CreateObject();
	//LectureTheatreExtras = m_objectManager.CreateObject();
	//ClearDesk = objectManager.CreateObject();
	Ball = m_objectManager.CreateObject("Ball");
	Plank1 = m_objectManager.CreateObject("Plank 1");
	Plank2 = m_objectManager.CreateObject("Plank 2");
	Desk = m_objectManager.CreateObject("Desk");
	Laptop1 = m_objectManager.CreateObject("Laptop 1");
	Laptop2 = m_objectManager.CreateObject("Laptop 2");
	Microphone = m_objectManager.CreateObject("Microphone");
	Chair1 = m_objectManager.CreateObject("Chair 1");

	//m_objectManager.GetObject(LectureTheatre)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/LectureTheatreFinal/LectureTheatre.gltf");
	m_objectManager.GetObject(LectureTheatreEmpty)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/LectureTheatreFinal/LectureTheatre1.gltf");
	//m_objectManager.GetObject(LectureTheatreCeiling)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/ceiling.gltf");
	//m_objectManager.GetObject(LectureTheatreExtras)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/extras.gltf");
	//objectManager.GetObject(ClearDesk)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/cleardesk.gltf");
	m_objectManager.GetObject(Plank1)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/physicsblock.gltf");
	m_objectManager.GetObject(Plank2)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/physicsblock.gltf");
	m_objectManager.GetObject(Ball)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/physicsbullet.gltf");
	m_objectManager.GetObject(Desk)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/Desk/desk.gltf");
	m_objectManager.GetObject(Laptop1)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/Laptops/laptop1.gltf");
	m_objectManager.GetObject(Laptop2)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/Laptops/laptop2.gltf");
	m_objectManager.GetObject(Microphone)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/Desk/microphone.gltf");
	m_objectManager.GetObject(Chair1)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/Chairs/chair.gltf");

	//m_objectManager.GetObject(LectureTheatreCeiling)->Start();
	//m_objectManager.GetObject(LectureTheatreExtras)->Start();
	//m_objectManager.GetObject(LectureTheatre)->Start();	// This line only exists to add a transform. Should come up with a better solution
	m_objectManager.GetObject(LectureTheatreEmpty)->Start();
	//m_objectManager.GetObject(Desk)->Start();
	//m_objectManager.GetObject(Laptop1)->Start();
	//m_objectManager.GetObject(Laptop2)->Start();
	m_objectManager.GetObject(Microphone)->Start();
	m_objectManager.GetObject(Chair1)->Start();

	//m_objectManager.GetObject(LectureTheatre)->AddComponent<Transform>()->setPosition(glm::dvec3(18.92, 0.0, -8.580));
	m_objectManager.GetObject(LectureTheatreEmpty)->AddComponent<Transform>()->setPosition(glm::dvec3(18.92, 0.0, -8.580));
	//m_objectManager.GetObject(LectureTheatreEmpty)->AddComponent<Transform>()->setPosition(glm::dvec3(18.92, 0.0, -8.580));

	///////////////////////////////////////////////////////////////////////////////////
	// PHYSICS TESTING

	glm::mat4 offset = glm::mat4(1.0);
	offset = glm::translate(offset,glm::vec3(0.0,-0.3,-0.00685));
	m_objectManager.GetObject(Plank1)->AddComponent<Transform>()->setPosition(glm::dvec3(11, 2.66, -4));
	m_objectManager.GetObject(Plank1)->GetComponent<DrawableEntity>()->SetOffset(offset);
	m_objectManager.GetObject(Plank1)->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(0.02, 0.16, 0.1));
	m_objectManager.GetObject(Plank1)->Start();

	m_objectManager.GetObject(Plank2)->AddComponent<Transform>()->setPosition(glm::dvec3(13.5, 2.66, -4));
	m_objectManager.GetObject(Plank2)->GetComponent<DrawableEntity>()->SetOffset(offset);
	m_objectManager.GetObject(Plank2)->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(0.02, 0.16, 0.1));
	m_objectManager.GetObject(Plank2)->Start();

	m_objectManager.GetObject(Ball)->AddComponent<Transform>()->setPosition(glm::dvec3(16, 2.72, -4));
	m_objectManager.GetObject(Ball)->AddComponent<SphereCollider>()->SetRadius(0.05);
	m_objectManager.GetObject(Ball)->Start();

	
	glm::mat4 offset1 = glm::mat4(1.0);
	offset1 = glm::rotate(offset1, glm::radians(-90.0f), glm::vec3(0, 1, 0));
	m_objectManager.GetObject(Desk)->AddComponent<Transform>()->setPosition(glm::dvec3(12.375, 0.46, -3.8));
	m_objectManager.GetObject(Desk)->GetComponent<DrawableEntity>()->SetOffset(offset1);
	//m_objectManager.GetObject(Desk)->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(0.02, 0.16, 0.1));
	m_objectManager.GetObject(Desk)->Start();
	

	m_objectManager.GetObject(Laptop1)->AddComponent<Transform>()->setPosition(glm::dvec3(13.6, -1.35, -5.4));
	//m_objectManager.GetObject(Laptop1)->GetComponent<DrawableEntity>()->SetOffset(offset1);
	//m_objectManager.GetObject(Desk)->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(0.02, 0.16, 0.1));
	m_objectManager.GetObject(Laptop1)->Start();

	m_objectManager.GetObject(Laptop2)->AddComponent<Transform>()->setPosition(glm::dvec3(13.5, -1.35, -5.4));
	//m_objectManager.GetObject(Laptop1)->GetComponent<DrawableEntity>()->SetOffset(offset1);
	//m_objectManager.GetObject(Desk)->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(0.02, 0.16, 0.1));
	m_objectManager.GetObject(Laptop2)->Start();

	// COLLIDERS
	InitColliders();
	UIInputObject = m_objectManager.CreateObject();
	UIinput = m_objectManager.GetObject(UIInputObject)->AddComponent<Input>();

	//Physics testing
	m_objectManager.GetObject(Plank1)->GetComponent<BoxCollider>()->SetLinearVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Plank1)->GetComponent<BoxCollider>()->SetAngularVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Plank1)->GetComponent<BoxCollider>()->SetMass(2.0);
	m_objectManager.GetObject(Plank1)->GetComponent<BoxCollider>()->SetIsStaticObject(false);
	m_objectManager.GetObject(Plank1)->GetComponent<BoxCollider>()->SetInertiaTensor();
	m_objectManager.GetObject(Plank1)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(1, 0, 0, 0));
	//m_objectManager.GetObject(Plank1)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.707, 0, 0, 0.707));
	m_objectManager.GetObject(Plank1)->GetComponent<BoxCollider>()->SetGravityAffected(true);
	
	m_objectManager.GetObject(Plank1)->GetComponent<BoxCollider>()->SetCollisionCategory(Physics::CATEGORY2);
	m_objectManager.GetObject(Plank1)->GetComponent<BoxCollider>()->SetCollisionMaskBits(Physics::CATEGORY1 | Physics::CATEGORY2);
	
	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetLinearVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetAngularVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetMass(2.0);
	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetIsStaticObject(false);
	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetInertiaTensor();
	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(1.0, 0, 0, 0));
	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetCollisionCategory(Physics::CATEGORY2);
	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetCollisionMaskBits(Physics::CATEGORY1 | Physics::CATEGORY2);
	//m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.854, 0.354, -0.146, 0.354));
	m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetGravityAffected(true);

	m_objectManager.GetObject(Ball)->GetComponent<SphereCollider>()->SetLinearVelocity(glm::dvec3(0.5, 0, 0));
	m_objectManager.GetObject(Ball)->GetComponent<SphereCollider>()->SetAngularVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Ball)->GetComponent<SphereCollider>()->SetMass(2.0);
	m_objectManager.GetObject(Ball)->GetComponent<SphereCollider>()->SetIsStaticObject(false);
	m_objectManager.GetObject(Ball)->GetComponent<SphereCollider>()->SetInertiaTensor();
	m_objectManager.GetObject(Ball)->GetComponent<SphereCollider>()->SetOrientation(glm::quat(1, 0, 0, 0));
	
	m_objectManager.GetObject(Ball)->GetComponent<SphereCollider>()->SetCollisionCategory(Physics::CATEGORY2);
	m_objectManager.GetObject(Ball)->GetComponent<SphereCollider>()->SetCollisionMaskBits(Physics::CATEGORY1 | Physics::CATEGORY2);
	m_objectManager.GetObject(Ball)->GetComponent<SphereCollider>()->SetGravityAffected(true);
}

void DemoScene::Update(double frameRate)
{
	m_objectManager.Update(frameRate);
	//PhysicsSystem::getInstance().IsDebugEnabled(m_physicsOn);
	//m_physicsOn = true;
}
void DemoScene::LateUpdate(double frameRate)
{
	m_objectManager.LateUpdate(frameRate);
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
	for (int i = 0; i < 48; i++)
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
	

	// Desk
	//objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(1.00, 0.75, 0.5));
	m_objectManager.GetObject(Colliders[counter])->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(1.00, 0.5, 0.5));
	m_objectManager.GetObject(Colliders[counter])->AddComponent<Transform>()->setPosition(glm::dvec3(13.125, 0.5, -4.25));
	m_objectManager.GetObject(Colliders[counter])->Start();
	m_objectManager.GetObject(Colliders[counter])->GetComponent<BoxCollider>()->StaticSet();
	//m_objectManager.GetObject(Colliders)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.986, 0.165, 0.0, 0.0));
	++counter;

	// Left Stairs
	m_objectManager.GetObject(Colliders[counter])->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(20.00, 0.5, 11.0));
	m_objectManager.GetObject(Colliders[counter])->AddComponent<Transform>()->setPosition(glm::dvec3(9.75, 0.25, -10));
	m_objectManager.GetObject(Colliders[counter])->Start();
	m_objectManager.GetObject(Colliders[counter])->GetComponent<Transform>()->setRotation(glm::quat(0.986, 0.165, 0.003, -0.017));
	m_objectManager.GetObject(Colliders[counter])->GetComponent<BoxCollider>()->StaticSet();
	++counter;

	// Left Wall
	m_objectManager.GetObject(Colliders[counter])->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(0.10, 5.0, 5.0));
	m_objectManager.GetObject(Colliders[counter])->AddComponent<Transform>()->setPosition(glm::dvec3(7.0, 0.25, -6.5));
	m_objectManager.GetObject(Colliders[counter])->Start();
	m_objectManager.GetObject(Colliders[counter])->GetComponent<Transform>()->setRotation(glm::quat(0.966, 0, 0.259, 0));
	m_objectManager.GetObject(Colliders[counter])->GetComponent<BoxCollider>()->StaticSet();
	++counter;
	// Right Wall
	m_objectManager.GetObject(Colliders[counter])->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(0.10, 5.0, 5.0));
	m_objectManager.GetObject(Colliders[counter])->AddComponent<Transform>()->setPosition(glm::dvec3(18.5, 0.25, -6.5));
	m_objectManager.GetObject(Colliders[counter])->Start();
	m_objectManager.GetObject(Colliders[counter])->GetComponent<Transform>()->setRotation(glm::quat(0.966, 0, -0.259, 0));
	m_objectManager.GetObject(Colliders[counter])->GetComponent<BoxCollider>()->StaticSet();
	++counter;
	

	// Back Wall
	m_objectManager.GetObject(Colliders[counter])->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(5.0, 5.0, 0.10));
	m_objectManager.GetObject(Colliders[counter])->AddComponent<Transform>()->setPosition(glm::dvec3(12, 0.25, -1.775));
	m_objectManager.GetObject(Colliders[counter])->Start();
	m_objectManager.GetObject(Colliders[counter])->GetComponent<BoxCollider>()->StaticSet();
	++counter;
	for(int i=0; i<14; ++i)
	{
		float y = 0.32 * i;
		float z = -1 * i;

		float extX = 0.3 * i;

		// To acount for diamond shape of rows
		if(i > 7)
			extX -= (0.21 * (i-7)) * 1.5;	// don't think about it lol
		m_objectManager.GetObject(Colliders[counter])->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(2.2 + extX, 0.55, 0.20));
		m_objectManager.GetObject(Colliders[counter])->AddComponent<Transform>()->setPosition(glm::dvec3(13.125, 0.1 + y, -8.75 + z));
		m_objectManager.GetObject(Colliders[counter])->Start();
		m_objectManager.GetObject(Colliders[counter])->GetComponent<BoxCollider>()->StaticSet();
		++counter;
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
		m_objectManager.GetObject(Colliders[counter])->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(1.35 + extX, 0.55, 0.20));
		m_objectManager.GetObject(Colliders[counter])->AddComponent<Transform>()->setPosition(glm::dvec3(8.0 + x, 0.1 + y, -7.75 + z));
		m_objectManager.GetObject(Colliders[counter])->Start();
		m_objectManager.GetObject(Colliders[counter])->GetComponent<Transform>()->setRotation(glm::quat(0.991, 0, 0.131, 0));
		m_objectManager.GetObject(Colliders[counter])->GetComponent<BoxCollider>()->StaticSet();
		++counter;
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
		m_objectManager.GetObject(Colliders[counter])->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(1.35 + extX, 0.55, 0.20));
		m_objectManager.GetObject(Colliders[counter])->AddComponent<Transform>()->setPosition(glm::dvec3(18.25 + x, 0.1 + y, -7.75 + z));
		m_objectManager.GetObject(Colliders[counter])->Start();
		m_objectManager.GetObject(Colliders[counter])->GetComponent<Transform>()->setRotation(glm::quat(0.991, 0, -0.131, 0));
		m_objectManager.GetObject(Colliders[counter])->GetComponent<BoxCollider>()->StaticSet();
		++counter;
	}

	std::cout << counter;
}