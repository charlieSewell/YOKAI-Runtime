#pragma once

#include "Engine/Scene.hpp"
#include "Engine/GameObject.hpp"
#include "Components/DrawableEntity.hpp"
#include "Components/InputComponent.hpp"
//#include "Engine/UIManager.hpp"
//#include "Physics/ResolutionFunctions.hpp"

/**
 * @class DemoScene
 * @brief A demo Scene for Assignment 1
 */

constexpr int NUM_BALLS = 10;

class ConnorsPhysicsScene : public Scene
{
  public:

      ConnorsPhysicsScene();
    /**
     * @brief Initialised the Scene
     */
    void Init() override;
    /**
     * @brief Updates the Scene before physics simulation
     */
    void Update(double frameRate) override;
    /**
     * @brief Updates the Scene After physics simulation
     */
    void LateUpdate(double frameRate);
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

    void Reset();

	void Shoot();


    ///Is this scene active
    bool isEnabled = true;

	bool m_physicsOn;

	unsigned int Player;

    unsigned int Plank1;
    unsigned int Plank2;
	unsigned int Table;
    unsigned int Ball[NUM_BALLS];
	unsigned int ballIndex = 0;
	unsigned int UIInputObject;
	std::shared_ptr<Input> UIinput;
};
