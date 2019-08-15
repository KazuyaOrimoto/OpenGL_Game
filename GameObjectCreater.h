#pragma once

#define GAME_OBJECT_CREATER GameObjectCreater::GetInstance()

class Game;

class GameObjectCreater
{
public:
    static GameObjectCreater* GetInstance() { return creater; }
    static void CreateInstance();
    static void DeleteInstance();

    void PlayerAndWallCreate(Game* game);


private:
    GameObjectCreater();
    ~GameObjectCreater();


    static GameObjectCreater* creater;
};

