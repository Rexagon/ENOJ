#include "ShaderManager.h"
#include "Log.h"

std::map<std::string, shader_ptr> ShaderManager::m_resourceMap;

std::vector<std::string> Split(const std::string& s, char delim)
{
	std::vector<std::string> elems;

	const char* cstr = s.c_str();
	unsigned int strLength = (unsigned int)s.length();
	unsigned int start = 0;
	unsigned int end = 0;

	while (end <= strLength) {
		while (end <= strLength) {
			if (cstr[end] == delim)
				break;
			end++;
		}

		elems.push_back(s.substr(start, end - start));
		start = end + 1;
		end = start;
	}

	return elems;
}

static std::string LoadShader(const std::string& path)
{
	std::ifstream file;
	file.open(path.c_str());

	std::string output;
	std::string line;

	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);

			if (line.find("#include") == std::string::npos)
				output.append(line + "\n");
			else {
				std::string includeFileName = Split(line, ' ')[1];
				includeFileName = includeFileName.substr(1, includeFileName.length() - 2);

				std::string toAppend = LoadShader(includeFileName);
				output.append(toAppend + "\n");
			}
		}
	}
	else {
		Log::out << Log::Type::ERROR << "Unable to load shader: " << path << "\n";
	}

	return output;
};

shader_ptr ShaderManager::Create(const std::string & shaderName, int type)
{
	std::string path = shaderName;
	shader_ptr shader = Get(shaderName);

	if (shader) {
		return shader;
	}
	else {
		shader = std::make_shared<Shader>();
		shader->GLid = glCreateProgram();
		shader->m_path = shaderName;

		if (!shader->GLid) {
			Log::out << Log::Type::ERROR << "Error creating shader program\n";
		}

		std::string vertexShaderText;
		std::string fragmentShaderText;
		std::string geometryShaderText;

		if (type & SHADER_VERTEX) {
			vertexShaderText = LoadShader(path + ".vp");
			shader->AddProgram(vertexShaderText, GL_VERTEX_SHADER);
			shader->AddAllAttributes(vertexShaderText);
		}

		if (type & SHADER_FRAGMENT) {
			fragmentShaderText = LoadShader(path + ".fp");
			shader->AddProgram(fragmentShaderText, GL_FRAGMENT_SHADER);
		}

		if (type & SHADER_GEOMETRY) {
			geometryShaderText = LoadShader(path + ".gp");
			shader->AddProgram(geometryShaderText, GL_GEOMETRY_SHADER);
		}

		shader->CompileShader();

		if (type & SHADER_VERTEX) {
			shader->AddUniforms(vertexShaderText);
		}

		if (type & SHADER_FRAGMENT) {
			shader->AddUniforms(fragmentShaderText);
		}

		if (type & SHADER_GEOMETRY) {
			shader->AddUniforms(geometryShaderText);
		}

		m_resourceMap.insert(std::make_pair(shaderName, shader));
	}

	Log::out << "Shader loaded: \"" << shaderName << "\"\n";

	return shader;
}

shader_ptr ShaderManager::Get(const std::string & path)
{
	auto it = m_resourceMap.find(path);
	if (it != m_resourceMap.end()) {
		return it->second;
	}
	else {
		return nullptr;
	}
}

void ShaderManager::Clear()
{
	m_resourceMap.clear();
}
