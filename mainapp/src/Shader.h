#ifndef SDL_GL_TEST_SHADER_H
#define SDL_GL_TEST_SHADER_H

#include <glad/glad.h>
#include <string>
#include <vector>

class Shader
{
public:
	Shader() = default;
	virtual ~Shader() = default;
	
	bool addSourceAndCompile(const std::string& path, GLenum type);
	
	bool link();
	
	void use();
	
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);

private:
	std::string readFile(const std::string& path);
	bool compileShader(const std::string& source, GLenum type);

private:
	GLuint handle = 0;
	std::vector<GLuint> shaders;
    bool failed = false;
};

#endif //SDL_GL_TEST_SHADER_H
