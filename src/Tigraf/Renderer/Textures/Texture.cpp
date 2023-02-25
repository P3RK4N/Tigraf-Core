#include "Tigraf/Renderer/Textures/Texture.h"
#include "OpenGLTexture.h"

#include "Tigraf/Renderer/Buffers/UniformBufferDefines.h"
#include "Tigraf/Renderer/Buffers/Buffer.h"

namespace Tigraf
{
	void SetTextureHandle(Ref<Texture2D> texture, Texture2DSlot textureSlot)
	{
		uint8_t textureHandleWrapper[16];													
		uint64_t handle = texture->getTextureHandle();										
		memcpy(textureHandleWrapper, &handle, 8);											
		UniformBuffer::s_TextureBuffer->updateBuffer(textureHandleWrapper, textureSlot, 16);
	}

	//void SetTextureHandle(Ref<Texture3D> texture, Texture3DSlot textureSlot) //TODO: Implement
	//{
	//	uint8_t textureHandleWrapper[16];													
	//	uint64_t handle = texture->getTextureHandle();										
	//	memcpy(textureHandleWrapper, &handle, 8);											
	//	UniformBuffer::s_TextureBuffer->updateBuffer(textureHandleWrapper, textureSlot, 16);
	//}

	void SetTextureHandle(Ref<TextureCube> texture, TextureCubeSlot textureSlot)
	{
		uint8_t textureHandleWrapper[16];													
		uint64_t handle = texture->getTextureHandle();										
		memcpy(textureHandleWrapper, &handle, 8);											
		UniformBuffer::s_TextureBuffer->updateBuffer(textureHandleWrapper, textureSlot, 16);
	}

	Ref<Texture2D> Texture2D::create(const char* filePath)
	{
		return createRef<OpenGLTexture2D>(filePath);
	}

	Ref<Texture2D> Texture2D::create(TextureFormat textureFormat, uint32_t width, uint32_t height, const void* data)
	{
		return createRef<OpenGLTexture2D>(textureFormat, width, height, data);
	}

	Ref<TextureCube> TextureCube::create(const char* baseFilePath, const char* fileFormat)
	{
		return createRef<OpenGLTextureCube>(baseFilePath, fileFormat);
	}

	Ref<RWTexture2D> RWTexture2D::create(TextureFormat textureFormat, uint32_t width, uint32_t height, const void* data)
	{
		return createRef<OpenGLRWTexture2D>(textureFormat, width, height, data);
	}

	const std::string TextureCube::s_CubeSides[6] =
	{
		"right",
		"left",
		"top",
		"bottom",
		"front",
		"back"
	};
}