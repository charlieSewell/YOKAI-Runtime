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
class PhysicsScene : public Scene
{
  public:

      PhysicsScene();
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
    void PhysicsTest2();
    void PhysicsTest3();

    void Throw();
    void Reset();

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
	//colliders
    
    //GameObjectManager m_objectManager;
    std::vector<int> bullets;
    int bulletCount = 0;
};
