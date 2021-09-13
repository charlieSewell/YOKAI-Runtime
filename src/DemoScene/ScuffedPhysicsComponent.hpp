//
// Created by charl on 7/09/2021.
//

#pragma once
#include "Model/Component.hpp"
#include "Model/GameObject.hpp"

#include "Model/Components/Transform.hpp"
#include "Model/Components/DrawableEntity.hpp"
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



