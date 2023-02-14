#pragma once

#include "Tigraf/Renderer/Buffers/Buffer.h"
#include "Tigraf/Renderer/Shaders/Shader.h"

namespace Tigraf
{
	class Mesh
	{
	public:
		Mesh(Ref<VertexBuffer> vertexBuffer, Ref<IndexBuffer> indexBuffer = nullptr, Ref<Shader> shader = nullptr);

		void drawTriangles();
		void drawTrianglesIndexed();

		//TODO: Add other draw methods

		void setShader(Ref<Shader> shader) { m_Shader = shader; }
		Ref<Shader> getShader() { return m_Shader; }

		Ref<VertexBuffer> getVertexBuffer() { return m_VertexBuffer; }
		Ref<IndexBuffer> getIndexBuffer() { return m_IndexBuffer; }

	protected:
		Ref<VertexBuffer> m_VertexBuffer = nullptr;
		Ref<IndexBuffer> m_IndexBuffer = nullptr;
		Ref<Shader> m_Shader = nullptr;
	};
}