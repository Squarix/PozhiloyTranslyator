#pragma once
#include "stdafx.h"
#include "Semantic.h"

namespace DefaultLib
{
	struct DL
	{
		int currentFunction;
		char** functions;
		int* paramsCounter;
		DL()
		{
			functions = new char*[15];
			paramsCounter = new int[15];
			for (int i = 0; i < 10; i++)
			{
				functions[i] = new char[15];
			}
			currentFunction = 0;

		}
		char* Add(int k, Semantic::Functions& funcs);
		int GetType(char* id);
	};
}