#pragma once

#include "Controller/Layer.hpp"
//#include "Controller/UIManager.hpp"

/**
 * @class DemoScene
 * @brief A demo Scene for Assignment 1
 */
class DemoScene : public Layer
{
  public:
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

    ///Is this scene active
    bool isEnabled = true;

};