#include "PLayerScript.hpp"

PlayerScript::PlayerScript(GameObject* parent)
	: 
	Component(parent),
	player(parent),
	camera(player->AddComponent<Camera>()),
	playerControlledMotion(player->AddComponent<PlayerControlledMotion>())

{
	Awake();
}

void PlayerScript::Awake()
{
	playerControlledMotion->registerAllMovement(camera->m_frontDirection, camera->m_upDirection, camera->m_position);
}

void PlayerScript::Start()
{

}

void PlayerScript::Update(float deltaTime)
{

}

void PlayerScript::Draw()
{

}