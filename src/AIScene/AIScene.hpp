#pragma once

#include "Engine/Scene.hpp"
#include "Engine/GameObject.hpp"
#include "Components/DrawableEntity.hpp"
#include "Components/InputComponent.hpp"
//#include "Engine/UIManager.hpp"

/**
 * @class DemoScene
 * @brief A demo Scene for Assignment 1
 */
class AIScene : public Scene
{
  public:

	  AIScene();
    /**
     * @brief Initialised the Scene
     */
    void Init() override;
	/**
	 * @brief Updates the Scene
	 */
    void Update(float frameRate) override;
    /**
     * @brief Draws the Scene
     */
    void Draw() override;
    /**
     * @brief Enables the Scene
     */
    void Enable() override;
    /**
     * @brief Disables the Scene
     */
    void Disable() override;
  private:
	
	void InitColliders();
    ///Is this scene active
    bool isEnabled = true;

	bool m_physicsOn = false;
	unsigned int Player;
	unsigned int Zombies[10];
	unsigned int UIInputObject;
	unsigned int Cube;
	unsigned int House;

	std::shared_ptr<Input> UIinput;
	//colliders
	 std::vector<unsigned int> Colliders;

};
