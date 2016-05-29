#pragma once

#include "Mesh.h"
#include "ShaderManager.h"

class ModelBone
{
public:
	ModelBone(const std::string& name = std::string());
	~ModelBone();

	void Draw(shader_ptr shader, const std::map<std::string, ModelBone*>& boneMap, const glm::mat4& globalInverseTransform);

	ModelBone* FindBone(const std::string& name);

	ModelBone& operator=(const ModelBone& right);

	ModelBone* GetParent() const { return m_parent; }
	void AddChild(ModelBone* bone) { m_children.push_back(bone); }
	void AddMesh(mesh_ptr mesh) { m_meshes.push_back(mesh); }

	void SetName(const std::string& name) { m_name = name; }
	std::string GetName() const { return m_name; }

	void SetLocalTransformation(const glm::mat4& transformation) { m_localTransformation = transformation; }
private:
	friend class Model;

	ModelBone* m_parent;
	std::vector<ModelBone*> m_children;

	std::string m_name;
	glm::mat4 m_localTransformation;
	glm::mat4 m_globalTransformation;
	glm::mat4 m_offsetMatrix;

	std::vector<mesh_ptr> m_meshes;
};