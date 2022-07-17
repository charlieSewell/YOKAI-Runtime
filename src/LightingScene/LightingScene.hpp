#pragma once

#include "Engine/Scene.hpp"
#include "Engine/GameObject.hpp"
#include "Components/DrawableEntity.hpp"
#include "Components/InputComponent.hpp"
#include <random>
//#include "Engine/UIManager.hpp"

/**
 * @class LightingScene
 * @brief A demo Scene for Assignment 1
 */
class LightingScene : public Scene
{
  public:

	LightingScene();
    /**
     * @brief Initialised the Scene
     */
    void Init() override;
	  /**
	  * @brief Updates the Scene
	  */
    void Update(double deltaTime) override;
    /**
	  * @brief Updates the Scene
	  */
    void LateUpdate(double deltaTime) override;
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
    ///Is this scene active
    bool isEnabled = true;

	bool m_physicsOn;

	unsigned int Player;
	unsigned int Scene;
	unsigned int UIInputObject;

	std::shared_ptr<Input> UIinput;
  PointLight RandomLight();

};
