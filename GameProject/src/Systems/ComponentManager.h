#pragma once

#include <vector>
#include "../Components/Graphics.h"
#include <memory>

class ComponentManager
{
public:
	void init();
	void createComponent(int componentType);
	int getComponentCount(int componentType);
	Graphics* getComponent(int componentType, int index);
private:
	std::vector<Graphics*> graphicsComponents;
	int componentTypeCount[1];
};