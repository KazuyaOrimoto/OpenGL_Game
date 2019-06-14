#pragma once

#include <glew.h>
#include <string>
#include "Math.h"

class Shader
{
public:
    Shader();
    ~Shader();
	bool Load(const std::string& vertName,const std::string& fragName);
	void Unload();

	void SetActive();

	/**
	@param シェーダー内の変数名
	@param 渡す行列
	*/
	void SetMatrixUniform(const char* name , const Matrix4& matrix);

private:
	bool CompileShader(const std::string& fileName,GLenum shaderType,GLuint& outShader);

	bool IsCompiled(GLuint shader);
	bool IsVaildProgram();

	GLuint vertexShader;
	GLuint fragShader;
	GLuint shaderProgram;
};

