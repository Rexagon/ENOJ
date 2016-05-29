#include "ModelManager.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Log.h"
#include "ModelBone.h"

std::map<std::string, Model> ModelManager::m_resourceMap;

static glm::mat4 AiMatrix4x4ToMat4(const aiMatrix4x4 &value)
{
	glm::mat4 result;
	result[0] = glm::vec4(value[0][0], value[1][0], value[2][0], value[3][0]);
	result[1] = glm::vec4(value[0][1], value[1][1], value[2][1], value[3][1]);
	result[2] = glm::vec4(value[0][2], value[1][2], value[2][2], value[3][2]);
	result[3] = glm::vec4(value[0][3], value[1][3], value[2][3], value[3][3]);

	return result;
}

static Material ProcessMaterial(const aiMaterial* material)
{
	texture_ptr diffuseTexture;
	texture_ptr normalTexture;
	texture_ptr specularTexture;

	if (material->GetTextureCount(aiTextureType_DIFFUSE)) {
		aiString path;
		material->GetTexture(aiTextureType_DIFFUSE, 0, &path);
		diffuseTexture = TextureManager::Create(path.C_Str());
	}

	if (material->GetTextureCount(aiTextureType_NORMALS)) {
		aiString path;
		material->GetTexture(aiTextureType_NORMALS, 0, &path);
		normalTexture = TextureManager::Create(path.C_Str());
	}

	if (material->GetTextureCount(aiTextureType_SPECULAR)) {
		aiString path;
		material->GetTexture(aiTextureType_SPECULAR, 0, &path);
		specularTexture = TextureManager::Create(path.C_Str());
	}

	return Material(diffuseTexture, normalTexture, specularTexture);
}

static mesh_ptr ProcessMesh(const aiScene* scene, aiMesh* mesh)
{
	std::vector<Vertex> vertices(mesh->mNumVertices);
	std::vector<size_t> indices;

	for (size_t i = 0; i < mesh->mNumVertices; ++i) {
		Vertex vertex;

		vertex.position.x = mesh->mVertices[i].x;
		vertex.position.y = mesh->mVertices[i].y;
		vertex.position.z = mesh->mVertices[i].z;

		vertex.normal.x = mesh->mNormals[i].x;
		vertex.normal.y = mesh->mNormals[i].y;
		vertex.normal.z = mesh->mNormals[i].z;

		if (mesh->mTextureCoords[0]) {
			vertex.texCoords.x = mesh->mTextureCoords[0][i].x;
			vertex.texCoords.y = mesh->mTextureCoords[0][i].y;
		}

		vertices[i] = vertex;
	}

	glm::vec3* tan1 = new glm::vec3[vertices.size() * 2];
	glm::vec3* tan2 = tan1 + vertices.size();

	for (size_t i = 0; i < mesh->mNumFaces; ++i) {
		const aiFace& face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; ++j) {
			indices.push_back(face.mIndices[j]);
		}

		// Computing tangents
		size_t i1 = face.mIndices[0];
		size_t i2 = face.mIndices[1];
		size_t i3 = face.mIndices[2];

		const glm::vec3& v1 = vertices[i1].position;
		const glm::vec3& v2 = vertices[i2].position;
		const glm::vec3& v3 = vertices[i3].position;

		const glm::vec2& w1 = vertices[i1].texCoords;
		const glm::vec2& w2 = vertices[i2].texCoords;
		const glm::vec2& w3 = vertices[i3].texCoords;

		float x1 = v2.x - v1.x;
		float x2 = v3.x - v1.x;
		float y1 = v2.y - v1.y;
		float y2 = v3.y - v1.y;
		float z1 = v2.z - v1.z;
		float z2 = v3.z - v1.z;

		float s1 = w2.x - w1.x;
		float s2 = w3.x - w1.x;
		float t1 = w2.y - w1.y;
		float t2 = w3.y - w1.y;

		float r = 1.0F / (s1 * t2 - s2 * t1);
		glm::vec3 sdir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r,
			(t2 * z1 - t1 * z2) * r);
		glm::vec3 tdir((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r,
			(s1 * z2 - s2 * z1) * r);

		tan1[i1] += sdir;
		tan1[i2] += sdir;
		tan1[i3] += sdir;

		tan2[i1] += tdir;
		tan2[i2] += tdir;
		tan2[i3] += tdir;
	}

	for (size_t i = 0; i < vertices.size(); ++i) {
		const glm::vec3& n = vertices[i].normal;
		const glm::vec3& t = tan1[i];

		vertices[i].tangent = glm::normalize(t - n * glm::dot(n, t));
	}

	delete[] tan1;

	std::vector<aiVertexWeight>* tempWeightsPerVertex = new std::vector<aiVertexWeight>[mesh->mNumVertices];

	for (size_t i = 0; i < mesh->mNumBones; ++i) {
		const aiBone * pBone = mesh->mBones[i];
		for (unsigned int b = 0; b < pBone->mNumWeights; b++) {
			tempWeightsPerVertex[pBone->mWeights[b].mVertexId].push_back(aiVertexWeight(i, pBone->mWeights[b].mWeight));
		}
	}

	for (size_t i = 0; i < vertices.size(); ++i) {
		vertices[i].boneIds = glm::ivec4(0, 0, 0, 0);
		vertices[i].weights = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

		if (mesh->HasBones()) {
			if (tempWeightsPerVertex[i].size() > 4) {
				Log::out << Log::Type::ERROR << "The model has invalid bone weights and is not loaded";
			}
			for (size_t j = 0; j < tempWeightsPerVertex[i].size(); ++j) {
				vertices[i].boneIds[j] = tempWeightsPerVertex[i][j].mVertexId;
				vertices[i].weights[j] = (float)tempWeightsPerVertex[i][j].mWeight;
			}
		}
	}

	if (tempWeightsPerVertex != NULL) {
		delete[] tempWeightsPerVertex;
		tempWeightsPerVertex = NULL;
	}

	auto res = std::make_shared<Mesh>(vertices, indices, ProcessMaterial(scene->mMaterials[mesh->mMaterialIndex]), mesh->mName.C_Str());
	for (size_t i = 0; i < mesh->mNumBones; ++i) {
		res->AddBone(mesh->mBones[i]->mName.C_Str());
	}

	return res;
}

static void ProcessNode(const aiScene* scene, aiNode* node, ModelBone* bone)
{
	bone->SetName(node->mName.C_Str());
	bone->SetLocalTransformation(AiMatrix4x4ToMat4(node->mTransformation));

	for (size_t i = 0; i < node->mNumMeshes; ++i) {
		bone->AddMesh(ProcessMesh(scene, scene->mMeshes[node->mMeshes[i]]));
	}

	for (size_t i = 0; i < node->mNumChildren; ++i) {
		auto child = new ModelBone();
		bone->AddChild(child);
		ProcessNode(scene, node->mChildren[i], child);
	}
}

Model ModelManager::Load(const std::string& filename)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		throw std::exception(("unable to load scene \"" + filename + "\": " + importer.GetErrorString()).c_str());
	}

	Model res;
	res.SetName(filename);
	ProcessNode(scene, scene->mRootNode, res.m_rootBone);

	Log::out << Log::Type::INFO << "Model loaded: \"" << filename << "\"\n"; // TODO add information about it

	return res;
}

Model ModelManager::Get(const std::string& name)
{
	auto it = m_resourceMap.find(name);
	if (it != m_resourceMap.end()) {
		return it->second;
	}
	else {
		return Load(name);
	}
}

void ModelManager::Clear()
{
	m_resourceMap.clear();
}
