#pragma once

#include <map>
#include <string>
#include <memory>
#include <GL\glew.h>

#include "Texture.h"

typedef std::shared_ptr<Texture> texture_ptr;

class TextureManager
{
public:
	static texture_ptr Create(const std::string& path, GLfloat filter = GL_LINEAR);
	static texture_ptr Get(const std::string& path);
	static void Clear();
private:
	static std::map<std::string, texture_ptr> m_resourceMap;
};