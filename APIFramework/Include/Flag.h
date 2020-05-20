#pragma once

//Scene Type
enum SCENE_CREATE
{
	SC_CURRENT,
	SC_NEXT

};

//Direction
enum MOVE_DIR
{
	MD_BACK = -1,
	MD_NONE = 0,
	MD_FRONT = 1,
};

//Collider Type
enum COLLIDER_TYPE
{
	CT_RECT,
	CT_SPHERE,
	CT_LINE,
	CT_POINT,
	CT_PIXEL,
	CT_END

};


//Collision State
enum COLLISION_STATE
{
	CS_ENTER,
	CS_STAY,
	CS_LEAVE,
	CS_END

};


// AnimationType
enum ANIMATION_TYPE 
{
	AT_ATLAS,
	AT_FRAME,
	AT_END

};

//Animation option
enum ANIMATION_OPTION
{
	AO_LOOP,
	AO_ONCE_RETURN,
	AO_ONCE_DESTROY,
	AO_TIME_RETURN,
	AO_TIME_DESTROY,
	AO_END

};