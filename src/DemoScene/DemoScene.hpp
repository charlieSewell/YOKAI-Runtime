#pragma once

#include "Controller/Layer.hpp"
#include "Model/GameObject.hpp"
#include "Model/Components/DrawableEntity.hpp"
#include "Controller/InputComponent.hpp"
//#include "Controller/UIManager.hpp"

/**
 * @class DemoScene
 * @brief A demo Scene for Assignment 1
 */
class DemoScene : public Layer
{
  public:

	DemoScene();
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

	bool m_physicsOn;

	GameObject Player;
	GameObject LectureTheatre;
    GameObject LectureTheatreCeiling;
    GameObject LectureTheatreExtras;
	GameObject UIInputObject;
	std::shared_ptr<Input> UIinput;

	//colliders
	GameObject FloorCollider;
	GameObject DeskCollider;

};
