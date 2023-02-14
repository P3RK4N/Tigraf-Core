#include "Tigraf/Renderer/Mesh/Mesh.h"

#include "Tigraf/Renderer/Renderer.h"

namespace Tigraf
{
	Mesh::Mesh(Ref<VertexBuffer> vertexBuffer, Ref<IndexBuffer> indexBuffer, Ref<Shader> shader)
		: m_Shader(shader), m_VertexBuffer(vertexBuffer), m_IndexBuffer(indexBuffer) 
	{
		if(m_IndexBuffer) m_VertexBuffer->setIndexBuffer(m_IndexBuffer);
	}

	void Mesh::drawTriangles()
	{
		TIGRAF_CORE_ASSERT(m_Shader, "Shader not attached!");
	
		m_Shader->use();
		Renderer::s_RendererAPI->drawTriangles(m_VertexBuffer);
	}

	void Mesh::drawTrianglesIndexed()
	{
		TIGRAF_CORE_ASSERT(m_IndexBuffer, "Index buffer not attached!");
		TIGRAF_CORE_ASSERT(m_Shader, "Shader not attached!");

		m_Shader->use();
		Renderer::s_RendererAPI->drawTrianglesIndexed(m_VertexBuffer);
	}
}