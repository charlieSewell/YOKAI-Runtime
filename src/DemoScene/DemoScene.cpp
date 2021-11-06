#include "DemoScene.hpp"
#include "Common/PlayerScript.hpp"
#include "Components/SphereCollider.hpp"
#include "Components/BoxCollider.hpp"
#include "Physics/Physics.hpp"
#include "glm/gtx/string_cast.hpp"
DemoScene::DemoScene()
{
	m_sceneName = "LectureTheatre";
}

void DemoScene::Init() 
{
	Player = m_objectManager.CreateObject("Player");
	m_objectManager.GetObject(Player)->AddComponent<PlayerScript>();
	m_objectManager.GetObject(Player)->GetComponent<Transform>()->SetPosition(11, 3, 0);
	m_objectManager.GetObject(Player)->Start();

	LectureTheatreEmpty = m_objectManager.CreateObject("LectureTheatreEmpty");
	Desk = m_objectManager.CreateObject("Desk");
	Laptop1 = m_objectManager.CreateObject("Laptop 1");
	Laptop2 = m_objectManager.CreateObject("Laptop 2");
	Chair1 = m_objectManager.CreateObject("Chair 1");
	Chair2 = m_objectManager.CreateObject("Chair 2");
	Chair3 = m_objectManager.CreateObject("Chair 3");
	Chair4 = m_objectManager.CreateObject("Chair 4");
	Chair5 = m_objectManager.CreateObject("Chair 5");
	Chair6 = m_objectManager.CreateObject("Chair 6");

	m_objectManager.GetObject(LectureTheatreEmpty)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/LectureTheatreFinal/LectureTheatre1.gltf");
	m_objectManager.GetObject(Desk)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/Desk/desk.gltf");
	m_objectManager.GetObject(Laptop1)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/Laptops/laptop1.gltf");
	m_objectManager.GetObject(Laptop2)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/Laptops/laptop1.gltf");
	m_objectManager.GetObject(Chair1)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/Chairs/chair.gltf");
	m_objectManager.GetObject(Chair2)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/Chairs/chair.gltf");
	m_objectManager.GetObject(Chair3)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/Chairs/chair.gltf");
	m_objectManager.GetObject(Chair4)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/Chairs/chair.gltf");
	m_objectManager.GetObject(Chair5)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/Chairs/chair.gltf");
	m_objectManager.GetObject(Chair6)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/Chairs/chair.gltf");

	m_objectManager.GetObject(LectureTheatreEmpty)->Start();
	m_objectManager.GetObject(LectureTheatreEmpty)->AddComponent<Transform>()->SetPosition(glm::dvec3(18.92, 0.0, -8.580));

	glm::mat4 offset1 = glm::mat4(1.0);
	offset1 = glm::rotate(offset1, glm::radians(-90.0f), glm::vec3(0, 1, 0));
	m_objectManager.GetObject(Desk)->AddComponent<Transform>()->SetPosition(glm::dvec3(12.375, 0.46, -3.8));
	m_objectManager.GetObject(Desk)->GetComponent<DrawableEntity>()->SetOffset(offset1);
	m_objectManager.GetObject(Desk)->Start();
	
	glm::mat4 offset2 = glm::mat4(1.0);
	offset2 = glm::translate(offset2, glm::vec3(0.7, -2.3, -1.05));
	m_objectManager.GetObject(Laptop1)->AddComponent<Transform>()->SetPosition(glm::dvec3(12.8, 0.95, -4.3));
	m_objectManager.GetObject(Laptop1)->GetComponent<DrawableEntity>()->SetOffset(offset2);
	m_objectManager.GetObject(Laptop1)->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(0.15, 0.15, 0.15));
	m_objectManager.GetObject(Laptop1)->Start();

	m_objectManager.GetObject(Laptop2)->AddComponent<Transform>()->SetPosition(glm::dvec3(12.4, 0.95, -4.3));
	m_objectManager.GetObject(Laptop2)->GetComponent<DrawableEntity>()->SetOffset(offset2);
	m_objectManager.GetObject(Laptop2)->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(0.15, 0.15, 0.15));
	m_objectManager.GetObject(Laptop2)->Start();

	glm::mat4 offset3 = glm::mat4(1.0);
	//offset3 = glm::translate(offset3, glm::vec3(2.5, -0.375, 3.25));
	offset3 = glm::translate(offset3, glm::vec3(1.8, -0.345, 2.4));
	offset3 = glm::rotate(offset3, glm::radians(-45.0f), glm::vec3(0, 1, 0));
	offset3 = glm::scale(offset3, glm::vec3(0.75, 0.75, 0.75));
	m_objectManager.GetObject(Chair1)->AddComponent<Transform>()->SetPosition(glm::dvec3(8, 0.4, -6.5));
	m_objectManager.GetObject(Chair1)->GetComponent<DrawableEntity>()->SetOffset(offset3);
	m_objectManager.GetObject(Chair1)->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(0.25, 0.4, 0.25));
	m_objectManager.GetObject(Chair1)->Start();
	m_objectManager.GetObject(Chair1)->GetComponent<Transform>()->SetRotation(glm::quat(0.966, 0, 0.259, 0));

	m_objectManager.GetObject(Chair2)->AddComponent<Transform>()->SetPosition(glm::dvec3(8.4, 0.4, -5.8));
	m_objectManager.GetObject(Chair2)->GetComponent<DrawableEntity>()->SetOffset(offset3);
	m_objectManager.GetObject(Chair2)->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(0.25, 0.4, 0.25));
	m_objectManager.GetObject(Chair2)->Start();
	m_objectManager.GetObject(Chair2)->GetComponent<Transform>()->SetRotation(glm::quat(0.966, 0, 0.259, 0));

	m_objectManager.GetObject(Chair3)->AddComponent<Transform>()->SetPosition(glm::dvec3(8.8, 0.4, -5.1));
	m_objectManager.GetObject(Chair3)->GetComponent<DrawableEntity>()->SetOffset(offset3);
	m_objectManager.GetObject(Chair3)->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(0.25, 0.4, 0.25));
	m_objectManager.GetObject(Chair3)->Start();
	m_objectManager.GetObject(Chair3)->GetComponent<Transform>()->SetRotation(glm::quat(0.966, 0, 0.259, 0));

	m_objectManager.GetObject(Chair4)->AddComponent<Transform>()->SetPosition(glm::dvec3(9.2, 0.4, -4.4));
	m_objectManager.GetObject(Chair4)->GetComponent<DrawableEntity>()->SetOffset(offset3);
	m_objectManager.GetObject(Chair4)->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(0.25, 0.4, 0.25));
	m_objectManager.GetObject(Chair4)->Start();
	m_objectManager.GetObject(Chair4)->GetComponent<Transform>()->SetRotation(glm::quat(0.966, 0, 0.259, 0));

	glm::mat4 offset4 = glm::mat4(1.0);
	offset4 = glm::translate(offset4, glm::vec3(1.8, -0.345, 2.4));
	offset4 = glm::rotate(offset4, glm::radians(-45.0f), glm::vec3(0, 1, 0));
	offset4 = glm::scale(offset4, glm::vec3(0.75, 0.75, 0.75));
	m_objectManager.GetObject(Chair5)->AddComponent<Transform>()->SetPosition(glm::dvec3(17.8, 0.4, -6.5));
	m_objectManager.GetObject(Chair5)->GetComponent<DrawableEntity>()->SetOffset(offset4);
	m_objectManager.GetObject(Chair5)->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(0.25, 0.4, 0.25));
	m_objectManager.GetObject(Chair5)->Start();
	m_objectManager.GetObject(Chair5)->GetComponent<Transform>()->SetRotation(glm::quat(-0.259, 0, -0.966, 0));

	m_objectManager.GetObject(Chair6)->AddComponent<Transform>()->SetPosition(glm::dvec3(17.4, 0.4, -5.8));
	m_objectManager.GetObject(Chair6)->GetComponent<DrawableEntity>()->SetOffset(offset4);
	m_objectManager.GetObject(Chair6)->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(0.25, 0.4, 0.25));
	m_objectManager.GetObject(Chair6)->Start();
	m_objectManager.GetObject(Chair6)->GetComponent<Transform>()->SetRotation(glm::quat(-0.259, 0, -0.966, 0));

	// COLLIDERS
	InitColliders();
	UIInputObject = m_objectManager.CreateObject();
	UIinput = m_objectManager.GetObject(UIInputObject)->AddComponent<Input>();

	m_objectManager.GetObject(Laptop1)->GetComponent<BoxCollider>()->SetLinearVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Laptop1)->GetComponent<BoxCollider>()->SetAngularVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Laptop1)->GetComponent<BoxCollider>()->SetMass(1.0);
	m_objectManager.GetObject(Laptop1)->GetComponent<BoxCollider>()->SetIsStaticObject(false);
	m_objectManager.GetObject(Laptop1)->GetComponent<BoxCollider>()->SetInertiaTensor();
	m_objectManager.GetObject(Laptop1)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(1.0, 0, 0, 0));
	m_objectManager.GetObject(Laptop1)->GetComponent<BoxCollider>()->SetCollisionCategory(Physics::CATEGORY2);
	m_objectManager.GetObject(Laptop1)->GetComponent<BoxCollider>()->SetCollisionMaskBits(Physics::CATEGORY1 | Physics::CATEGORY2);
	m_objectManager.GetObject(Laptop1)->GetComponent<BoxCollider>()->SetGravityAffected(true);

	m_objectManager.GetObject(Laptop2)->GetComponent<BoxCollider>()->SetLinearVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Laptop2)->GetComponent<BoxCollider>()->SetAngularVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Laptop2)->GetComponent<BoxCollider>()->SetMass(1.0);
	m_objectManager.GetObject(Laptop2)->GetComponent<BoxCollider>()->SetIsStaticObject(false);
	m_objectManager.GetObject(Laptop2)->GetComponent<BoxCollider>()->SetInertiaTensor();
	m_objectManager.GetObject(Laptop2)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(1.0, 0, 0, 0));
	m_objectManager.GetObject(Laptop2)->GetComponent<BoxCollider>()->SetCollisionCategory(Physics::CATEGORY2);
	m_objectManager.GetObject(Laptop2)->GetComponent<BoxCollider>()->SetCollisionMaskBits(Physics::CATEGORY1 | Physics::CATEGORY2);
	m_objectManager.GetObject(Laptop2)->GetComponent<BoxCollider>()->SetGravityAffected(true);

	m_objectManager.GetObject(Chair1)->GetComponent<BoxCollider>()->SetLinearVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Chair1)->GetComponent<BoxCollider>()->SetAngularVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Chair1)->GetComponent<BoxCollider>()->SetMass(4.0);
	m_objectManager.GetObject(Chair1)->GetComponent<BoxCollider>()->SetIsStaticObject(false);
	m_objectManager.GetObject(Chair1)->GetComponent<BoxCollider>()->SetInertiaTensor();
	m_objectManager.GetObject(Chair1)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(1.0, 0, 0, 0));
	m_objectManager.GetObject(Chair1)->GetComponent<BoxCollider>()->SetCollisionCategory(Physics::CATEGORY2);
	m_objectManager.GetObject(Chair1)->GetComponent<BoxCollider>()->SetCollisionMaskBits(Physics::CATEGORY1 | Physics::CATEGORY2);
	m_objectManager.GetObject(Chair1)->GetComponent<BoxCollider>()->SetGravityAffected(true);

	m_objectManager.GetObject(Chair2)->GetComponent<BoxCollider>()->SetLinearVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Chair2)->GetComponent<BoxCollider>()->SetAngularVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Chair2)->GetComponent<BoxCollider>()->SetMass(4.0);
	m_objectManager.GetObject(Chair2)->GetComponent<BoxCollider>()->SetIsStaticObject(false);
	m_objectManager.GetObject(Chair2)->GetComponent<BoxCollider>()->SetInertiaTensor();
	m_objectManager.GetObject(Chair2)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(1.0, 0, 0, 0));
	m_objectManager.GetObject(Chair2)->GetComponent<BoxCollider>()->SetCollisionCategory(Physics::CATEGORY2);
	m_objectManager.GetObject(Chair2)->GetComponent<BoxCollider>()->SetCollisionMaskBits(Physics::CATEGORY1 | Physics::CATEGORY2);
	m_objectManager.GetObject(Chair2)->GetComponent<BoxCollider>()->SetGravityAffected(true);

	m_objectManager.GetObject(Chair3)->GetComponent<BoxCollider>()->SetLinearVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Chair3)->GetComponent<BoxCollider>()->SetAngularVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Chair3)->GetComponent<BoxCollider>()->SetMass(4.0);
	m_objectManager.GetObject(Chair3)->GetComponent<BoxCollider>()->SetIsStaticObject(false);
	m_objectManager.GetObject(Chair3)->GetComponent<BoxCollider>()->SetInertiaTensor();
	m_objectManager.GetObject(Chair3)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(1.0, 0, 0, 0));
	m_objectManager.GetObject(Chair3)->GetComponent<BoxCollider>()->SetCollisionCategory(Physics::CATEGORY2);
	m_objectManager.GetObject(Chair3)->GetComponent<BoxCollider>()->SetCollisionMaskBits(Physics::CATEGORY1 | Physics::CATEGORY2);
	m_objectManager.GetObject(Chair3)->GetComponent<BoxCollider>()->SetGravityAffected(true);

	m_objectManager.GetObject(Chair4)->GetComponent<BoxCollider>()->SetLinearVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Chair4)->GetComponent<BoxCollider>()->SetAngularVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Chair4)->GetComponent<BoxCollider>()->SetMass(4.0);
	m_objectManager.GetObject(Chair4)->GetComponent<BoxCollider>()->SetIsStaticObject(false);
	m_objectManager.GetObject(Chair4)->GetComponent<BoxCollider>()->SetInertiaTensor();
	m_objectManager.GetObject(Chair4)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(1.0, 0, 0, 0));
	m_objectManager.GetObject(Chair4)->GetComponent<BoxCollider>()->SetCollisionCategory(Physics::CATEGORY2);
	m_objectManager.GetObject(Chair4)->GetComponent<BoxCollider>()->SetCollisionMaskBits(Physics::CATEGORY1 | Physics::CATEGORY2);
	m_objectManager.GetObject(Chair4)->GetComponent<BoxCollider>()->SetGravityAffected(true);

	m_objectManager.GetObject(Chair5)->GetComponent<BoxCollider>()->SetLinearVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Chair5)->GetComponent<BoxCollider>()->SetAngularVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Chair5)->GetComponent<BoxCollider>()->SetMass(4.0);
	m_objectManager.GetObject(Chair5)->GetComponent<BoxCollider>()->SetIsStaticObject(false);
	m_objectManager.GetObject(Chair5)->GetComponent<BoxCollider>()->SetInertiaTensor();
	m_objectManager.GetObject(Chair5)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(1.0, 0, 0, 0));
	m_objectManager.GetObject(Chair5)->GetComponent<BoxCollider>()->SetCollisionCategory(Physics::CATEGORY2);
	m_objectManager.GetObject(Chair5)->GetComponent<BoxCollider>()->SetCollisionMaskBits(Physics::CATEGORY1 | Physics::CATEGORY2);
	m_objectManager.GetObject(Chair5)->GetComponent<BoxCollider>()->SetGravityAffected(true);

	m_objectManager.GetObject(Chair6)->GetComponent<BoxCollider>()->SetLinearVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Chair6)->GetComponent<BoxCollider>()->SetAngularVelocity(glm::dvec3(0, 0, 0));
	m_objectManager.GetObject(Chair6)->GetComponent<BoxCollider>()->SetMass(4.0);
	m_objectManager.GetObject(Chair6)->GetComponent<BoxCollider>()->SetIsStaticObject(false);
	m_objectManager.GetObject(Chair6)->GetComponent<BoxCollider>()->SetInertiaTensor();
	m_objectManager.GetObject(Chair6)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(1.0, 0, 0, 0));
	m_objectManager.GetObject(Chair6)->GetComponent<BoxCollider>()->SetCollisionCategory(Physics::CATEGORY2);
	m_objectManager.GetObject(Chair6)->GetComponent<BoxCollider>()->SetCollisionMaskBits(Physics::CATEGORY1 | Physics::CATEGORY2);
	m_objectManager.GetObject(Chair6)->GetComponent<BoxCollider>()->SetGravityAffected(true);
}

