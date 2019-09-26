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
	int i = rand() % ObstacleMap::MAP_QTY;
	return mapDocments[i];
}

void ObstacleMapLoder::Initialize()
{
	std::string fileName;
	rapidjson::Document* data = nullptr;
	for (int i = 1; i <= ObstacleMap::MAP_QTY; i++)
	{
		data = new rapidjson::Document();
		char mapNum = '0' + i;
		fileName = "MapData/map";
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
