#pragma once
#include "Tigraf/Renderer/Framebuffers/Framebuffer.h"

#include <glad/glad.h>

namespace Tigraf
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(uint32_t width, uint32_t height);
		virtual ~OpenGLFramebuffer();

		virtual void bind() override;
		virtual void unbind() override;

		virtual void invalidate() override;
		virtual void resize(uint32_t width, uint32_t height) override;

		virtual void clearDepthStencil() override;
		virtual void clearColor(uint32_t index) override;
		virtual void clearAll() override;

		virtual void attachColorTexture(TextureFormat colorFormat) override;
		virtual void attachDepthStencilTexture(TextureFormat depthStencilFormat) override;

	protected:
		GLuint m_FramebufferID = 0;
	};
}