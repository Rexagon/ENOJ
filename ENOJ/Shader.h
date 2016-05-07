#pragma once

#include <vector>
#include <string>
#include <map>

#include "Math.h"

class Shader
{
public:
	Shader() {}
	~Shader();

	void Bind();
	void SetUniform(const std::string& name, int value);
	void SetUniform(const std::string& name, float value);
	void SetUniform(const std::string& name, const vec2& value);
	void SetUniform(const std::string& name, const vec3& value);
	void SetUniform(const std::string& name, const mat4& value);
	void SetUniformsArray(const std::string& name, vec3* value, int size);
	void SetUniformsArray(const std::string& name, mat4* value, int size);

	int GetGLid() const;
private:
	friend class ShaderManager;

	std::string m_path;

	int GLid;

	std::map<std::string, size_t> m_uniformsi;
	std::map<std::string, size_t> m_uniformsf;
	std::map<std::string, size_t> m_uniformsVec2;
	std::map<std::string, size_t> m_uniformsVec3;
	std::map<std::string, size_t> m_uniformsMat4;
	std::map<std::string, size_t> m_uniformsVec3Array;
	std::map<std::string, size_t> m_uniformsMat4Array;

	std::vector<int> m_programs; // vertex, pixel, geometry and etc

	void AddProgram(const std::string& text, int type);
	void AddAllAttributes(const std::string& vertexShaderText);
	void AddUniforms(const std::string& shaderText);
	void CompileShader();
};