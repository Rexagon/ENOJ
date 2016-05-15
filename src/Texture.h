#pragma once

#include <string>

class Texture
{
public:
	Texture() {}
	~Texture();

	void Bind(size_t id);
private:
	friend class TextureManager;

	std::string m_path;

	size_t m_textureTarget;
	size_t m_textureID;
};