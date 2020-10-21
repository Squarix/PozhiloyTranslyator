#include "stdafx.h"
#include "Semantic.h"
using namespace Semantic;

	Functions Semantic::GetFunction()
	{
		Functions func;
		return func;
	}

	bool Semantic::CheckFunction(char* id, Functions functions, int* params)
	{
		for (int i = 0; i < functions.size; i++)
		{
			if (!strcmp(functions.func[i].id, id))
			{
				int j = 0;
				for (j; params[j] && functions.func[i].paramsList[j]; j++)
				{
					if (functions.func[i].paramsList[j] != params[j])
						return false;	
				}
			
				if (params[j] || (functions.func[i].paramsList[j] >= 0))
					return false;
				else
					return true;
			}
		}
	}

	void Semantic::AddFunction(char* id, int* params, Functions& fn)
	{
		strcpy(fn.func[fn.size].id, id);
		for (int i = 0; params[i]; i++)
			fn.func[fn.size].paramsList[i] = params[i];
		fn.size++;
		return;
	}
