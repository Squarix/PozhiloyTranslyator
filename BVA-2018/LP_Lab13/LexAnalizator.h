#pragma once

#include "stdafx.h"
#include "IT.h"
#include "LT.h"
#include "In.h"
#include "Log.h"
#include "FST.h"
#include "DefaultLib.h"
#include "Semantic.h"

namespace Lexer
{
	struct LEX
	{
		LT::LexTable Lextable;
		IT::IdTable	IDtable;
	};

	struct Graph
	{
		Fst::FST graph;
		char lexema;
	
	};

	LEX RunAnalysis(In::IN& in, Log::LOG& log, DefaultLib::DL defaultLib, Semantic::Functions func);
}
