#pragma once

#include <glew.h>
#include <string>
#include "Math.h"

class Shader
{
public:
    Shader();
    ~Shader();
	/**
	@brief	頂点シェーダーとフラグメントシェーダーのロード
	@param	頂点シェーダーのファイル名
	@param	頂点シェーダーのファイル名
	@return	true : 成功 , false : 失敗
	*/
	bool Load(const std::string& vertName,const std::string& fragName);
	/**
	@brief	ロードしたシェーダーの解放
	*/
	void Unload();

	/**
	@brief	シェーダープログラムをアクティブにする
	*/
	void SetActive();

	/**
	@brief	行列のUniform変数を設定する
	@param	設定するUniform変数名
	@param	設定する行列
	*/
	void SetMatrixUniform(const char* name , const Matrix4& matrix);

    /**
    @brief	Vector3のUniform変数を設定する
    @param	設定するUniform変数名
    @param	設定するVector3
    */
    void SetVectorUniform(const char* name, const Vector3& vector);

    /**
    @brief	floatのUniform変数を設定する
    @param	設定するUniform変数名
    @param	設定するfloat
    */
    void SetFloatUniform(const char* name, const float& value);

private:
	/**
	@brief	シェーダーをコンパイルする
	@param	コンパイルするシェーダーのファイル名
	@param	シェーダーの種類
	@param	シェーダーのID用の参照変数
	@return	true : 成功 , false : 失敗
	*/
	bool CompileShader(const std::string& fileName,GLenum shaderType,GLuint& outShader);

	/**
	@brief	シェーダーがコンパイル出来ているか確認
	@param	シェーダーのID
	@return	true : 成功 , false : 失敗
	*/
	bool IsCompiled(GLuint shader);
	/**
	@brief	シェーダーがリンク出来ているか確認
	@param	シェーダーのID
	@return	true : 成功 , false : 失敗
	*/
	bool IsVaildProgram();

	GLuint vertexShader;
	GLuint fragShader;
	GLuint shaderProgram;
};

