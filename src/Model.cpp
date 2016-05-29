#include "Model.h"
#include "Log.h"

Model::Model() :
	m_rootBone(new ModelBone())
{
}

Model::~Model()
{
	delete m_rootBone;
}

void Model::Draw(shader_ptr shader, const glm::mat4& globalTransformation)
{
	if (m_rootBone) {
		m_rootBone->m_localTransformation = glm::inverse(globalTransformation);
		m_rootBone->Draw(shader, m_boneMap, m_rootBone->m_localTransformation);
	}
}

void Model::CreateBoneMap(ModelBone* bone)
{
	m_boneMap[bone->GetName()] = bone;

	for (auto c : bone->m_children) {
		CreateBoneMap(c);
	}
}

Model& Model::operator=(const Model& right)
{
	if (this == &right) return *this;

	m_name = right.m_name;
	*m_rootBone = *right.m_rootBone;
	CreateBoneMap(m_rootBone);

	return *this;
}
