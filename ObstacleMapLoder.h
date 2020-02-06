#pragma once
#include <vector>
#include <document.h>

namespace ObstacleMap
{
	const int MAP_QTY = 1;
}

class ObstacleMapLoder
{
public:
	ObstacleMapLoder();
	~ObstacleMapLoder();

	rapidjson::Document* GetRandamMap();

private:
	void Initialize();
	void LoadMap(const std::string & argFileName, rapidjson::Document* doc);

	std::vector<rapidjson::Document*> mapDocments;
};

