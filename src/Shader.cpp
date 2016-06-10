#include "Shader.h"
#include "Log.h"

#include <GL\glew.h>
#include <regex>

static void CheckShaderError(int shader, int flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (!success) {
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		Log::out << Log::Type::ERROR << errorMessage << ": " << error;
	}
}

Shader::~Shader()
{
	for (auto i : m_programs) {
		glDetachShader(GLid, i);
		glDeleteShader(i);
	}
	glDeleteProgram(GLid);

	Log::out << Log::Type::INFO << "Shader deleted: \"" + m_path + "\"\n";
}

void Shader::Bind()
{
	glUseProgram(GLid);
}

void Shader::SetUniform(const std::string & name, int value)
{
	glUniform1i(m_uniformsi[name], value);
}

void Shader::SetUniform(const std::string & name, float value)
{
	glUniform1f(m_uniformsf[name], value);
}

void Shader::SetUniform(const std::string & name, const glm::vec2 & value)
{
	glUniform2f(m_uniformsVec2[name], value.x, value.y);
}

void Shader::SetUniform(const std::string & name, const glm::vec3 & value)
{
	glUniform3f(m_uniformsVec3[name], value.x, value.y, value.z);
}

void Shader::SetUniform(const std::string & name, const glm::mat4 & value)
{
	glUniformMatrix4fv(m_uniformsMat4[name], 1, GL_FALSE, &value[0][0]);
}

void Shader::SetUniformsArray(const std::string & name, glm::vec3 * value, int size)
{
	glUniform3fv(m_uniformsVec3Array[name], size, &value[0][0]);
}

void Shader::SetUniformsArray(const std::string & name, glm::mat4 * value, int size)
{
	glUniformMatrix4fv(m_uniformsMat4Array[name], size, GL_FALSE, &value[0][0][0]);
}

int Shader::GetGLid() const
{
	return GLid;
}

void Shader::AddProgram(const std::string & text, int type)
{
	int shader = glCreateShader(type);

	if (shader == 0) {
		Log::out << Log::Type::ERROR << "Error creating shader type " << type << "\n";
	}

	const GLchar* p[1];
	p[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, p, lengths);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];

		glGetShaderInfoLog(shader, 1024, NULL, InfoLog);
		Log::out << Log::Type::ERROR << "Error compiling shader type " << shader << ": " << InfoLog << "\n";
	}

	glAttachShader(GLid, shader);
	m_programs.push_back(shader);
}

void Shader::AddAllAttributes(const std::string & vertexShaderText)
{
	static const std::string ATTRIBUTE_KEY = "layout";

	size_t attributeLocation = vertexShaderText.find(ATTRIBUTE_KEY);
	while (attributeLocation != std::string::npos) {
		bool isCommented = false;
		size_t lastLineEnd = vertexShaderText.rfind(";", attributeLocation);

		if (lastLineEnd != std::string::npos) {
			std::string potentialCommentSection = vertexShaderText.substr(lastLineEnd, attributeLocation - lastLineEnd);
			isCommented = potentialCommentSection.find("//") != std::string::npos;
		}

		if (!isCommented) {
			size_t begin = attributeLocation + ATTRIBUTE_KEY.length();
			size_t end = vertexShaderText.find(";", begin);

			std::string attributeLine = vertexShaderText.substr(begin + 1, end - begin - 1);

			std::regex reg("\\( *location *= *([\\d]) *\\) *[a-z\\d]{1,} *[a-z\\d]{1,} *(\\w{1,})", std::regex::optimize);
			std::smatch match;

			if (std::regex_search(attributeLine, match, reg)) {
				const std::string location = match[1];
				const std::string name = match[2];

				glBindAttribLocation(GLid, atoi(location.c_str()), name.c_str());
			}
		}
		attributeLocation = vertexShaderText.find(ATTRIBUTE_KEY, attributeLocation + ATTRIBUTE_KEY.length());
	}
}

void Shader::AddUniforms(const std::string & shaderText)
{
	static const std::string UNIFORM_KEY = "uniform";

	size_t uniformLocation = shaderText.find(UNIFORM_KEY);
	while (uniformLocation != std::string::npos) {
		bool isCommented = false;
		size_t lastLineEnd = shaderText.rfind(";", uniformLocation);

		if (lastLineEnd != std::string::npos) {
			std::string potentialCommentSection = shaderText.substr(lastLineEnd, uniformLocation - lastLineEnd);
			isCommented = potentialCommentSection.find("//") != std::string::npos;
		}

		if (!isCommented) {
			size_t begin = uniformLocation + UNIFORM_KEY.length();
			size_t end = shaderText.find(";", begin);

			std::string uniformLine = shaderText.substr(begin + 1, end - begin - 1);

			begin = uniformLine.find(" ");
			std::string uniformName = uniformLine.substr(begin + 1);
			std::string uniformType = uniformLine.substr(0, begin);

			bool isArray = uniformLine.find("[", 0) != std::string::npos;

			if (uniformType == "int")
				m_uniformsi[uniformName] = glGetUniformLocation(GLid, uniformName.c_str());
			else if (uniformType == "float")
				m_uniformsf[uniformName] = glGetUniformLocation(GLid, uniformName.c_str());
			else if (uniformType == "vec2")
				m_uniformsVec2[uniformName] = glGetUniformLocation(GLid, uniformName.c_str());
			else if (uniformType == "vec3")
				if (isArray)
					m_uniformsVec3Array[uniformName] = glGetUniformLocation(GLid, uniformName.c_str());
				else
					m_uniformsVec3[uniformName] = glGetUniformLocation(GLid, uniformName.c_str());
			else if (uniformType == "mat4")
				if (isArray)
					m_uniformsMat4Array[uniformName] = glGetUniformLocation(GLid, uniformName.c_str());
				else
					m_uniformsMat4[uniformName] = glGetUniformLocation(GLid, uniformName.c_str());
			else if (uniformType == "sampler2D" || uniformType == "sampler2DShadow" || uniformType == "samplerCube")
				m_uniformsi[uniformName] = glGetUniformLocation(GLid, uniformName.c_str());
		}
		uniformLocation = shaderText.find(UNIFORM_KEY, uniformLocation + UNIFORM_KEY.length());
	}
}

void Shader::CompileShader()
{
	glLinkProgram(GLid);
	CheckShaderError(GLid, GL_LINK_STATUS, true, "Error linking shader program");

	glValidateProgram(GLid);
	CheckShaderError(GLid, GL_VALIDATE_STATUS, true, "Invalid shader program");
}
