#include "NPCScript.hpp"
#include "Components/BoxCollider.hpp"

NPCScript::NPCScript(GameObject* parent)
	:
	Component(parent),
	gameObject(parent),
	transform(gameObject->AddComponent<Transform>()),
	sphereCollider(gameObject->AddComponent<SphereCollider>()),
	rayCaster(gameObject->AddComponent<RayCaster>()),
	automatedBehaviours(gameObject->AddComponent<AutomatedBehaviours>()),
	affordanceSystem(gameObject->AddComponent<AffordanceSystem>())
{
	Awake();
}


void NPCScript::Awake()
{
	gameObject->AddComponent<DrawableEntity>()->LoadModel("content/aiScene/models/Zombie/ZombieSmooth.gltf");
	transform->setScale(0.25);
	sphereCollider->SetRadius(1.0);
	rayCaster->setOwnColliderID(sphereCollider->GetColliderID());

	//std::function<void(glm::vec3)> setPosition = [&](glm::vec3 newPosition) { transform->setPosition(newPosition); };
	//affordanceSystem->AddAffordance<PickupAffordance>()->EnableAffordance(setPosition);

	std::function<glm::vec3()> getPosition = [&]() { return transform->getPosition(); };
	std::function<glm::vec3()> getHeading = [&]() { return automatedBehaviours->Heading; };
	affordanceSystem->AddAffordance<PickupAffordance>()->EnableAbility(getPosition, getHeading);
	affordanceSystem->GetAffordance<PickupAffordance>()->PickUpOffset = 1;
}

void NPCScript::Start()
{
	automatedBehaviours->RotationSpeed = 0.05;
}

void NPCScript::Update(float deltaTime)
{
	int fakeState = 0;

	std::shared_ptr<GameObject> otherObject;
	int objectID = automatedBehaviours->frontFeelerHit;
	if (objectID != -1)
	{
		otherObject = GetAISceneObject(objectID);
		if (otherObject->GetComponent<AffordanceSystem>() != nullptr)
		{
			if (otherObject->GetComponent<AffordanceSystem>()->GetAffordance<PickupAffordance>() != nullptr)
			{
				fakeState = CheckPickup(otherObject);
			}
		}
	}

	if(!fakeState)
	{
		automatedBehaviours->wander();
	}

	automatedBehaviours->accelerate(0.015);
	sphereCollider->SetPosition(glm::vec3(transform->getPosition().x, transform->getPosition().y + 1, transform->getPosition().z));
}

void NPCScript::Draw()
{

}

bool NPCScript::CheckPickup(std::shared_ptr<GameObject> otherObject)
{
	std::shared_ptr<PickupAffordance> pickupAffordance = affordanceSystem->GetAffordance<PickupAffordance>();
	std::shared_ptr<PickupAffordance> otherPickupAffordance = otherObject->GetComponent<AffordanceSystem>()->GetAffordance<PickupAffordance>();

	if (otherPickupAffordance != nullptr)
	{
		if (pickupAffordance->HasAbility && otherPickupAffordance->IsAvailable && !pickupAffordance->IsActive)
		{
			// Object we want is directly in front so set this to avoid front collision detection
			automatedBehaviours->frontFeelerHit = -1;
			automatedBehaviours->feelerLeftHit = -1;
			automatedBehaviours->feelerRightHit = -1;
			automatedBehaviours->seek(otherObject->GetComponent<Transform>()->getPosition());

			if (glm::distance(transform->getPosition(), otherObject->GetComponent<Transform>()->getPosition()) < 2)
			{
				pickupAffordance->Interact(otherPickupAffordance);

				int otherColliderID = 0;
				if(otherObject->GetComponent<BoxCollider>() != nullptr)
				{
					rayCaster->setExcludedColliderID(otherObject->GetComponent<BoxCollider>()->GetColliderID());
				}
				else if(otherObject->GetComponent<SphereCollider>() != nullptr)
				{
					rayCaster->setExcludedColliderID(otherObject->GetComponent<SphereCollider>()->GetColliderID());
				}
			}

			return true;
		}
		else if (pickupAffordance->IsActive)
		{
			// logic to drop box
			//pickupAffordance->Stop();
			//rayCaster->setExcludedColliderID(-1);
		}
	}

	return false;
}