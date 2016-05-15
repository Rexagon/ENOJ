#pragma once

#include <memory>
#include <GL\glew.h>

#include "Shader.h"

static const int SHADER_VERTEX = 1 << 0;
static const int SHADER_FRAGMENT = 1 << 1;
static const int SHADER_GEOMETRY = 1 << 2;
static const int SHADER_COMPUTE = 1 << 3;

typedef std::shared_ptr<Shader> shader_ptr;

class ShaderManager
{
public:
	static shader_ptr Create(const std::string& shaderName, int type);
	static shader_ptr Get(const std::string& path);
	static void Clear();
private:
	static std::map<std::string, shader_ptr> m_resourceMap;
};