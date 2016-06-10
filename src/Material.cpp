#include "Material.h"

Material::Material(texture_ptr diffuseTexture, texture_ptr normalTexture, texture_ptr specularTexture) :
	m_diffuseTexture(diffuseTexture), m_normalTexture(normalTexture), m_specularTexture(specularTexture)
{
	if (!m_diffuseTexture) {
		m_diffuseTexture = TextureManager::Create("images/default_diffuse.png");
	}

	if (!m_normalTexture) {
		m_normalTexture = TextureManager::Create("images/default_normal.png");
	}

	if (!m_specularTexture) {
		m_specularTexture = TextureManager::Create("images/default_specular.png");
	}
}

void Material::Bind(size_t id)
{
	m_diffuseTexture->Bind(id);
	m_normalTexture->Bind(id + 1);
	m_specularTexture->Bind(id + 2);
}
