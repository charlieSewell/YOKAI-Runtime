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
class CharliePhysics : public Scene
{
  public:

      CharliePhysics();
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
	
	void InitColliders();

    void PhysicsTest1();


    ///Is this scene active
    bool isEnabled = true;

	bool m_physicsOn;

	unsigned int Player;
    unsigned int Box;
    unsigned int Wall1;
    unsigned int Wall2;
    unsigned int Wall3;

    unsigned int Plank1;
    unsigned int Plank2;
    unsigned int Ball;

    unsigned int Plank3;
    unsigned int Plank4;

    unsigned int Ball2;
    unsigned int Ball3;

	unsigned int UIInputObject;
	std::shared_ptr<Input> UIinput;
    std::vector<unsigned int> Colliders;
};
