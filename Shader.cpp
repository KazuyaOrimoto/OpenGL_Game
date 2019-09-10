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
bool Shader::Load(const std::string & _vertName, const std::string & _fragName)
{
	if (!CompileShader(_vertName,GL_VERTEX_SHADER,vertexShader) ||
		!CompileShader(_fragName,GL_FRAGMENT_SHADER, fragShader))
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
void Shader::SetMatrixUniform(const char * _name, const Matrix4 & _matrix)
{
	GLuint loc = glGetUniformLocation(shaderProgram,_name);
	// シェーダーに行列データを送る
	glUniformMatrix4fv(loc, 1, GL_TRUE, _matrix.GetAsFloatPtr());
}

/**
@brief	ベクトルのUniform変数を設定する
@param	設定するUniform変数名
@param	設定するベクトル
*/
void Shader::SetVectorUniform(const char * _name, const Vector3 & _vector)
{
    GLuint loc = glGetUniformLocation(shaderProgram, _name);
    // シェーダーにVectorデータを送る
    glUniform3fv(loc, 1, _vector.GetAsFloatPtr());
}

/**
@brief	floatのUniform変数を設定する
@param	設定するUniform変数名
@param	設定するfloat
*/
void Shader::SetFloatUniform(const char * _name, const float & _value)
{
    GLuint loc = glGetUniformLocation(shaderProgram, _name);
    // シェーダーにfloatデータを送る
    glUniform1f(loc, _value);
}

/**
@brief	シェーダーをコンパイルする
@param	コンパイルするシェーダーのファイル名
@param	シェーダーの種類
@param	シェーダーのID用の参照変数
@return	true : 成功 , false : 失敗
*/
bool Shader::CompileShader(const std::string & _fileName, GLenum _shaderType, GLuint & _outShader)
{
	std::ifstream shaderFile(_fileName);
	if (shaderFile.is_open())
	{
		std::stringstream sstream;
		sstream << shaderFile.rdbuf();
		std::ifstream().swap(shaderFile);
		std::string contents = sstream.str();
		const char* contentsChar = contents.c_str();

		_outShader = glCreateShader(_shaderType);

		glShaderSource(_outShader, 1, &(contentsChar), nullptr);
		glCompileShader(_outShader);

		if (!IsCompiled(_outShader))
		{
			SDL_Log("Failed to compile shader %s", _fileName.c_str());
			return false;
		}
	}
	else
	{
		SDL_Log("Shader file not found: %s", _fileName.c_str());
		return false;
	}

	return true;
}

/**
@brief	シェーダーがコンパイル出来ているか確認
@param	シェーダーのID
@return	true : 成功 , false : 失敗
*/
bool Shader::IsCompiled(GLuint _shader)
{
	GLint status;

	glGetShaderiv(_shader,GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer,0,512);
		glGetShaderInfoLog(_shader,411,nullptr,buffer);
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
