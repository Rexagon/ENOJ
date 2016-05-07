#include "TextureManager.h"
#include "Log.h"

#include "stb_image\stb_image.h"

std::map<std::string, texture_ptr> TextureManager::m_resourceMap;

texture_ptr TextureManager::Create(const std::string & path, GLfloat filter)
{
	texture_ptr texture = Get(path);

	if (texture)
	{
		return texture;
	} 
	else {
		int width, height, numComponents;
		unsigned char* data = stbi_load(("Data/" + path).c_str(), &width, &height, &numComponents, 4);

		size_t textureID;
		size_t textureTarget;

		if (data == 0)
		{
			Log::out << Log::Type::ERROR << "Unable to load texture: \"" << "Data/" + path << "\"\n";
			throw std::string("Data/" + path);
		}
		else if (width > 0 && height > 0) {
			glGenTextures(1, &textureID);
			textureTarget = GL_TEXTURE_2D;;

			glBindTexture(textureTarget, textureID);

			glTexParameterf(textureTarget, GL_TEXTURE_MIN_FILTER, filter);
			glTexParameterf(textureTarget, GL_TEXTURE_MAG_FILTER, filter);

			glTexImage2D(textureTarget, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}

		stbi_image_free(data);
		glBindTexture(GL_TEXTURE_2D, 0);

		texture = std::make_shared<Texture>();
		texture->m_textureID = textureID;
		texture->m_textureTarget = textureTarget;
		texture->m_path = path;
		m_resourceMap.insert(std::make_pair(path, texture));
	}

	return texture;
}

texture_ptr TextureManager::Get(const std::string & path)
{
	auto it = m_resourceMap.find(path);
	if (it != m_resourceMap.end())
	{
		return it->second;
	}
	else {
		return nullptr;
	}
}

void TextureManager::Clear()
{
	m_resourceMap.clear();
}
