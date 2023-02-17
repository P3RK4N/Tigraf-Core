#include "OpenGLBuffer.h"

namespace Tigraf
{
	static GLenum OpenGLVertexAttributeType(VertexAttributeType type)
	{
		switch(type)
		{
		case VertexAttributeType::INT:		return GL_INT;
		case VertexAttributeType::INT2:		return GL_INT;
		case VertexAttributeType::INT3:		return GL_INT;
		case VertexAttributeType::INT4:		return GL_INT;
		case VertexAttributeType::FLOAT:	return GL_FLOAT;
		case VertexAttributeType::FLOAT2:	return GL_FLOAT;
		case VertexAttributeType::FLOAT3:	return GL_FLOAT;
		case VertexAttributeType::FLOAT4:	return GL_FLOAT;
		case VertexAttributeType::FLOAT3X3:	return GL_FLOAT;
		case VertexAttributeType::FLOAT4X4:	return GL_FLOAT;
		}

		TIGRAF_CORE_ASSERT(0, "Invalid VertexAttributeType");
		return 0;
	};

	static GLuint OpenGLVertexAttributeTypeSize(VertexAttributeType type)
	{
		switch(type)
		{
		case VertexAttributeType::INT:		return sizeof(int)   * 1;
		case VertexAttributeType::INT2:		return sizeof(int)   * 2;
		case VertexAttributeType::INT3:		return sizeof(int)   * 3;
		case VertexAttributeType::INT4:		return sizeof(int)   * 4;
		case VertexAttributeType::FLOAT:	return sizeof(float) * 1;
		case VertexAttributeType::FLOAT2:	return sizeof(float) * 2;
		case VertexAttributeType::FLOAT3:	return sizeof(float) * 3;
		case VertexAttributeType::FLOAT4:	return sizeof(float) * 4;
		case VertexAttributeType::FLOAT3X3:	return sizeof(float) * 9;
		case VertexAttributeType::FLOAT4X4:	return sizeof(float) * 16;
		}

		TIGRAF_CORE_ASSERT(0, "Invalid VertexAttributeType");
		return 0;
	};

	static GLuint OpenGLVertexAttributeTypeCount(VertexAttributeType type)
	{
		switch(type)
		{
		case VertexAttributeType::INT:		return 1;
		case VertexAttributeType::INT2:		return 2;
		case VertexAttributeType::INT3:		return 3;
		case VertexAttributeType::INT4:		return 4;
		case VertexAttributeType::FLOAT:	return 1;
		case VertexAttributeType::FLOAT2:	return 2;
		case VertexAttributeType::FLOAT3:	return 3;
		case VertexAttributeType::FLOAT4:	return 4;
		case VertexAttributeType::FLOAT3X3:	return 9;
		case VertexAttributeType::FLOAT4X4:	return 16;
		}

		TIGRAF_CORE_ASSERT(0, "Invalid VertexAttributeType");
		return 0;
	};

	static GLuint OpenGLBufferFlags(BufferFlag bufferFlags)
	{
		GLuint openglBufferFlags = 0;

		//It's static by default
		if(BufferFlag::STATIC && bufferFlags) ;
		if(BufferFlag::DYNAMIC && bufferFlags) openglBufferFlags |= GL_DYNAMIC_STORAGE_BIT;

		return openglBufferFlags;
	};

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteVertexArrays(1, &m_VertexArrayID);
		glDeleteBuffers(1, &m_VertexBufferID);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(GLuint vertexCount, GLuint vertexSize, void* data, BufferFlag bufferFlags)
	{
		m_VertexSize = vertexSize;
		m_VertexCount = vertexCount;

		//Creating vertex buffer and assigning immutable storage to it
		glCreateBuffers(1, &m_VertexBufferID);
		glNamedBufferStorage(m_VertexBufferID, vertexSize*vertexCount, data, OpenGLBufferFlags(bufferFlags));

		//Creating vertex array and binding buffer to index 0
		glCreateVertexArrays(1, &m_VertexArrayID);
		glVertexArrayVertexBuffer(m_VertexArrayID, 0, m_VertexBufferID, 0, vertexSize);
	}

