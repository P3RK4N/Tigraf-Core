#pragma once

#include "UniformBufferDefines.h"
#include "RWBufferDefines.h"

#define isINT(VertexAttributeType)		(uint32_t)VertexAttributeType <  100U
#define isFLOAT(VertexAttributeType)	(uint32_t)VertexAttributeType >= 100U && (uint32_t)VertexAttributeType < 200U
#define isDOUBLE(VertexAttributeType)	(uint32_t)VertexAttributeType >= 200U


/**
* Sets texture to index location in UNIFORM_TEXTURE_BUFFER
*/
#define SET_TEXTURE_HANDLE(textureHandle, textureIndex)											\
	{																							\
		uint8_t textureHandleWrapper[16];														\
		uint64_t handle = textureHandle;														\
		memcpy(textureHandleWrapper, &handle, 8);												\
		UniformBuffer::s_TextureBuffer->updateBuffer(textureHandleWrapper, textureIndex, 16);	\
	}

/**
* Updates per frame buffer with given data,size and offset
*/
#define UPDATE_PER_FRAME_BUFFER(data, byteOffset, byteSize)	UniformBuffer::s_PerFrameBuffer->updateBuffer((void*)&(data), byteOffset, byteSize)

/**
* Updates per model buffer with given data,size and offset
*/
#define UPDATE_PER_MODEL_BUFFER(data, byteOffset, byteSize)	UniformBuffer::s_PerModelBuffer->updateBuffer((void*)&(data), byteOffset, byteSize)


namespace Tigraf
{
	enum class VertexAttributeType : uint16_t
	{
		INT = 0,
		INT2 = 1,
		INT3 = 2,
		INT4 = 3,

		FLOAT = 100,
		FLOAT2 = 101,
		FLOAT3 = 102,
		FLOAT4 = 103,

		FLOAT3X3 = 104,
		FLOAT4X4 = 105,
	};

	struct BufferFlag
	{
	public:
		/* For buffer which will be read by user on CPU side */
		static const BufferFlag STATIC;
		/* For buffer which needs to be updated by user on CPU side */
		static const BufferFlag DYNAMIC;

		operator uint32_t() const { return m_BufferFlagValue; }
		operator uint32_t() { return m_BufferFlagValue; }

	private:
		BufferFlag();
		BufferFlag(uint32_t value) : m_BufferFlagValue(value) {}

		uint32_t m_BufferFlagValue;
	};

	class IndexBuffer;
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void pushVertexAttribute(VertexAttributeType type) = 0;

		const Ref<IndexBuffer>& getIndexBuffer() { return m_IndexBuffer; }
		virtual void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;
		
		const uint32_t getVertexSize() const { return m_VertexSize; }
		const uint32_t getVertexCount() const { return m_VertexCount; }

	public:
		static Ref<VertexBuffer> create(uint32_t vertexCount, uint32_t vertexSize, void* data, BufferFlag bufferFlags);

	protected:
		uint32_t m_VertexSize = 0;
		uint32_t m_VertexCount = 0;

		Ref<IndexBuffer> m_IndexBuffer = nullptr;
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		const uint32_t getIndicesCount() const { return m_IndicesCount; }

	public:
		static Ref<IndexBuffer> create(const std::vector<uint32_t>& indices, BufferFlag bufferFlags);

	protected:
		uint32_t m_IndicesCount = 0;
	};

	class UniformBuffer
	{
	public:
		virtual ~UniformBuffer() {}

		virtual void updateBuffer(void* subData, uint32_t byteOffset, uint32_t byteSize) {}
		const uint16_t getBindIndex() { return m_BindIndex; }

		virtual void bind(uint16_t bindIndex) = 0;
		virtual void unbind() = 0;

	public:
		static Ref<UniformBuffer> create(void* data, uint32_t sizeInBytes, BufferFlag bufferFlags);

		static std::unordered_set<uint16_t> s_CurrentUniformBuffers;
		static Ref<UniformBuffer> s_TextureBuffer;
		static Ref<UniformBuffer> s_PerFrameBuffer;
		static Ref<UniformBuffer> s_PerModelBuffer;

	protected:
		uint32_t m_SizeInBytes = 0;
		uint16_t m_BindIndex = -1;
	};

	class RWBuffer
	{
	public:
		virtual ~RWBuffer() {}

		virtual void updateBuffer(void* subData, uint32_t byteOffset, uint32_t byteSize) {}
		const uint16_t getBindIndex() { return m_BindIndex; }

		virtual void bind(uint16_t bindIndex) = 0;
		virtual void unbind() = 0;

	public:
		static Ref<RWBuffer> create(void* data, uint32_t sizeInBytes, BufferFlag bufferFlags);

		static std::unordered_set<uint16_t> s_CurrentRWBuffers;

	protected:
		uint32_t m_SizeInBytes = 0;
		uint16_t m_BindIndex = -1;
	};
}