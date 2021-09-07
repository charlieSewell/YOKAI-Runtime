//
// Created by charl on 7/09/2021.
//

#include "ScuffedPhysicsComponent.hpp"
#include "Controller/Yokai.hpp"

ScuffedPhysicsComponent::ScuffedPhysicsComponent(GameObject* parent) : Component(parent){}

void ScuffedPhysicsComponent::Start()
{
    //This is cursed i know it is cursed i dont rlly give a fuck react made me do it
    if(m_parent->GetComponent<Transform>() == nullptr) {
        m_parent->AddComponent<Transform>();
    }

    m_parent->GetComponent<Transform>()->setPosition(50,0,50);
    modelID = m_parent->GetComponent<DrawableEntity>()->GetModelID();
    Model* model = Yokai::getInstance().getModelManager()->GetModel(modelID);
    std::vector<Mesh>::iterator mesh;
    std::vector<std::vector<float>> height;
    height.resize(100);
    modelID = m_parent->GetComponent<DrawableEntity>()->GetModelID();
    int meshCount =0;
    for(auto& vec : height)
    {
        vec.resize(100);
    }
    for(mesh = model->getMeshes()->begin(); mesh != model->getMeshes()->end(); ++mesh) {
        std::vector<Vertex>::iterator vertice;

        for (vertice = mesh->getVertices()->begin(); vertice != mesh->getVertices()->end(); ++vertice) {

            glm::vec4 temp = m_parent->GetComponent<Transform>()->getMatrix() * mesh->getTransform() * glm::vec4(vertice->position,1.0);

            if(height.at(static_cast<int>(temp.x)).at(static_cast<int>(temp.z)) != 0)
            {
                if(height.at(static_cast<int>(temp.x)).at(static_cast<int>(temp.z)) <= temp.y)
                {
                    height.at(static_cast<int>(temp.x)).at(static_cast<int>(temp.z)) = temp.y;
                }
            }
            else
            {
                height.at(static_cast<int>(temp.x)).at(static_cast<int>(temp.z)) = temp.y;
            }
        }
    }
    colliderID = PhysicsSystem::getInstance().addTerrainShape(3,m_parent->GetComponent<Transform>().get(),height);
}

void ScuffedPhysicsComponent::Update(float deltaTime)
{

}