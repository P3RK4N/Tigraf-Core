#include "Tigraf/Renderer/Buffers/Buffer.h"

#include "OpenGLBuffer.h"

namespace Tigraf
{
	const BufferFlag BufferFlag::STATIC =	BufferFlag(BIT(0));
	const BufferFlag BufferFlag::DYNAMIC =	BufferFlag(BIT(1));

	Ref<VertexBuffer> VertexBuffer::create(uint32_t vertexCount, uint32_t vertexSize, void* data, BufferFlag bufferFlags)
	{
		TIGRAF_CORE_ASSERT(!(bufferFlags && 0b00), "Invalid buffer flags used!");

		return createRef<OpenGLVertexBuffer>(vertexCount, vertexSize, data, bufferFlags);
	}

	Ref<IndexBuffer> IndexBuffer::create(const std::vector<uint32_t>& indices, BufferFlag bufferFlags)
	{
		TIGRAF_CORE_ASSERT(!(bufferFlags && 0b00), "Invalid buffer flags used!");

		return createRef<OpenGLIndexBuffer>(indices, bufferFlags);
	}

	Ref<UniformBuffer> UniformBuffer::create(void* data, uint32_t byteSize, BufferFlag bufferFlags)
	{
		TIGRAF_CORE_ASSERT(!(bufferFlags && 0b00), "Invalid buffer flags used!");

		return createRef<OpenGLUniformBuffer>(data, byteSize, bufferFlags);
	}

	Ref<RWBuffer> RWBuffer::create(void* data, uint32_t sizeInBytes, BufferFlag bufferFlags)
	{
		TIGRAF_CORE_ASSERT(!(bufferFlags && 0b00), "Invalid buffer flags used!");

		return createRef<OpenGLRWBuffer>(data, sizeInBytes, bufferFlags);
	}

	Ref<UniformBuffer> UniformBuffer::s_TextureBuffer = nullptr;
	Ref<UniformBuffer> UniformBuffer::s_PerFrameBuffer = nullptr;
	Ref<UniformBuffer> UniformBuffer::s_PerModelBuffer = nullptr;

	std::unordered_set<uint16_t> UniformBuffer::s_CurrentUniformBuffers = { 0, 1, 2 };
	std::unordered_set<uint16_t> RWBuffer::s_CurrentRWBuffers = {};

}