void DemoScene::Update(double frameRate)
{
	m_objectManager.Update(frameRate);
	if(UIinput->GetKeyState(YOKAI_INPUT::G))
	{
		YOKAI_PARSE::SaveScene("content/LectureTheatre.json", m_objectManager, m_lightManager);
	}
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
	m_objectManager.GetObject(Colliders[counter])->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(20, 0.1, 20));
	m_objectManager.GetObject(Colliders[counter])->AddComponent<Transform>()->SetPosition(glm::dvec3(15, 0, -15));
	m_objectManager.GetObject(Colliders[counter])->Start();
	m_objectManager.GetObject(Colliders[counter])->GetComponent<BoxCollider>()->StaticSet();
	++counter;
	

	// Desk
	//objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(1.00, 0.75, 0.5));
	m_objectManager.GetObject(Colliders[counter])->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(1.00, 0.5, 0.5));
	m_objectManager.GetObject(Colliders[counter])->AddComponent<Transform>()->SetPosition(glm::dvec3(13.125, 0.3, -4.25));
	m_objectManager.GetObject(Colliders[counter])->Start();
	m_objectManager.GetObject(Colliders[counter])->GetComponent<BoxCollider>()->StaticSet();
	//m_objectManager.GetObject(Colliders)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.986, 0.165, 0.0, 0.0));
	++counter;

	// Left Stairs
	m_objectManager.GetObject(Colliders[counter])->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(20.00, 0.5, 11.0));
	m_objectManager.GetObject(Colliders[counter])->AddComponent<Transform>()->SetPosition(glm::dvec3(9.75, 0.25, -10));
	m_objectManager.GetObject(Colliders[counter])->Start();
	m_objectManager.GetObject(Colliders[counter])->GetComponent<Transform>()->SetRotation(glm::quat(0.986, 0.165, 0.003, -0.017));
	m_objectManager.GetObject(Colliders[counter])->GetComponent<BoxCollider>()->StaticSet();
	++counter;

	// Left Wall
	m_objectManager.GetObject(Colliders[counter])->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(0.10, 5.0, 5.0));
	m_objectManager.GetObject(Colliders[counter])->AddComponent<Transform>()->SetPosition(glm::dvec3(7.0, 0.25, -6.5));
	m_objectManager.GetObject(Colliders[counter])->Start();
	m_objectManager.GetObject(Colliders[counter])->GetComponent<Transform>()->SetRotation(glm::quat(0.966, 0, 0.259, 0));
	m_objectManager.GetObject(Colliders[counter])->GetComponent<BoxCollider>()->StaticSet();
	++counter;
	// Right Wall
	m_objectManager.GetObject(Colliders[counter])->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(0.10, 5.0, 5.0));
	m_objectManager.GetObject(Colliders[counter])->AddComponent<Transform>()->SetPosition(glm::dvec3(18.5, 0.25, -6.5));
	m_objectManager.GetObject(Colliders[counter])->Start();
	m_objectManager.GetObject(Colliders[counter])->GetComponent<Transform>()->SetRotation(glm::quat(0.966, 0, -0.259, 0));
	m_objectManager.GetObject(Colliders[counter])->GetComponent<BoxCollider>()->StaticSet();
	++counter;
	

	// Back Wall
	m_objectManager.GetObject(Colliders[counter])->AddComponent<BoxCollider>()->SetExtents(glm::dvec3(5.0, 5.0, 0.10));
	m_objectManager.GetObject(Colliders[counter])->AddComponent<Transform>()->SetPosition(glm::dvec3(12, 0.25, -1.775));
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
		m_objectManager.GetObject(Colliders[counter])->AddComponent<Transform>()->SetPosition(glm::dvec3(13.125, 0.1 + y, -8.75 + z));
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
		m_objectManager.GetObject(Colliders[counter])->AddComponent<Transform>()->SetPosition(glm::dvec3(8.0 + x, 0.1 + y, -7.75 + z));
		m_objectManager.GetObject(Colliders[counter])->Start();
		m_objectManager.GetObject(Colliders[counter])->GetComponent<Transform>()->SetRotation(glm::quat(0.991, 0, 0.131, 0));
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
		m_objectManager.GetObject(Colliders[counter])->AddComponent<Transform>()->SetPosition(glm::dvec3(18.25 + x, 0.1 + y, -7.75 + z));
		m_objectManager.GetObject(Colliders[counter])->Start();
		m_objectManager.GetObject(Colliders[counter])->GetComponent<Transform>()->SetRotation(glm::quat(0.991, 0, -0.131, 0));
		m_objectManager.GetObject(Colliders[counter])->GetComponent<BoxCollider>()->StaticSet();
		++counter;
	}

}