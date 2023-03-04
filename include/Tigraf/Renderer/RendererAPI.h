#pragma once

#include "Tigraf/Renderer/Buffers/Buffer.h"
#include "Tigraf/Renderer/Textures/TextureDefines.h"

namespace Tigraf
{
	//TODO: Maybe refactor into a one draw function with enum draw config
	class RendererAPI
	{
	public:
		virtual ~RendererAPI() {}

		virtual void init() = 0;

		virtual void clear() = 0;
		virtual void setClearColor(const glm::vec4& color) = 0;

		virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		virtual void drawTriangles(const Ref<VertexBuffer>& vertexBuffer, uint32_t numVertices = 0) = 0;
		//virtual void drawTrianglesInstanced(const Ref<VertexBuffer>& vertexBuffer, uint32_t numInstances) = 0;
		virtual void drawTrianglesIndexed(const Ref<VertexBuffer>& vertexBuffer, uint32_t numIndices = 0) = 0;
		//virtual void drawTrianglesIndexedInstanced(const Ref<VertexBuffer>& vertexBuffer, uint32_t numInstances) = 0;

		virtual void drawPoints(const Ref<VertexBuffer>& vertexBuffer, uint32_t numVertices = 0) = 0;
		virtual void drawPointsInstanced(const Ref<VertexBuffer>& vertexBuffer, uint32_t numInstances, uint32_t numVertices = 0) = 0;
		virtual void drawPointsIndexed(const Ref<VertexBuffer>& vertexBuffer, uint32_t numIndices = 0) = 0;
		//virtual void drawPointsIndexedInstanced(const Ref<VertexBuffer>& vertexBuffer, uint32_t numInstances) = 0;

		//TODO: Add drawLines, implement commented functions
		virtual void drawLines(const Ref<VertexBuffer>& vertexBuffer, uint32_t numVertices = 0) = 0;
		//TODO...
		virtual void drawLinesIndexed(const Ref<VertexBuffer>& vertexBuffer, uint32_t numIndices = 0) = 0;
		//TODO...

	private:

	};
}