#pragma once
#include "pch.h"
#include <fstream>
#include <optional>
#include <sstream>
#include <map>

class Shader
{
public:
	enum class ShaderType
	{
		VERTEX_SHADER,
		FRAGMENT_SHADER,
		GEOMETRIC_SHADER,
		PROGRAM
	};

	struct ShaderPathInfo {
		ShaderType type;
		std::string shaderPath;
		GLuint getGLType() const {
			switch (type)
			{
			case Shader::ShaderType::VERTEX_SHADER:
				return GL_VERTEX_SHADER;
			case Shader::ShaderType::FRAGMENT_SHADER:
				return GL_FRAGMENT_SHADER;
			case Shader::ShaderType::GEOMETRIC_SHADER:
				return GL_GEOMETRY_SHADER;
			case Shader::ShaderType::PROGRAM:
				throw std::runtime_error("ShaderType::PROGRAM is not allowed in this context");
			default:
				throw std::logic_error("unhandled type of ShaderType");
			}
		}
	};

	void Setup(const std::vector<ShaderPathInfo>& shaidersInfo) {
		m_program = AttachShaders(shaidersInfo);
	}

	void Use() {
		glUseProgram(m_program);
	}

	void UniformMatrix4f(const glm::mat4& mat, const std::string& procName) {
		glUniformMatrix4fv(
			glGetUniformLocation(m_program, procName.c_str()),
			1,
			GL_FALSE,
			glm::value_ptr(mat)
		);
	}

	void UniformFloat(float value, const std::string& procName) {
		glUniform1f(
			glGetUniformLocation(m_program, procName.c_str()),
			value
		);
	}

	void UniformVec3f(glm::vec3& vec, const std::string& procName) {
		glUniform3fv(
			glGetUniformLocation(m_program, procName.c_str()),
			1,
			glm::value_ptr(vec)
		);
	}

private:
	static GLuint LoadShader(const ShaderPathInfo& info)
	{
		auto path = info.shaderPath;
		std::string sourceCode;
		try {
			std::ifstream file;
			file.open(path);
			std::stringstream stringStream;
			stringStream << file.rdbuf();
			file.close();
			sourceCode = stringStream.str();
		}
		catch (std::ifstream::failure& ex) {
			std::cerr << ex.what() << std::endl;
		}

		const char* cStringSourceCode = sourceCode.c_str();
		GLuint shader = glCreateShader(info.getGLType());
		glShaderSource(shader, 1, &cStringSourceCode, NULL);
		glCompileShader(shader);
		CheckCompileErrors(shader, info.type);
		return shader;
	}

	static GLuint AttachShaders(const std::vector<ShaderPathInfo>& shaders) {
		// Создаём программу и привязываем к ней шейдер
		GLuint prog = glCreateProgram();
		std::vector<GLuint> compiledShaders;
		for (auto& pathInfo : shaders) {
			auto shader = LoadShader(pathInfo);
			glAttachShader(prog, shader);
			compiledShaders.push_back(shader);
		}
		glLinkProgram(prog);
		CheckCompileErrors(prog, ShaderType::PROGRAM);
		CheckShaderLinkStatus(prog);
		for (auto shader : compiledShaders) {
			glDeleteShader(shader);
		}
		return prog;
	}

	static void CheckCompileErrors(unsigned int shader, const ShaderType& type)
	{
		int success;
		char infoLog[1024];
		if (type != ShaderType::PROGRAM)
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << ShaderTypeToString(type) << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << ShaderTypeToString(type) << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
	static void CheckShaderLinkStatus(unsigned int ID) {
		int status;
		GLchar infoLog[1024];
		glGetProgramiv(ID, GL_LINK_STATUS, &status);
		if (!status) {
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::" << ID << "::LINKING_FAILURE\n" << infoLog << std::endl;
		}
		else {
			std::cout << "SHADER::" << ID << "::LINKING_SUCCESS" << std::endl;
		}
	}

	static std::string ShaderTypeToString(ShaderType enumVal) {
		switch (enumVal)
		{
		case Shader::ShaderType::VERTEX_SHADER:
			return "VERTEX_SHADER";
		case Shader::ShaderType::FRAGMENT_SHADER:
			return "FRAGMENT_SHADER";
		case Shader::ShaderType::GEOMETRIC_SHADER:
			return "GEOMETRIC_SHADER";
		case Shader::ShaderType::PROGRAM:
			return "PROGRAM";
		default:
			throw std::logic_error("unhandled type of enum val");
		}
	}

	GLuint m_program;
};