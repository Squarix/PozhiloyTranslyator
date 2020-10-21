#pragma once
#include "stdafx.h"
#include "LT.h"
#include "IT.h"
#include "Error.h"

namespace Semantic
{
	struct Function
	{
		char* id;
		int* paramsList;
		Function()
		{
			id = new char[15];
			paramsList = new int[10];
		}
	};

	struct Functions
	{
		int size = 0;
		int maxsize = 30;

		Function* func = new Function[maxsize];
	};	

	Functions GetFunction();
	bool CheckFunction(char* id, Functions func, int* params);
	void AddFunction(char* id, int* params, Functions& fn);
}


