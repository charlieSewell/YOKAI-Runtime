# Add source files.
target_sources(${PROJECT_NAME} PRIVATE
        main.cpp
		DemoScene/DemoScene.cpp
		Common/PlayerScript.cpp

		AIScene/AIScene.cpp
		AIScene/AIScripts/ZombieScript.cpp
		AIScene/AIScripts/DogScript.cpp
		AIScene/AIScripts/BlakeScript.cpp
		AIScene/AIScripts/CubeScript.cpp		
		AIScene/AIComponents/EmotionSystem.cpp
		AIScene/AIComponents/AffordanceSystem.cpp
		AIScene/AIComponents/PickupAffordance.cpp
		AIScene/AIComponents/BiteAffordance.cpp

		LightingScene/LightingScene.cpp

		PhysicsScene/PhysicsScene.cpp
)

# Include project header files.
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
