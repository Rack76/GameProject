#include "ComponentManager.h"
#include "../ComponentTypes.h"
#include <cassert>

void ComponentManager::createComponent(int componentType)
{
    switch (componentType)
    {
    case GRAPHICS:
        graphicsComponents.push_back(new Graphics);
    case CAMERA:
        camera = new Camera();
    }
}

int ComponentManager::getComponentCount(int componentType)
{
    switch (componentType)
    {
    case GRAPHICS:
        return graphicsComponents.size();
    case CAMERA:
        return camera ? 1 : 0;
    }
}

Component* ComponentManager::getComponent(int componentType, int index)
{
    switch(componentType) {
    case GRAPHICS:
        if (index < graphicsComponents.size())
            return (Component*)(graphicsComponents[index]);
        else

            assert(false && "component index is out of bounds!");
    case CAMERA:
        return camera;
    }
}

void ComponentManager::cleanUp()
{
    for (auto component : graphicsComponents)
    {
        if(component)
            delete component;
    }
    graphicsComponents.clear();
    if (camera)
        delete camera;
}