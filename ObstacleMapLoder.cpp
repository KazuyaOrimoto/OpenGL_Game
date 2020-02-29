//=============================================================================
//	@file	ObstacleMapLoder.cpp
//	@brief	障害物のマップを外部ファイルから読み込む
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#include "ObstacleMapLoder.h"
#include <fstream>
#include <sstream>
#include <document.h>
#include <string>
#include "Game.h"

ObstacleMapLoder::ObstacleMapLoder()
{
	Initialize();
}

ObstacleMapLoder::~ObstacleMapLoder()
{
}

rapidjson::Document* ObstacleMapLoder::GetRandamMap()
{
	mapNum++;
	if (mapNum >= ObstacleMap::MAP_QTY)
	{
		return nullptr;
	}
	return mapDocments[mapNum];
}

void ObstacleMapLoder::Initialize()
{
	mapNum = -1;
	std::string fileName;
	rapidjson::Document* data = nullptr;
	for (int i = 1; i <= ObstacleMap::MAP_QTY; i++)
	{
		data = new rapidjson::Document();
		std::string mapNum = std::to_string(i);
		fileName = "MapData/Stage";
		fileName = fileName + mapNum;
		fileName = fileName + ".json";
		LoadMap(fileName,data);
		mapDocments.push_back(data);
	}
}

void ObstacleMapLoder::LoadMap(const std::string & _fileName, rapidjson::Document* _doc)
{
	std::ifstream file(_fileName);
	if (!file.is_open())
	{
		SDL_Log("File not found: Map %s", _fileName.c_str());
		return ;
	}

	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	rapidjson::StringStream jsonStr(contents.c_str());
	(*_doc).ParseStream(jsonStr);

}
