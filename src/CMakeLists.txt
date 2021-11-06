# Add source files.
target_sources(${PROJECT_NAME} PRIVATE
        main.cpp
		Common/PlayerScript.cpp
		CharliePhysics/CharliePhysics.cpp
)

# Include project header files.
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
