#include "stdafx.h"
#include "DefaultLib.h"
#include "Semantic.h"

using namespace DefaultLib;
	char* DefaultLib::DL::Add(int k, Semantic::Functions& funcs)
	{
		char* id = new char[15];
		paramsCounter[1] = 0;
		switch (k)
		{
		case 11:
			id = "substr";
			paramsCounter[0] = 2;
			break;
		case 12:
			id = "stdlen";
			paramsCounter[0] = 2;
			break;
		case 13:
			id = "strsearch";
			paramsCounter[0] = 2;
			paramsCounter[1] = 2;
			break;
		case 14:
			id = "dgr";
			paramsCounter[0] = 1;
			paramsCounter[1] = 1;
			break;
		case 15:
			id = "mabs";
			paramsCounter[0] = 3;
			break;
		case 16:
			id = "mcos";
			paramsCounter[0] = 3;
		case 17:
			id = "mexp";
			paramsCounter[0] = 1;
			break;
		case 18:
			id = "mln";
			paramsCounter[0] = 3;
			break;
		case 19:
			id = "msin";
			paramsCounter[0] = 3;
			break;
		case 20:
			id = "msqr";
			paramsCounter[0] = 3;
			break;
		case 21:
			id = "mtan";
			paramsCounter[0] = 3;
			break;
		default:
			break;
		}
		Semantic::AddFunction(id, paramsCounter, funcs);
		functions[currentFunction++] = id;
		return id;
	}
	int DefaultLib::DL::GetType(char* id)
	{
		if (!strcmp(id, "substr")) {
			return 2;
		} else if (!strcmp(id, "strsearch")) {
			return 1;
		} else if (!strcmp(id, "stdlen")) {
			return 1;
		} else if (!strcmp(id, "dgr")) {
			return 1;
		} else if (!strcmp(id, "mabs")) {
			return 3;
		} else if (!strcmp(id, "mcos")) {
			return 3;
		} else if (!strcmp(id, "msin")) {
			return 3;
		} else if (!strcmp(id, "mexp")) {
			return 3;
		} else if (!strcmp(id, "mln")) {
			return 3;
		} else if (!strcmp(id, "msqr")) {
			return 3;
		} else if (!strcmp(id, "mtan")) {
			return 3;
		}
		else
			return 0;
	}
