#pragma once

#include "TextureManager.h"

class Material
{
public:
	Material(texture_ptr diffuseTexture = nullptr, texture_ptr normalTexture = nullptr, texture_ptr specularTexture = nullptr);

	void Bind(size_t id);

	void SetDiffuseTexture(texture_ptr diffuseTexture) { m_diffuseTexture = diffuseTexture; }
	void SetNormalTexture(texture_ptr normalTexture) { m_normalTexture = normalTexture; }
	void SetSpecularTexture(texture_ptr specularTexture) { m_specularTexture = specularTexture; }
private:
	texture_ptr m_diffuseTexture;
	texture_ptr m_normalTexture;
	texture_ptr m_specularTexture;
};