	void OpenGLVertexBuffer::pushVertexAttribute(VertexAttributeType type)
	{
		glEnableVertexArrayAttrib(m_VertexArrayID, m_AttributeCount);

		GLuint attributeSize = OpenGLVertexAttributeTypeSize(type);
		GLenum attributeElementType = OpenGLVertexAttributeType(type);
		GLuint attributeElementCount = OpenGLVertexAttributeTypeCount(type);
	
		//Adding attribute to vertex array
		if(isINT(type))			glVertexArrayAttribIFormat(m_VertexArrayID, m_AttributeCount, attributeElementCount, attributeElementType, m_AttributeOffset);
		else if(isFLOAT(type))	glVertexArrayAttribFormat(m_VertexArrayID, m_AttributeCount, attributeElementCount, attributeElementType, false, m_AttributeOffset);
		else if(isDOUBLE(type)) glVertexArrayAttribLFormat(m_VertexArrayID, m_AttributeCount, attributeElementCount, attributeElementType, m_AttributeOffset);

		//Binding attribute to first vertex buffer
		glVertexArrayAttribBinding(m_VertexArrayID, m_AttributeCount, 0);

		m_AttributeOffset += attributeSize; 
		m_AttributeCount += 1;

	}

	void OpenGLVertexBuffer::setIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glVertexArrayElementBuffer(m_VertexArrayID, reinterpret_cast<OpenGLIndexBuffer*>(indexBuffer.get())->getIndexBufferID());
		m_IndexBuffer = indexBuffer;
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(const std::vector<GLuint>& indices, BufferFlag bufferFlags)
	{
		m_IndicesCount = indices.size();
		glCreateBuffers(1, &m_IndexBufferID);
		glNamedBufferStorage(m_IndexBufferID, m_IndicesCount * sizeof(indices[0]), indices.data(), OpenGLBufferFlags(bufferFlags));
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_IndexBufferID);
	}

	OpenGLUniformBuffer::OpenGLUniformBuffer(void* data, uint32_t sizeInBytes, BufferFlag bufferFlags)
	{
		glCreateBuffers(1, &m_UniformBufferID);
		glNamedBufferStorage(m_UniformBufferID, sizeInBytes, data, OpenGLBufferFlags(bufferFlags));
		m_SizeInBytes = sizeInBytes;
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		glDeleteBuffers(1, &m_UniformBufferID);
	}

	void OpenGLUniformBuffer::updateBuffer(void* subData, uint32_t byteOffset, uint32_t sizeInBytes)
	{
		glNamedBufferSubData(m_UniformBufferID, byteOffset, sizeInBytes, subData);
	}

	void OpenGLUniformBuffer::bind(uint16_t bindIndex)
	{
		TIGRAF_CORE_ASSERT(UniformBuffer::s_CurrentUniformBuffers.find(bindIndex) == UniformBuffer::s_CurrentUniformBuffers.end(), "Index is already taken!");
		glBindBufferBase(GL_UNIFORM_BUFFER, bindIndex, m_UniformBufferID);
		UniformBuffer::s_CurrentUniformBuffers.insert(bindIndex);
		m_BindIndex = bindIndex;
	}

	void OpenGLUniformBuffer::unbind()
	{
		TIGRAF_CORE_ASSERT(m_BindIndex != -1, "This buffer is already unbound!");
		glBindBufferBase(GL_UNIFORM_BUFFER, m_BindIndex, 0);
		UniformBuffer::s_CurrentUniformBuffers.erase(m_BindIndex);
		m_BindIndex = -1;
	}

	
	OpenGLRWBuffer::OpenGLRWBuffer(void* data, uint32_t sizeInBytes, BufferFlag bufferFlags)
	{
		glCreateBuffers(1, &m_RWBufferID);
		glNamedBufferStorage(m_RWBufferID, sizeInBytes, data, OpenGLBufferFlags(bufferFlags));
		m_SizeInBytes = sizeInBytes;
	}

	OpenGLRWBuffer::~OpenGLRWBuffer()
	{
		glDeleteBuffers(1, &m_RWBufferID);
	}

	void OpenGLRWBuffer::updateBuffer(void* subData, uint32_t byteOffset, uint32_t sizeInBytes)
	{
		glNamedBufferSubData(m_RWBufferID, byteOffset, sizeInBytes, subData);
	}

	void OpenGLRWBuffer::bind(uint16_t bindIndex)
	{
		TIGRAF_CORE_ASSERT(RWBuffer::s_CurrentRWBuffers.find(bindIndex) == RWBuffer::s_CurrentRWBuffers.end(), "Index is already taken!");
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindIndex, m_RWBufferID);
		RWBuffer::s_CurrentRWBuffers.insert(bindIndex);
		m_BindIndex = bindIndex;
	}

	void OpenGLRWBuffer::unbind()
	{
		TIGRAF_CORE_ASSERT(m_BindIndex != -1, "This buffer is already unbound!");
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, m_BindIndex, 0);
		RWBuffer::s_CurrentRWBuffers.erase(m_BindIndex);
		m_BindIndex = -1;
	}

}