#pragma once

#include <vector>
#include "../Components/Graphics.h"
#include "../Components/Camera.h"
#include <memory>

class ComponentManager
{
public:
	ComponentManager() {
	
	}
	void init();
	void createComponent(int componentType);
	int getComponentCount(int componentType);
	Component* getComponent(int componentType, int index = 0);
	void cleanUp();
private:
	std::vector<Graphics*> graphicsComponents;
	Camera* camera;
	int componentTypeCount[1];
};