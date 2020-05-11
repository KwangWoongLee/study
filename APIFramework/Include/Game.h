
#pragma once

#include <Windows.h>
#include <vector>
#include <list>
#include <unordered_map>
#include <crtdbg.h>


using namespace std;

#include "Macro.h"
#include "resource.h"
#include "Types.h"
#include "Flag.h"

template <typename T>
void Safe_Delete_VectorList(T& p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter));
	}

	p.clear();

}

template <typename T>
void Safe_Release_VectorList(T& p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_RELEASE((*iter));
	}

	p.clear();

}