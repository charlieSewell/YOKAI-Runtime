# Add source files.
target_sources(${PROJECT_NAME} PRIVATE
        main.cpp
		DemoScene/DemoScene.cpp
		Common/PlayerScript.cpp
		AIScene/NPCScript.cpp
		AIScene/AIScene.cpp
		LightingScene/LightingScene.cpp
)

# Include project header files.
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
