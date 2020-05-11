#pragma once

typedef struct _tagResolution
{
	unsigned int	iW;
	unsigned int	iH;

} RESOLUTION, * PRESOLUTION;

typedef struct _tagPosition
{
	float x, y;
	_tagPosition() :
		x(0.f),
		y(0.f)
	{
	}

	_tagPosition(float _x, float _y) :
		x(_x),
		y(_y)
	{
	}

	_tagPosition(const _tagPosition& pos)
	{
		x = pos.x;
		y = pos.y;
	}

	_tagPosition(const POINT& p)
	{
		x = p.x;
		y = p.y;
	}

	void operator = (const _tagPosition& pos) 
	{
		x = pos.x;
		y = pos.y;
	}

	void operator = (const POINT& p)
	{
		x = p.x;
		y = p.y;
	}

	void operator = (float f[2])
	{
		x = f[0];
		y = f[1];
	}

	_tagPosition operator + (const _tagPosition& pos)
	{
		_tagPosition tPos;
		tPos.x = x + pos.x;
		tPos.y = y + pos.y;

		return tPos;
	}

	_tagPosition operator + (const POINT& pos)
	{
		_tagPosition tPos;
		tPos.x = x + pos.x;
		tPos.y = y + pos.y;

		return tPos;
	}

	_tagPosition operator + (float f[2])
	{
		_tagPosition tPos;
		tPos.x = x + f[1];
		tPos.y = y + f[2];

		return tPos;
	}

	_tagPosition operator + (float f)
	{
		_tagPosition tPos;
		tPos.x = x + f;
		tPos.y = y + f;

		return tPos;
	}


	void operator += (const _tagPosition& pos)
	{
		x += pos.x;
		y += pos.y;

	}

	_tagPosition operator - (const _tagPosition& pos)
	{
		_tagPosition tPos;
		tPos.x = x - pos.x;
		tPos.y = y - pos.y;

		return tPos;
	}

	_tagPosition operator - (const POINT& pos)
	{
		_tagPosition tPos;
		tPos.x = x - pos.x;
		tPos.y = y - pos.y;

		return tPos;
	}

	_tagPosition operator - (float f[2])
	{
		_tagPosition tPos;
		tPos.x = x - f[1];
		tPos.y = y - f[2];

		return tPos;
	}

	_tagPosition operator - (float f)
	{
		_tagPosition tPos;
		tPos.x = x - f;
		tPos.y = y - f;

		return tPos;
	}

	_tagPosition operator * (const _tagPosition& pos)
	{
		_tagPosition tPos;
		tPos.x = x * pos.x;
		tPos.y = y * pos.y;

		return tPos;
	}

	_tagPosition operator * (const POINT& pos) const
	{
		_tagPosition tPos;
		tPos.x = x * pos.x;
		tPos.y = y * pos.y;

		return tPos;
	}

	_tagPosition operator * (float f[2]) const
	{
		_tagPosition tPos;
		tPos.x = x * f[1];
		tPos.y = y * f[2];

		return tPos;
	}

	_tagPosition operator * (float f) const
	{
		_tagPosition tPos;
		tPos.x = x * f;
		tPos.y = y * f;

		return tPos;
	}

	_tagPosition operator / (const _tagPosition& pos)
	{
		_tagPosition tPos;
		tPos.x = x / pos.x;
		tPos.y = y / pos.y;

		return tPos;
	}

	_tagPosition operator / (const POINT& pos)
	{
		_tagPosition tPos;
		tPos.x = x / pos.x;
		tPos.y = y / pos.y;

		return tPos;
	}

	_tagPosition operator / (float f[2])
	{
		_tagPosition tPos;
		tPos.x = x / f[1];
		tPos.y = y / f[2];

		return tPos;
	}

	_tagPosition operator / (float f)
	{
		_tagPosition tPos;
		tPos.x = x / f;
		tPos.y = y / f;

		return tPos;
	}
}POSITION, *PPOSITION,_SIZE, * P_SIZE;