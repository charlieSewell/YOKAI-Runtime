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
	unsigned int LectureTheatre;
	unsigned int LectureTheatreCeiling;
	unsigned int LectureTheatreExtras;
    //unsigned int ClearDesk;
    unsigned int Plank1;
    unsigned int Plank2;
    unsigned int Ball;
	unsigned int UIInputObject;
	std::shared_ptr<Input> UIinput;
    std::vector<unsigned int> Colliders;
	//colliders
    
    //GameObjectManager m_objectManager;

};
