#include "Shader.h"
#include "Texture.h"
#include <SDL.h>
#include <fstream>
#include <sstream>


Shader::Shader()
	:vertexShader(0)
	, fragShader(0)
	,shaderProgram(0)
{
}

Shader::~Shader()
{
}

/**
@brief	頂点シェーダーとフラグメントシェーダーのロード
@param	頂点シェーダーのファイル名
@param	頂点シェーダーのファイル名
@return	true : 成功 , false : 失敗
*/
bool Shader::Load(const std::string & vertName, const std::string & fragName)
{
	if (!CompileShader(vertName,GL_VERTEX_SHADER,vertexShader) ||
		!CompileShader(fragName,GL_FRAGMENT_SHADER, fragShader))
	{
		return false;
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);

	if (!IsVaildProgram())
	{
		return false;
	}

	return true;
}

/**
@brief	ロードしたシェーダーの解放
*/
void Shader::Unload()
{
	glDeleteProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
}

/**
@brief	シェーダープログラムをアクティブにする
*/
void Shader::SetActive()
{
	glUseProgram(shaderProgram);
}

/**
@brief	行列のUniform変数を設定する
@param	設定するUniform変数名
@param	設定する行列
*/
void Shader::SetMatrixUniform(const char * name, const Matrix4 & matrix)
{
	GLuint loc = glGetUniformLocation(shaderProgram,name);

	glUniformMatrix4fv(loc, 1, GL_TRUE, matrix.GetAsFloatPtr());
}

/**
@brief	シェーダーをコンパイルする
@param	コンパイルするシェーダーのファイル名
@param	シェーダーの種類
@param	シェーダーのID用の参照変数
@return	true : 成功 , false : 失敗
*/
bool Shader::CompileShader(const std::string & fileName, GLenum shaderType, GLuint & outShader)
{
	std::ifstream shaderFile(fileName);
	if (shaderFile.is_open())
	{
		std::stringstream sstream;
		sstream << shaderFile.rdbuf();
		std::string contents = sstream.str();
		const char* contentsChar = contents.c_str();

		outShader = glCreateShader(shaderType);

		glShaderSource(outShader, 1, &(contentsChar), nullptr);
		glCompileShader(outShader);

		if (!IsCompiled(outShader))
		{
			SDL_Log("Failed to compile shader %s", fileName.c_str());
			return false;
		}
	}
	else
	{
		SDL_Log("Shader file not found: %s", fileName.c_str());
		return false;
	}

	return true;
}

/**
@brief	シェーダーがコンパイル出来ているか確認
@param	シェーダーのID
@return	true : 成功 , false : 失敗
*/
bool Shader::IsCompiled(GLuint shader)
{
	GLint status;

	glGetShaderiv(shader,GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer,0,512);
		glGetShaderInfoLog(shader,411,nullptr,buffer);
		SDL_Log("GLSL Compile Failed:\n%s", buffer);
		return false;
	}
	return true;
}

/**
@brief	シェーダーがリンク出来ているか確認
@param	シェーダーのID
@return	true : 成功 , false : 失敗
*/
bool Shader::IsVaildProgram()
{
	GLint status;

	glGetProgramiv(shaderProgram,GL_LINK_STATUS,&status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer,0,512);
		glGetProgramInfoLog(shaderProgram,511,nullptr,buffer);
		SDL_Log("GLSL Link Status:\n%s", buffer);
		return false;
	}
	return true;
}
