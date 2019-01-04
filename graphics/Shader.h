#pragma once

#include "GL\glew.h"

#include <string>
#include <fstream>

struct Shader {
	unsigned int m_shaderProgram;

	Shader(std::string vertSrc, std::string fragSrc) {
		int success;
		char infoLog[512];

		std::ifstream file(vertSrc);
		std::string line;
		std::string temp;

		if (file.is_open()) {
			while (std::getline(file, line)) {
				temp = temp + line + "\n";
			}
			std::cout << "Vert" << std::endl;
			std::cout << temp << std::endl;
		}
		else {
			std::cout << "Error loading file" << std::endl;
		}

		const char* src = temp.c_str();

		unsigned int vertShader;
		vertShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertShader, 1, &src, NULL);
		glCompileShader(vertShader);

		glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		};

		std::ifstream file2(fragSrc);
		std::string line2;
		std::string temp2;

		if (file2.is_open()) {
			while (std::getline(file2, line2)) {
				temp2 = temp2 + line2 + "\n";
			}
			std::cout << "Frag" << std::endl;
			std::cout << temp2 << std::endl;
		}
		else {
			std::cout << "Error loading file" << std::endl;
		}

		const char* src2 = temp2.c_str();

		unsigned int fragShader;
		fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &src2, NULL);
		glCompileShader(fragShader);

		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAG::COMPILATION_FAILED\n" << infoLog << std::endl;
		};

		m_shaderProgram = glCreateProgram();

		glAttachShader(m_shaderProgram, vertShader);
		glAttachShader(m_shaderProgram, fragShader);
		glLinkProgram(m_shaderProgram);

		glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		glDeleteProgram(vertShader);
		glDeleteProgram(fragShader);
	}

	void useShader() {
		glUseProgram(m_shaderProgram);
	}
};