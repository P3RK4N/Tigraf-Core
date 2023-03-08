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

		virtual const bool isComplete() override { return glCheckNamedFramebufferStatus(m_FramebufferID, GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE; }

		virtual void clearDepthStencil() override;
		virtual void clearColor(uint32_t index) override;
		virtual void clearAll() override;

		virtual void attachColorTexture(TextureFormat colorFormat) override;
		virtual void attachColorTexture(Ref<Texture2D>colorFormat) override {} //TODO: Implement
		virtual void attachDepthStencilTexture(TextureFormat depthStencilFormat) override;
		virtual void attachDepthStencilTexture(Ref<Texture2D> depthStencilTexture) override {} //TODO:Implement
		virtual void attachDepthStencilTexture(Ref<TextureCube> depthStencilTexture) override;

	protected:
		GLuint m_FramebufferID = 0;
	};
}