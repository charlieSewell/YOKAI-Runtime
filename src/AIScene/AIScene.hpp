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
    void Update(double deltaTime) override;

	void UpdateEmotionIcons(std::vector<unsigned int> actors, const int SIZE);

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

	// Object sizes will not be hard coded in later
	unsigned int Player;
	unsigned int UIInputObject;
	unsigned int House;

	std::vector<unsigned int> Zombies;
	std::vector<unsigned int> Dogs;
	std::vector<unsigned int> Blakes;
	std::vector<unsigned int> Cubes;
	std::map<unsigned int, unsigned int> Emotions;

	const int NUM_ZOMBIES = 5;
	const int NUM_DOGS = 5;
	const int NUM_BLAKES = 5;
	const int NUM_CUBES = 5;


	std::shared_ptr<Input> UIinput;
	//colliders
	 std::vector<unsigned int> Colliders;

};
