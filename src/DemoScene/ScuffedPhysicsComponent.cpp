//
// Created by charl on 7/09/2021.
//

#include "ScuffedPhysicsComponent.hpp"
#include "Controller/Yokai.hpp"

ScuffedPhysicsComponent::ScuffedPhysicsComponent(GameObject* parent)
	: Component(parent), UpdateTransform()
{

}

void ScuffedPhysicsComponent::Start()
{
    //This is cursed i know it is cursed i dont rlly give a fuck react made me do it
    if(m_parent->GetComponent<Transform>() == nullptr) {
        m_parent->AddComponent<Transform>();
    }

    m_parent->GetComponent<Transform>()->setPosition(0,0,26);
    modelID = m_parent->GetComponent<DrawableEntity>()->GetModelID();
    std::shared_ptr<Model> model = Yokai::getInstance().getModelManager()->GetModel(modelID);
    std::vector<Mesh>::iterator mesh;
    std::vector<std::vector<float>> height;
    height.resize(100);
    modelID = m_parent->GetComponent<DrawableEntity>()->GetModelID();
    for(auto& vec : height)
    {
        vec.resize(100);
    }
    for(mesh = model->getMeshes()->begin(); mesh != model->getMeshes()->end(); ++mesh) {
        std::vector<Vertex>::iterator vertice;

        for (vertice = mesh->getVertices()->begin(); vertice != mesh->getVertices()->end(); ++vertice) {

            glm::vec4 temp = m_parent->GetComponent<Transform>()->getMatrix() * mesh->getTransform() * glm::vec4(vertice->position,1.0);

            if(height.at(static_cast<int>(temp.z)).at(static_cast<int>(temp.x)) != 0)
            {
                if(height.at(static_cast<int>(temp.x)).at(static_cast<int>(temp.z)) <= temp.y)
                {
                    height.at(static_cast<int>(temp.x)).at(static_cast<int>(temp.z)) = temp.y;
                }
            }
            else
            {
                height.at(static_cast<int>(temp.z)).at(static_cast<int>(temp.x)) = temp.y;
            }
        }
    }
    for(auto& x : height)
    {
        for(auto& y : x)
        {
			//std::cout << y << ", ";
			if(y == 0)
				y = 5;
        } 
        //std::cout << std::endl;
    }
    m_parent->GetComponent<Transform>()->setPosition(0,0,26);
    colliderID = PhysicsSystem::getInstance().addTerrainShape(m_parent->GetObjectID(), &UpdateTransform, height);
}

void ScuffedPhysicsComponent::Update(float deltaTime)
{

}