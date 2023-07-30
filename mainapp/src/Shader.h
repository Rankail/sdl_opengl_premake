#ifndef SDL_GL_TEST_SHADER_H
#define SDL_GL_TEST_SHADER_H

#include <glad/glad.h>
#include <string>
#include <vector>
#include "math/math.h"

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

	template<int M, int N, typename T> requires (M >= 2 && M <= 4 && N >= 2 && N <= 4 && (std::is_same_v<T, double> || std::is_same_v<T, float>))
	void setMatrix(const std::string& name, Matrix<M, N, T> const& m) {
		int location = glGetUniformLocation(handle, name.c_str());
		
		if (std::is_same_v<T, double>) {
			switch (N) {
				case 2:
					switch (M) {
						case 2: glUniformMatrix2dv(location, 1, GL_FALSE, (double*)m.getValuePtr()); return;
						case 3: glUniformMatrix2x3dv(location, 1, GL_FALSE, (double*)m.getValuePtr()); return;
						case 4: glUniformMatrix2x4dv(location, 1, GL_FALSE, (double*)m.getValuePtr()); return;
					}
				case 3:
					switch (M) {
						case 2: glUniformMatrix3x2dv(location, 1, GL_FALSE, (double*)m.getValuePtr()); return;
						case 3: glUniformMatrix3dv(location, 1, GL_FALSE, (double*)m.getValuePtr()); return;
						case 4: glUniformMatrix3x4dv(location, 1, GL_FALSE, (double*)m.getValuePtr()); return;
					}
				case 4:
					switch (M) {
						case 2: glUniformMatrix4x2dv(location, 1, GL_FALSE, (double*)m.getValuePtr()); return;
						case 3: glUniformMatrix4x3dv(location, 1, GL_FALSE, (double*)m.getValuePtr()); return;
						case 4: glUniformMatrix4dv(location, 1, GL_FALSE, (double*)m.getValuePtr()); return;
					}
			}
		} else if (std::is_same_v<T, float>) {
			switch (N) {
				case 2:
					switch (M) {
						case 2: glUniformMatrix2fv(location, 1, GL_FALSE, (float*)m.getValuePtr()); return;
						case 3: glUniformMatrix2x3fv(location, 1, GL_FALSE, (float*)m.getValuePtr()); return;
						case 4: glUniformMatrix2x4fv(location, 1, GL_FALSE, (float*)m.getValuePtr()); return;
					}
				case 3:
					switch (M) {
						case 2: glUniformMatrix3x2fv(location, 1, GL_FALSE, (float*)m.getValuePtr()); return;
						case 3: glUniformMatrix3fv(location, 1, GL_FALSE, (float*)m.getValuePtr()); return;
						case 4: glUniformMatrix3x4fv(location, 1, GL_FALSE, (float*)m.getValuePtr()); return;
					}
				case 4:
					switch (M) {
						case 2: glUniformMatrix4x2fv(location, 1, GL_FALSE, (float*)m.getValuePtr()); return;
						case 3: glUniformMatrix4x3fv(location, 1, GL_FALSE, (float*)m.getValuePtr()); return;
						case 4: glUniformMatrix4fv(location, 1, GL_FALSE, (float*)m.getValuePtr()); return;
					}
			}
		}
	}

	template<int M, int N, typename T> requires (M >= 2 && M <= 4 && N == 1 && (std::is_same_v<T, double> || std::is_same_v<T, float>))
	void setVector(const std::string& name, Matrix<M, N, T> const& m) {
		int location = glGetUniformLocation(handle, name.c_str());

		if (std::is_same_v<T, double>) {
			switch (M) {
				case 2: glUniform2dv(location, 1, (double*)m.getValuePtr()); return;
				case 3: glUniform3dv(location, 1, (double*)m.getValuePtr()); return;
				case 4: glUniform4dv(location, 1, (double*)m.getValuePtr()); return;
			}
		} else if (std::is_same_v<T, float>) {
			switch (M) {
				case 2: glUniform2fv(location, 1, (float*)m.getValuePtr()); return;
				case 3: glUniform3fv(location, 1, (float*)m.getValuePtr()); return;
				case 4: glUniform4fv(location, 1, (float*)m.getValuePtr()); return;
			}
		}
	}

private:
	std::string readFile(const std::string& path);
	bool compileShader(const std::string& source, GLenum type);

private:
	GLuint handle = 0;
	std::vector<GLuint> shaders;
    bool failed = false;
};

#endif //SDL_GL_TEST_SHADER_H
