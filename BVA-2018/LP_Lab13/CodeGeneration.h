#pragma once
#include <fstream>
#include "DefaultLib.h"
#include "stdafx.h"
#include "In.h"
#include "Parm.h"
#include "Error.h"


namespace CodeGeneration
{
	void Generate(wchar_t infile[], LT::LexTable& lex, IT::IdTable& ids, DefaultLib::DL& DLib);
	void PrintLiterals(std::ofstream* out, IT::IdTable& ids);
	void PrintId(std::ofstream* out, IT::IdTable& ids);
	void DecideBlocks(std::ofstream* out, IT::IdTable& ids, LT::LexTable& lex, DefaultLib::DL& DLib);
	void DecideCode(std::ofstream* out, IT::IdTable& ids, LT::LexTable& lex, int& pos, int& literal_counter, int& whcounter, int& ifcounter, DefaultLib::DL& DLib, int& DLibCounter);
	void PushLiteral(std::ofstream* out, IT::IdTable& ids, LT::LexTable& lex, int& pos, int& literal_counter);
	void PushVar(std::ofstream* out, IT::IdTable& ids, LT::LexTable& lex, int& pos);

}