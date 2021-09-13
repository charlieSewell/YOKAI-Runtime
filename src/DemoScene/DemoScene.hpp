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

	unsigned int Player;
	unsigned int LectureTheatre;
  unsigned int LectureTheatreCeiling;
  unsigned int LectureTheatreExtras;
	unsigned int UIInputObject;
	std::shared_ptr<Input> UIinput;

	//colliders
	unsigned int FloorCollider;
	unsigned int DeskCollider;

};
