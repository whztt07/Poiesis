// Systems processes entities with specific components and give life to the
// game.

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <memory>
#include <string>

#include "bandit/core/entity/EntityManager.h"

class System
{
  public:
    System() {}
    System(std::shared_ptr<EntityManager> entityManager) : entityManager(entityManager) {}
    virtual ~System() {}

    // Gets human-readable system name.
    virtual std::string GetName() = 0;

    // Processes entities and components.
    virtual void Update(float dt) = 0;

  protected:
    std::shared_ptr<EntityManager> entityManager;
};

#endif // SYSTEM_H_