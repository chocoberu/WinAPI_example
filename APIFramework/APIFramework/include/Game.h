#pragma once

#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>
#include "Macro.h"
#include "resource.h"
#include "Types.h"
#include "Flag.h"

using namespace std;

template <typename T>
void Safe_Delete_VecList(T& p)
{
	for (auto iter = p.begin(); iter != p.end(); iter++)
		SAFE_DELETE((*iter));
	p.clear();
}
template <typename T>
void Safe_Release_VecList(T& p)
{
	for (auto iter = p.begin(); iter != p.end(); iter++)
		SAFE_RELEASE((*iter));
	p.clear();
}