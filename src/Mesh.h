#pragma once

#include <vector>
#include <GL\glew.h>

#include "Vertex.h"
#include "Material.h"

class Mesh
{
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<size_t> indices, const Material& material = Material(), const std::string& name = std::string());
	~Mesh();

	void Draw();

	void SetMaterial(const Material& material) { m_material = material; }
	const Material& GetMaterial() const { return m_material; }

	void SetName(const std::string& name) { m_name = name; }
	std::string GetName() const { return m_name; }

	void AddBone(const std::string& name) { m_bones.push_back(name); }
private:
	friend class ModelBone;

	std::string m_name;
	GLuint m_vao;
	size_t m_indicesNum;
	Material m_material;

	std::vector<std::string> m_bones;
};

typedef std::shared_ptr<Mesh> mesh_ptr;