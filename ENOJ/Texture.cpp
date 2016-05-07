#include "Texture.h"
#include "Log.h"

#include <GL\glew.h>

Texture::~Texture()
{
	if (m_textureID) glDeleteTextures(1, &m_textureID);
	Log::out << Log::Type::INFO << "Texture deleted: Data/" + m_path + "\n";
}

void Texture::Bind(size_t id)
{
	glActiveTexture(GL_TEXTURE0 + id);
	glBindTexture(m_textureTarget, m_textureID);
}
