#include "Tigraf/Renderer/Renderer.h"

#include "OpenGLRendererAPI.h"

namespace Tigraf
{
	RendererAPIName Renderer::s_RendererAPIName = RendererAPIName::OpenGL;
	RendererAPI* Renderer::s_RendererAPI = new OpenGLRendererAPI();

	void Renderer::init()
	{
		s_RendererAPI->init();
	}

	void Renderer::shutdown()
	{
	
	}

}