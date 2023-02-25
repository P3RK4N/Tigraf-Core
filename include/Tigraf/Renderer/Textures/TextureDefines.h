#pragma once

//TEXTURE HANDLE OFFSET
#define TEXTURE_HANDLE_OFFSET 16

//Counts	//TODO: Change, make cleaner and better? Make modifiable by user?
#define TEXTURE_2D_COUNT	100
#define TEXTURE_3D_COUNT	20 
#define TEXTURE_CUBE_COUNT	20		

#define UNIFORM_BUFFER_0_TEXTURE_SIZE	(TEXTURE_2D_COUNT + TEXTURE_3D_COUNT + TEXTURE_CUBE_COUNT) * TEXTURE_HANDLE_OFFSET

//Texture 2D Slots
typedef enum
{
	TEXTURE_2D_0	=	0		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_1	=	1		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_2	=	2		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_3	=	3		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_4	=	4		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_5	=	5		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_6	=	6		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_7	=	7		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_8	=	8		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_9	=	9		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_10	=	10		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_11	=	11		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_12	=	12		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_13	=	13		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_14	=	14		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_15	=	15		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_16	=	16		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_17	=	17		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_18	=	18		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_19	=	19		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_20	=	20		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_21	=	21		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_22	=	22		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_23	=	23		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_24	=	24		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_25	=	25		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_26	=	26		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_27	=	27		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_28	=	28		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_29	=	29		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_30	=	30		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_31	=	31		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_32	=	32		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_33	=	33		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_34	=	34		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_35	=	35		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_36	=	36		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_37	=	37		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_38	=	38		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_39	=	39		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_40	=	40		*   TEXTURE_HANDLE_OFFSET,
	TEXTURE_2D_41	=	41		*   TEXTURE_HANDLE_OFFSET,	//TODO: Finish
} Texture2DSlot;

//Texture 3D Slots
typedef enum
{
	TEXTURE_3D_0	=	100		*	TEXTURE_HANDLE_OFFSET,
	TEXTURE_3D_1	=	101		*	TEXTURE_HANDLE_OFFSET,
	TEXTURE_3D_2	=	102		*	TEXTURE_HANDLE_OFFSET,
	TEXTURE_3D_3	=	103		*	TEXTURE_HANDLE_OFFSET,
	TEXTURE_3D_4	=	104		*	TEXTURE_HANDLE_OFFSET,
	TEXTURE_3D_5	=	105		*	TEXTURE_HANDLE_OFFSET,
	TEXTURE_3D_6	=	106		*	TEXTURE_HANDLE_OFFSET,
	TEXTURE_3D_7	=	107		*	TEXTURE_HANDLE_OFFSET,
	TEXTURE_3D_9	=	108		*	TEXTURE_HANDLE_OFFSET,	//TODO: Finish
} Texture3DSlot;

//Texture Cube Slots
typedef enum
{
	TEXTURE_CUBE_0	=	120		*	TEXTURE_HANDLE_OFFSET,
	TEXTURE_CUBE_1	=	121		*	TEXTURE_HANDLE_OFFSET,
	TEXTURE_CUBE_2	=	122		*	TEXTURE_HANDLE_OFFSET,
	TEXTURE_CUBE_3	=	123		*	TEXTURE_HANDLE_OFFSET,
	TEXTURE_CUBE_4	=	124		*	TEXTURE_HANDLE_OFFSET,
	TEXTURE_CUBE_5	=	125		*	TEXTURE_HANDLE_OFFSET,
	TEXTURE_CUBE_6	=	126		*	TEXTURE_HANDLE_OFFSET,
	TEXTURE_CUBE_7	=	127		*	TEXTURE_HANDLE_OFFSET,
	TEXTURE_CUBE_9	=	128		*	TEXTURE_HANDLE_OFFSET,	//TODO: Finish
}  TextureCubeSlot;