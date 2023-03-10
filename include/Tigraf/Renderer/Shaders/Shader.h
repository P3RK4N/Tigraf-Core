#pragma once

namespace Tigraf
{
	class Shader
	{
	public:
		Shader() {}
		virtual ~Shader() {}

		/* Create shader from file */
		static Ref<Shader> create(const std::filesystem::path& shaderPath);
		/* Create shader from memory */
		static Ref<Shader> create(const char* vertexSrc, const char* pixelSrc);

	public:
		virtual void use() = 0;
		virtual void dispatch(int x, int y, int z) = 0;

		virtual void setFloat(float value, const char* name) = 0;			
		virtual void setFloat2(const glm::vec2& vector, const char* name) = 0;
		virtual void setFloat3(const glm::vec3& vector, const char* name) = 0;
		virtual void setFloat4(const glm::vec4& vector, const char* name) = 0;

		virtual void setInt(int value, const char* name) = 0;				
		virtual void setInt2(const glm::i32vec2& vector, const char* name) = 0;
		virtual void setInt3(const glm::i32vec3& vector, const char* name) = 0;
		virtual void setInt4(const glm::i32vec4& vector, const char* name) = 0;

		virtual void setMat3(const glm::mat3& mat, const char* name) = 0;
		virtual void setMat4(const glm::mat4& mat, const char* name) = 0;
	};

}
