#pragma once

#include "ModelBone.h"

class Model
{
public:
	Model();
	~Model();

	void Draw(shader_ptr shader, const glm::mat4& globalTransformation);
	ModelBone* GetRootBone() const { return m_rootBone; }

	Model& operator=(const Model& right);

	void CreateBoneMap(ModelBone* bone);

	void SetName(const std::string& name) { m_name = name; }
	std::string GetName() const { return m_name; }
private:
	friend class ModelManager;

	std::string m_name;

	ModelBone* m_rootBone;
	std::map<std::string, ModelBone*> m_boneMap;
};