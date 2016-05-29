#include "Mesh.h"
#include "Log.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<size_t> indices, const Material& material, const std::string& name) :
	m_material(material), m_name(name), m_indicesNum(indices.size())
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	GLuint vbo, ebo;
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesNum * sizeof(size_t), &indices[0], GL_STATIC_DRAW);

	//position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	//texCoords
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));

	//normal
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	//tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, tangent));

	//boneIds
	glEnableVertexAttribArray(4);
	glVertexAttribIPointer(4, 4, GL_INT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, boneIds));

	//weights
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, weights));

	Log::out << Log::Type::INFO << "Mesh created: " << m_name << "\n";
}

Mesh::~Mesh()
{
	Log::out << Log::Type::INFO << "Mesh deleted: " << m_name << "\n";
}

void Mesh::Draw()
{
	m_material.Bind(0);
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_indicesNum, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
