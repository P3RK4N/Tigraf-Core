#pragma once
#include "Tigraf/Renderer/Buffers/Buffer.h"

#include <glad/glad.h>

namespace Tigraf
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		virtual ~OpenGLVertexBuffer();
		OpenGLVertexBuffer(GLuint vertexCount, GLuint vertexSize, void* data, BufferFlag bufferFlags);

		virtual void pushVertexAttribute(VertexAttributeType type) override;
		virtual void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		const GLuint getVertexArrayID() const { return m_VertexArrayID; }
		const GLuint getVertexBufferID() const { return m_VertexBufferID; }

	protected:
		GLuint m_VertexBufferID = 0;
		GLuint m_VertexArrayID = 0;

		uint32_t m_AttributeOffset = 0;
		uint32_t m_AttributeCount = 0;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		virtual ~OpenGLIndexBuffer();
		OpenGLIndexBuffer(const std::vector<GLuint>& indices, BufferFlag bufferFlags);
		
		const GLuint getIndexBufferID() const { return m_IndexBufferID; }

	protected:
		GLuint m_IndexBufferID = 0;
	};

	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:
		OpenGLUniformBuffer(void* data, uint32_t byteSize, BufferFlag bufferFlags);
		virtual ~OpenGLUniformBuffer();

		virtual void updateBuffer(void* subData, uint32_t byteOffset, uint32_t sizeInBytes) override;
		virtual void bind(uint16_t bindIndex) override;
		virtual void unbind() override;

		uint32_t getUniformBufferID() { return m_UniformBufferID; }

	protected:
		GLuint m_UniformBufferID = 0;
	};

	class OpenGLRWBuffer : public RWBuffer
	{
	public:
		OpenGLRWBuffer(void* data, uint32_t sizeInBytes, BufferFlag bufferFlags);
		virtual ~OpenGLRWBuffer();

		virtual void updateBuffer(void* subData, uint32_t byteOffset, uint32_t sizeInBytes) override;
		virtual void bind(uint16_t bindIndex) override;
		virtual void unbind() override;

		uint32_t getRWBufferID() { return m_RWBufferID; }

	protected:
		GLuint m_RWBufferID = 0;
	};
}