#pragma once
//GLOBAL UNIFORM BUFFERS -------------------------------------------------------------

//TODO: Make cleaner, modifiable by user?
//UNIFORM_BUFFER_0_TEXTURE_SIZE in TextureDefines.h

#define UNIFORM_BUFFER_1_PER_FRAME_SIZE 1000
#define UNIFORM_BUFFER_2_PER_MODEL_SIZE 1000

/** 
*	Available slots for Uniform Buffers.
*	First three can only be updated.
*
*	For more details, look at functions:
*	SetTextureHandle()
*	UpdatePerFrameBuffer()
*	UpdatePerModelBuffer()
*
*	You can find size of previous buffers with: 
*	--- UNIFORM_BUFFER_0_TEXTURE_SIZE, 
*	--- UNIFORM_BUFFER_1_PER_FRAME_SIZE,
*	--- UNIFORM_BUFFER_2_PER_MODEL_SIZE
*
*	Others need to be created with UniformBuffer::create() and manually used.
*/
typedef enum
{
	/**
	*	Buffer for storing 2D,3D and CUBE Textures.
	*	Access indices with:
	*		TEXTURE_2D_0	-	TEXTURE_2D_100
	*		TEXTURE_3D_0	-	TEXTURE_2D_20
	*		TEXTURE_CUBE_0	-	TEXTURE_2D_20
	*	
	*	Shader format:
	*	
	*	layout(std140, binding = 0) uniform TextureBuffer
	*	----	sampler2D textures2D[TEXTURE_2D_COUNT];			//Default 100
	*	----	sampler3D textures3D[TEXTURE_3D_COUNT];			//Default 20
	*	----	samplerCube texturesCube[TEXTURE_CUBE_COUNT];	//Default 20
	*/
	UNIFORM_BUFFER_TEXTURE		= 0,

	/**
	*	Buffer for storing data that changes once per frame.
	*/
	UNIFORM_BUFFER_PER_FRAME	= 1,

	/**
	*	Buffer for storing data that changes with each model.
	*/
	UNIFORM_BUFFER_PER_MODEL	= 2,

	/* General purpose buffers */
	UNIFORM_BUFFER_3			= 3,
	UNIFORM_BUFFER_4			= 4,
	UNIFORM_BUFFER_5			= 5,
	UNIFORM_BUFFER_6			= 6,
	UNIFORM_BUFFER_7			= 7,
	UNIFORM_BUFFER_8			= 8,
	UNIFORM_BUFFER_9			= 9,
	UNIFORM_BUFFER_10			= 10,
	UNIFORM_BUFFER_11			= 11,
	UNIFORM_BUFFER_12			= 12,
	UNIFORM_BUFFER_13			= 13,
	UNIFORM_BUFFER_14			= 14,
	UNIFORM_BUFFER_15			= 15
} UniformBufferSlot;

//------------------------------------------------------------------------------------
