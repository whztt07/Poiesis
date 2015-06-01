#include "poiesis/systems/InputSystem.h"

std::string InputSystem::GetName()
{
    return "InputSystem";
}

void InputSystem::Update(float dt)
{
    // Avoid warnings for not using dt.
    LOG_D("[RenderingSystem] Update: " << dt);

    if (!Engine::GetInstance().GetInputAdapter()->CheckInputOccurred(InputType::MousePress))
        return;

    auto entities = Engine::GetInstance().GetEntityManager()->GetAllEntitiesWithComponentOfClass("MoveableComponent");
    auto cameraEntities = Engine::GetInstance().GetEntityManager()->GetAllEntitiesWithComponentOfClass("CameraComponent");
    std::shared_ptr<MoveableComponent> moveableComponent;
    std::shared_ptr<ParticleComponent> particleComponent;
    float mouseX = Engine::GetInstance().GetInputAdapter()->GetMouseX();
    float mouseY = Engine::GetInstance().GetInputAdapter()->GetMouseY();
    Vector mousePosition(mouseX, mouseY);
    Vector particlePosition;
    Vector inputForce;
    Vector resultantForce;
    float distance;

    Vector cameraOffset;

    if (cameraEntities.size() > 0)
    {
        auto cameraComponent = std::static_pointer_cast<CameraComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(cameraEntities[0], "CameraComponent"));
        Vector screenOffset = Vector(CFG_GETI("WINDOW_WIDTH"), CFG_GETI("WINDOW_HEIGHT"))*0.5;
        cameraOffset = cameraComponent->GetPosition() - screenOffset;
    }

    mousePosition += cameraOffset;

    for (auto entity : entities)
    {
        moveableComponent = std::static_pointer_cast<MoveableComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "MoveableComponent"));
        particleComponent = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "ParticleComponent"));

        if (moveableComponent->GetActive())
        {
            particlePosition = particleComponent->GetPosition();
            distance = particlePosition.CalculateDistance(mousePosition);
            inputForce = mousePosition - particlePosition;
            inputForce.Normalize();
            inputForce *= -CFG_GETF("INPUT_FORCE")/(1 + distance); // Summing with 1 to avoid division by zero.
            resultantForce = inputForce + particleComponent->GetForce();
            particleComponent->SetForce(resultantForce);

            LOG_D("Particle position: " << particlePosition);
            LOG_D("Mouse position: " << mousePosition);
            LOG_D("Distance: " << distance);
            LOG_D("Force: " << inputForce);
            LOG_D("Resultant force: " << resultantForce);
        }
    }
}
