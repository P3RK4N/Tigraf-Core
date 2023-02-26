#pragma once

namespace Tigraf
{
	class Mesh;
	class Shader;

	class MeshPrimitives
	{
	public:

		/*
		* Creates plane Mesh with vertex and index buffer with default transform on a XZ plane
		*/
		static Ref<Mesh> Plane();

		/*
		* Creates plane Mesh with vertex and index buffer with given transform on a XZ plane
		*/
		static Ref<Mesh> Plane(const glm::mat4& initialTransform);

		/*
		* Creates plane Mesh with vertex and index buffer with default transform on a XY plane.
		*/
		static Ref<Mesh> Plane2D();

		/*
		* Creates plane Mesh with vertex and index buffer with default transform on a XY plane.
		*/
		static Ref<Mesh> Plane2D(const glm::mat4& initialTransform);

		/*
		* Creates cube Mesh with vertex and index buffer with default transform
		*/
		static Ref<Mesh> Cube();

		/*
		* Creates cube Mesh with vertex and index buffer with given transform
		*/
		static Ref<Mesh> Cube(const glm::mat4& initialTransform);

	private:
		static Ref<Shader> s_PrimitiveShader;

		friend class RendererAPI;
		friend class OpenGLRendererAPI;
	};
}