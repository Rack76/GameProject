#include "ComponentManager.h"
#include "../ComponentTypes.h"
#include <cassert>

void ComponentManager::init() {
    componentTypeCount[GRAPHICS] = 0;
}

void ComponentManager::createComponent(int componentType)
{
    switch (componentType)
    {
    case GRAPHICS:
        graphicsComponents.push_back(new Graphics);
    }
}

int ComponentManager::getComponentCount(int componentType)
{
    switch (componentType)
    {
    case GRAPHICS:
        return graphicsComponents.size();
    }
}

Graphics* ComponentManager::getComponent(int componentType, int index)
{
    if(index < graphicsComponents.size())
        return graphicsComponents[index];
    else

        assert(false && "component index is out of bounds!");
}
