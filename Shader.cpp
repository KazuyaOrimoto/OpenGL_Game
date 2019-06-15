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
@brief	���_�V�F�[�_�[�ƃt���O�����g�V�F�[�_�[�̃��[�h
@param	���_�V�F�[�_�[�̃t�@�C����
@param	���_�V�F�[�_�[�̃t�@�C����
@return	true : ���� , false : ���s
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
@brief	���[�h�����V�F�[�_�[�̉��
*/
void Shader::Unload()
{
	glDeleteProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
}

/**
@brief	�V�F�[�_�[�v���O�������A�N�e�B�u�ɂ���
*/
void Shader::SetActive()
{
	glUseProgram(shaderProgram);
}

/**
@brief	�s���Uniform�ϐ���ݒ肷��
@param	�ݒ肷��Uniform�ϐ���
@param	�ݒ肷��s��
*/
void Shader::SetMatrixUniform(const char * name, const Matrix4 & matrix)
{
	GLuint loc = glGetUniformLocation(shaderProgram,name);

	glUniformMatrix4fv(loc, 1, GL_TRUE, matrix.GetAsFloatPtr());
}

/**
@brief	�V�F�[�_�[���R���p�C������
@param	�R���p�C������V�F�[�_�[�̃t�@�C����
@param	�V�F�[�_�[�̎��
@param	�V�F�[�_�[��ID�p�̎Q�ƕϐ�
@return	true : ���� , false : ���s
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
@brief	�V�F�[�_�[���R���p�C���o���Ă��邩�m�F
@param	�V�F�[�_�[��ID
@return	true : ���� , false : ���s
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
@brief	�V�F�[�_�[�������N�o���Ă��邩�m�F
@param	�V�F�[�_�[��ID
@return	true : ���� , false : ���s
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
