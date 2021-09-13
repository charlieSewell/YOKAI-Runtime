//
// Created by charl on 7/09/2021.
//

#pragma once
#include "Components/Component.hpp"
#include "Engine/GameObject.hpp"

#include "Components/Transform.hpp"
#include "Components/DrawableEntity.hpp"
class ScuffedPhysicsComponent : public Component{
public:
    ScuffedPhysicsComponent(GameObject* parent);
    void Start();
    void Update(float deltaTime);
	Transform UpdateTransform;
private:
    unsigned int colliderID;
    unsigned int modelID;
    std::vector<float> heights;
};



