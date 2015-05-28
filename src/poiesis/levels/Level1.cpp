#include "poiesis/levels/Level1.h"

void Level1::Start()
{
    LOG_I("[Level1] Starting");
    
    EntityFactory::CreateBackground();
    EntityFactory::CreateCell(1, Vector(400, 300));
    EntityFactory::CreateCell(1, Vector(410, 310));
    EntityFactory::CreateFood(Vector(700, 300));

    Random r;
    float x;
    float y;
    for (int i = 0; i < 0; ++i)
    {
        x = r.GenerateFloat(0, 1000);
        y = r.GenerateFloat(0, 1000);
        EntityFactory::CreateCell(1, Vector(x, y));
    }

    // Engine::GetInstance().AddSystem(std::make_shared<FoodSpawningSystem>());
    // Engine::GetInstance().AddSystem(std::make_shared<GrowthSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<InputSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<CollisionSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<ParticleSystem>());
}

void Level1::Update()
{
    LOG_D("[Level1] Updating");
}

void Level1::Finish()
{
    LOG_I("[Level1] Finishing");
}