#pragma once

#include "Tigraf/Renderer/RendererAPI.h"

namespace Tigraf
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual ~OpenGLRendererAPI() override {}

		virtual void init() override;

		virtual void clear() override;
		virtual void setClearColor(const glm::vec4& color) override;
		virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void setWireframeMode(bool wireframed) override;
		virtual void setCulling(bool cull, bool side = 0) override;

		virtual void drawTriangles(const Ref<VertexBuffer>& vertexBuffer, uint32_t numVertices = 0) override;
		virtual void drawTrianglesIndexed(const Ref<VertexBuffer>& vertexBuffer, uint32_t numIndices = 0) override;

		virtual void drawPoints(const Ref<VertexBuffer>& vertexBuffer, uint32_t numVertices = 0) override;
		virtual void drawPointsInstanced(const Ref<VertexBuffer>& vertexBuffer, uint32_t numInstances, uint32_t numVertices = 0) override;
		virtual void drawPointsIndexed(const Ref<VertexBuffer>& vertexBuffer, uint32_t numIndices = 0) override;

		virtual void drawLines(const Ref<VertexBuffer>& vertexBuffer, uint32_t numVertices = 0) override;
		virtual void drawLinesIndexed(const Ref<VertexBuffer>& vertexBuffer, uint32_t numIndices = 0) override;

	private:
		void initGlobalUniformBuffers();
	};
}