#include "Tigraf/Renderer/Shaders/Shader.h"
#include "glslShader.h"

namespace Tigraf
{
	Ref<Shader> Shader::create(const std::filesystem::path& shaderPath)
	{
		return createRef<glslShader>(shaderPath);
	}

	Ref<Shader> Shader::create(const char* vertexSrc, const char* pixelSrc)
	{
	TIGRAF_CORE_ASSERT(vertexSrc && strlen(vertexSrc), "Invalid vertex source!")
	TIGRAF_CORE_ASSERT(pixelSrc && strlen(pixelSrc), "Invalid pixel source!")

		return createRef<glslShader>(vertexSrc, pixelSrc);
	}
}