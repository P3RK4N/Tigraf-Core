#include "Tigraf/Renderer/Framebuffers/Framebuffer.h"
#include "OpenGLFramebuffer.h"

namespace Tigraf
{
	const Ref<Texture2D>& Framebuffer::getColorTexture(uint32_t textureIndex) { TIGRAF_CORE_ASSERT(textureIndex < m_ColorTextures.size(), "Invalid index!"); return m_ColorTextures[textureIndex]; }
	const Ref<Texture2D>& Framebuffer::getDepthStencilTexture() { TIGRAF_CORE_ASSERT(m_DepthStencilTexture, "DepthStencil not attached!"); return m_DepthStencilTexture; }


	Ref<Framebuffer> Framebuffer::create(uint32_t width, uint32_t height)
	{
		return createRef<OpenGLFramebuffer>(width, height);
	}

	float		Framebuffer::s_ClearColor1f = { 1.0f };
	glm::vec2	Framebuffer::s_ClearColor2f = { 0.3f, 1.0f };
	glm::vec3	Framebuffer::s_ClearColor3f = { 0.4f, 0.7f, 0.2f };
	glm::vec4	Framebuffer::s_ClearColor4f = { 0.1f, 1.0f, 0.1f, 1.0f };
	int			Framebuffer::s_ClearColor1i = { -1 };
	glm::ivec2	Framebuffer::s_ClearColor2i = { -1, -1 };
	glm::ivec3	Framebuffer::s_ClearColor3i = { -1, -1, -1 };
	glm::ivec4  Framebuffer::s_ClearColor4i = { -1, -1, -1, -1 };
}