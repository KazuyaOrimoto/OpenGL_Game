#include "Mesh.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"
#include <fstream>
#include <sstream>
#include <document.h>
#include <SDL_log.h>
#include "Math.h"

Mesh::Mesh()
    : vertexArray(nullptr)
    , radius(0.0f)
    , specPower(100.0f)
{
}

Mesh::~Mesh()
{
}

/**
@brief  メッシュデータの読み込み
@param	ロードしたいメッシュのファイル名
@param	Rendererクラスのポインタ
@return true : 成功 , false : 失敗
*/
bool Mesh::Load(const std::string & argFileName, Renderer* argRenderer)
{
    std::ifstream file(argFileName);
    if (!file.is_open())
    {
        SDL_Log("File not found: Mesh %s", argFileName.c_str());
        return false;
    }

    std::stringstream fileStream;
    fileStream << file.rdbuf();
    std::string contents = fileStream.str();
    rapidjson::StringStream jsonStr(contents.c_str());
    rapidjson::Document doc;
    doc.ParseStream(jsonStr);

    if (!doc.IsObject())
    {
        SDL_Log("Mesh %s is not valid json", argFileName.c_str());
        return false;
    }

    int ver = doc["version"].GetInt();

    // バージョンのチェック
    if (ver != 1)
    {
        SDL_Log("Mesh %s not version 1", argFileName.c_str());
        return false;
    }

	shaderName = doc["shader"].GetString();

    // Skip the vertex format/shader for now
    // (This is changed in a later chapter's code)
    size_t vertSize = 8;

    // テクスチャのロード
    const rapidjson::Value& readTextures = doc["textures"];
    if (!readTextures.IsArray() || readTextures.Size() < 1)
    {
        SDL_Log("Mesh %s has no textures, there should be at least one", argFileName.c_str());
        return false;
    }

	specPower = static_cast<float>(doc["specularPower"].GetDouble());

    for (rapidjson::SizeType i = 0; i < readTextures.Size(); i++)
    {
        // すでにロードされたテクスチャじゃないか調べる
        std::string texName = readTextures[i].GetString();
        Texture* t = argRenderer->GetTexture(texName);
        if (t == nullptr)
        {
            // テクスチャをロードする
            t = argRenderer->GetTexture(texName);
            if (t == nullptr)
            {
                // テクスチャがロードできなかった場合、デフォルトのテクスチャを使用
                t = argRenderer->GetTexture("Assets/Default.png");
            }
        }
		textures.emplace_back(t);
    }

    // 頂点配列データをロード
    const rapidjson::Value& vertsJson = doc["vertices"];
    if (!vertsJson.IsArray() || vertsJson.Size() < 1)
    {
        SDL_Log("Mesh %s has no vertices", argFileName.c_str());
        return false;
    }

    std::vector<float> vertices;
    vertices.reserve(vertsJson.Size() * vertSize);
	radius = 0.0f;
    for (rapidjson::SizeType i = 0; i < vertsJson.Size(); i++)
    {
        // 今のところは８つの要素とする
        const rapidjson::Value& vert = vertsJson[i];
        if (!vert.IsArray() || vert.Size() != 8)
        {
            SDL_Log("Unexpected vertex format for %s", argFileName.c_str());
            return false;
        }

        Vector3 pos(vert[0].GetFloat(), vert[1].GetFloat(), vert[2].GetFloat());
		radius = Math::Max(radius, pos.LengthSq());

        // float型で要素を追加
        for (rapidjson::SizeType i = 0; i < vert.Size(); i++)
        {
            vertices.emplace_back(static_cast<float>(vert[i].GetDouble()));
        }
    }

    // 半径を2乗する
	radius = Math::Sqrt(radius);

    // 要素配列データのロード
    const rapidjson::Value& indJson = doc["indices"];
    if (!indJson.IsArray() || indJson.Size() < 1)
    {
        SDL_Log("Mesh %s has no indices", argFileName.c_str());
        return false;
    }

    std::vector<unsigned int> indices;
    indices.reserve(indJson.Size() * 3);
    for (rapidjson::SizeType i = 0; i < indJson.Size(); i++)
    {
        const rapidjson::Value& ind = indJson[i];
        if (!ind.IsArray() || ind.Size() != 3)
        {
            SDL_Log("Invalid indices for %s", argFileName.c_str());
            return false;
        }

        indices.emplace_back(ind[0].GetUint());
        indices.emplace_back(ind[1].GetUint());
        indices.emplace_back(ind[2].GetUint());
    }

    // ここでVertexArrayクラスの作成
	vertexArray = new VertexArray(vertices.data(), static_cast<unsigned>(vertices.size()) / vertSize,
        indices.data(), static_cast<unsigned>(indices.size()));
    return true;
}

/**
@brief  ロードしたメッシュデータの解放
*/
void Mesh::Unload()
{
    delete vertexArray;
	vertexArray = nullptr;
}

/**
@brief  テクスチャのGetter
*/
Texture* Mesh::GetTexture(size_t argIndex)
{
    if (argIndex < textures.size())
    {
        return textures[argIndex];
    }
    else
    {
        return nullptr;
    }
}
