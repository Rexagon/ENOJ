#include "ModelBone.h"

#include <iostream>

ModelBone::ModelBone(const std::string & name) :
	m_name(name), m_parent(nullptr)
{
}

ModelBone::~ModelBone()
{
	m_meshes.clear();

	for (auto c : m_children) {
		delete c;
	}
}

void ModelBone::Draw(shader_ptr shader, const std::map<std::string, ModelBone*>& boneMap, const glm::mat4 & globalInverseTransform)
{
	for (auto m : m_meshes) {
		std::vector<glm::mat4> boneMatrices(m->m_bones.size());

		for (size_t i = 0; i < boneMatrices.size(); ++i) {
			auto it = boneMap.find(m->m_bones[i]);
			if (it != boneMap.end()) {
				boneMatrices[i] = globalInverseTransform * it->second->m_globalTransformation * it->second->m_offsetMatrix;
			}
		}
		bool hasBones = !boneMatrices.empty();
		if (hasBones) {
			shader->SetUniformsArray("bone_matrices", &boneMatrices[0], boneMatrices.size());
		}
		shader->SetUniform("model_matrix", m_globalTransformation);
		m->Draw();
	}

	for (auto c : m_children) {
		c->Draw(shader, boneMap, globalInverseTransform);
	}
}

ModelBone * ModelBone::FindBone(const std::string & name)
{
	if (name == m_name) return this;

	for (auto c : m_children) {
		ModelBone* p = c->FindBone(name);
		if (p) {
			return p;
		}
	}

	return nullptr;
}

ModelBone & ModelBone::operator=(const ModelBone & right)
{
	if (this == &right) {
		return *this;
	}

	m_name = right.m_name;
	m_localTransformation = right.m_localTransformation;
	m_globalTransformation = right.m_globalTransformation;
	m_offsetMatrix = right.m_offsetMatrix;
	m_meshes = right.m_meshes;

	for (size_t i = 0; i < right.m_children.size(); ++i) {
		m_children.push_back(new ModelBone());
		*m_children.back() = *right.m_children[i];
		m_children.back()->m_parent = this;
	}

	return *this;
}
