#include "Shader.h"

#include <iostream>
#include <fstream>

bool Shader::addSourceAndCompile(const std::string& path, GLenum type) {
	auto source = readFile(path);
    if (source.empty()) {
        failed = true;
        return false;
    }

    bool compiled = compileShader(source, type);
    failed |= !compiled;
    return compiled;
}

bool Shader::link() {
    if (failed) {
        std::cout << "Canceled linking because the compilation of one or more shaders failed" << std::endl;
        return false;
    }

	GLuint program = glCreateProgram();
	
	for (auto shader : shaders)
		glAttachShader(program, shader);
	
	glLinkProgram(program);
	int isLinked;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);

	if (isLinked == GL_FALSE) {
		GLint size;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &size);
		std::vector<GLchar> infoLog(size);
		glGetProgramInfoLog(program, size, &size, infoLog.data());
		
		std::cout << "Failed to link program! Error:\n" << infoLog.data() << std::endl;
		
		glDeleteProgram(program);
		return false;
	}
	
	for (auto shader : shaders) {
		glDetachShader(program, shader);
		glDeleteShader(shader);
	}
	
	handle = program;

    return true;
}

void Shader::use() {
	glUseProgram(handle);
}

void Shader::setInt(const std::string& name, int value) {
	int location = glGetUniformLocation(handle, name.c_str());
	glUniform1i(location, value);
}

void Shader::setFloat(const std::string& name, float value) {
	int location = glGetUniformLocation(handle, name.c_str());
	glUniform1f(location, value);
}

std::string Shader::readFile(const std::string& path) {
	std::ifstream file;
	file.open(path);
	std::string result;
	if (!file.is_open()) {
        std::cout << "Failed to read shader from '" << path << "'." << std::endl;
        file.close();
        return "";
    }

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    result.resize(size);
    file.seekg(0, std::ios::beg);
    file.read(&result[0], size);

	file.close();
	return result;
}

bool Shader::compileShader(const std::string& source, GLenum type) {
	GLuint shader = glCreateShader(type);
	const GLchar* sourceCStr = source.c_str();
	glShaderSource(shader, 1, &sourceCStr, 0);
	
	glCompileShader(shader);
	int isCompiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint size;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);
		std::vector<GLchar> infoLog(size);
		glGetShaderInfoLog(shader, size, &size, infoLog.data());
		
		std::cout << "Failed to compile shader! Error:\n" << infoLog.data() << std::endl;
		
		glDeleteShader(shader);
		return false;
	}
	
	shaders.push_back(shader);
    return true;
}