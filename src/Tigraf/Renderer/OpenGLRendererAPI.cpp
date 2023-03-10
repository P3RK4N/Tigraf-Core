#include "OpenGLRendererAPI.h"

#include "Tigraf/Renderer/Buffers/OpenGLBuffer.h"
#include "Tigraf/Renderer/Mesh/MeshPrimitives.h"
#include "Tigraf/Renderer/Shaders/Shader.h"

#include <glad/glad.h>

//TODO: Add much more asserts
namespace Tigraf
{
	void OpenGLRendererAPI::init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

		//glEnable(GL_CULL_FACE);				//TODO: Enable
		//glCullFace(GL_BACK);

		glClearColor(0.2f, 0.6f, 0.8f, 1.0f);

		initGlobalUniformBuffers();

		MeshPrimitives::s_PrimitiveShader = Shader::create
		(
			//VertexShader
			R"_(
			#version 460 core
			layout (location = 0) in vec3 ObjectPositionVS;

			layout(std140, binding = 1) uniform PerFrameBuffer
			{
				mat4 VP;
			};

			layout (std140, binding = 2) uniform PerModelBuffer
			{
				mat4 MVP;
			};

			void main()
			{
				gl_Position = VP * vec4(ObjectPositionVS, 1.0);
			})_",

			//PixelShader
			R"_(
			#version 460 core

			out vec4 PixelColor;

			void main()
			{
				PixelColor = vec4(0.6, 0.3, 0.2, 1.0);
			})_"
		);
	}

	void OpenGLRendererAPI::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void OpenGLRendererAPI::setClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::drawTriangles(const Ref<VertexBuffer>& vertexBuffer, uint32_t numVertices)
	{
		TIGRAF_CORE_ASSERT(numVertices <= vertexBuffer->getVertexCount(), "Number of vertices is too great!");

		glBindVertexArray(reinterpret_cast<OpenGLVertexBuffer*>(vertexBuffer.get())->getVertexArrayID());
		glDrawArrays(GL_TRIANGLES, 0, numVertices ? numVertices : vertexBuffer->getVertexCount());
	}

	void OpenGLRendererAPI::drawTrianglesIndexed(const Ref<VertexBuffer>& vertexBuffer, uint32_t numIndices)
	{
		TIGRAF_CORE_ASSERT(vertexBuffer->getIndexBuffer() != nullptr, "Index Buffer must be set before drawing indexed!");
		TIGRAF_CORE_ASSERT(numIndices <= vertexBuffer->getIndexBuffer()->getIndicesCount(), "Number of indices is too great!");

		glBindVertexArray(reinterpret_cast<OpenGLVertexBuffer*>(vertexBuffer.get())->getVertexArrayID());
		glDrawElements(GL_TRIANGLES, numIndices ? numIndices : vertexBuffer->getIndexBuffer()->getIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::drawPoints(const Ref<VertexBuffer>& vertexBuffer, uint32_t numVertices)
	{
		TIGRAF_CORE_ASSERT(numVertices <= vertexBuffer->getVertexCount(), "Number of vertices is too great!");

		glBindVertexArray(reinterpret_cast<OpenGLVertexBuffer*>(vertexBuffer.get())->getVertexArrayID());
		glDrawArrays(GL_POINTS, 0, numVertices ? numVertices : vertexBuffer->getVertexCount());
	}

	void OpenGLRendererAPI::drawPointsIndexed(const Ref<VertexBuffer>& vertexBuffer, uint32_t numIndices)
	{
		TIGRAF_CORE_ASSERT(vertexBuffer->getIndexBuffer() != nullptr, "Index Buffer must be set before drawing indexed!");
		TIGRAF_CORE_ASSERT(numIndices <= vertexBuffer->getIndexBuffer()->getIndicesCount(), "Number of indices is too great!");

		glBindVertexArray(reinterpret_cast<OpenGLVertexBuffer*>(vertexBuffer.get())->getVertexArrayID());
		glDrawElements(GL_POINTS, numIndices ? numIndices : vertexBuffer->getIndexBuffer()->getIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::drawPointsInstanced(const Ref<VertexBuffer>& vertexBuffer, uint32_t numInstances, uint32_t numVertices)
	{
		TIGRAF_CORE_ASSERT(numVertices <= vertexBuffer->getVertexCount(), "Number of vertices is too great!");

		glBindVertexArray(reinterpret_cast<OpenGLVertexBuffer*>(vertexBuffer.get())->getVertexArrayID());
		glDrawArraysInstanced(GL_POINTS, 0, numVertices ? numVertices : vertexBuffer->getVertexCount(), numInstances);
	}

	void OpenGLRendererAPI::drawLines(const Ref<VertexBuffer>& vertexBuffer, uint32_t numVertices)
	{
		TIGRAF_CORE_ASSERT(numVertices <= vertexBuffer->getVertexCount(), "Number of vertices is too great!");

		glBindVertexArray(reinterpret_cast<OpenGLVertexBuffer*>(vertexBuffer.get())->getVertexArrayID());
		glDrawArrays(GL_LINES, 0, numVertices ? numVertices : vertexBuffer->getVertexCount());
	}
		
	void OpenGLRendererAPI::drawLinesIndexed(const Ref<VertexBuffer>& vertexBuffer, uint32_t numIndices)
	{
		TIGRAF_CORE_ASSERT(vertexBuffer->getIndexBuffer() != nullptr, "Index Buffer must be set before drawing indexed!");
		TIGRAF_CORE_ASSERT(numIndices <= vertexBuffer->getIndexBuffer()->getIndicesCount(), "Number of indices is too great!");

		glBindVertexArray(reinterpret_cast<OpenGLVertexBuffer*>(vertexBuffer.get())->getVertexArrayID());
		glDrawElements(GL_LINES, numIndices ? numIndices : vertexBuffer->getIndexBuffer()->getIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::initGlobalUniformBuffers()
	{
		UniformBuffer::s_TextureBuffer = UniformBuffer::create
		(
			NULL, 
			TEXTURE_HANDLE_OFFSET * (TEXTURE_2D_COUNT + TEXTURE_3D_COUNT + TEXTURE_CUBE_COUNT),
			BufferFlag::DYNAMIC
		);

		UniformBuffer::s_PerFrameBuffer = UniformBuffer::create
		(
			NULL,
			UNIFORM_BUFFER_1_PER_FRAME_SIZE,
			BufferFlag::DYNAMIC
		);

		UniformBuffer::s_PerModelBuffer = UniformBuffer::create
		(
			NULL,
			UNIFORM_BUFFER_2_PER_MODEL_SIZE,
			BufferFlag::DYNAMIC
		);

		
		GLuint textureBufferID = reinterpret_cast<OpenGLUniformBuffer*>(UniformBuffer::s_TextureBuffer.get())->getUniformBufferID();
		glBindBufferBase(GL_UNIFORM_BUFFER, UNIFORM_BUFFER_TEXTURE, textureBufferID);

		textureBufferID = reinterpret_cast<OpenGLUniformBuffer*>(UniformBuffer::s_PerFrameBuffer.get())->getUniformBufferID();
		glBindBufferBase(GL_UNIFORM_BUFFER, UNIFORM_BUFFER_PER_FRAME, textureBufferID);

		textureBufferID = reinterpret_cast<OpenGLUniformBuffer*>(UniformBuffer::s_PerModelBuffer.get())->getUniformBufferID();
		glBindBufferBase(GL_UNIFORM_BUFFER, UNIFORM_BUFFER_PER_MODEL, textureBufferID);

	}
}