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
class DemoScene : public Scene
{
  public:

	DemoScene();
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

    ///Is this scene active
    bool isEnabled = true;

	bool m_physicsOn;

	unsigned int Player;
    unsigned int LectureTheatreEmpty;

    unsigned int Desk;
    unsigned int Laptop1;
    unsigned int Laptop2;
    unsigned int Chair1;
    unsigned int Chair2;
    unsigned int Chair3;
    unsigned int Chair4;
    unsigned int Chair5;
    unsigned int Chair6;

	unsigned int UIInputObject;
	std::shared_ptr<Input> UIinput;
    std::vector<unsigned int> Colliders;
	//colliders
    
    //GameObjectManager m_objectManager;

};
