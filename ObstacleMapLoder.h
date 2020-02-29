//=============================================================================
//	@file	ObstacleMapLoder.h
//	@brief	障害物のマップを外部ファイルから読み込む
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#pragma once
#include <vector>
#include <document.h>

namespace ObstacleMap
{
	const int MAP_QTY = 27;
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
	int mapNum;
};

