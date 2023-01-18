#pragma once

class EntityManager
{
public:
	int getEntityCount(const char* componentType);
private:
	int entityCount = 0;
};