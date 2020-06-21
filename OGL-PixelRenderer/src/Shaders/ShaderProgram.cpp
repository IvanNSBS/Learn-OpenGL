#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragPath)
{
	std::string vertex = ReadFromFile(vertexPath);
	std::string frag = ReadFromFile(fragPath);

	if (vertex.empty() || frag.empty()) {
		return;
	}

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	int success;
	char infoLog[512];

	const char* vertexCode = vertex.c_str();
	const char* fragmentCode = frag.c_str();

	glShaderSource(vertexShader, 1, &vertexCode, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	shaderProgram = glCreateProgram();
	// Output of this shader must be input for the next, otherwise
	// there will be errrors
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}

ShaderProgram::~ShaderProgram() {
	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(shaderProgram);
}

std::string ShaderProgram::ReadFromFile(const char* path) {
	std::string shaderCode;
	std::ifstream shaderFile;
	// ensure ifstream objects can throw exceptions:
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		shaderFile.open(path);
		std::stringstream  shaderStream;
		// read file's buffer contents into streams
		shaderStream << shaderFile.rdbuf();
		// close file handlers
		shaderFile.close();
		shaderCode = shaderStream.str();
		return shaderCode;
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		return "";
	}
}

void ShaderProgram::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
}
void ShaderProgram::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}
void ShaderProgram::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void ShaderProgram::SetFloat3(const std::string& name, glm::vec3 value) const
{
	glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), value.x, value.y, value.z);
}

void ShaderProgram::SetMat4(const std::string& name, GLboolean transpose, GLfloat* val) const
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, transpose, val);
}

void ShaderProgram::Bind()
{
	glUseProgram(this->shaderProgram);
}