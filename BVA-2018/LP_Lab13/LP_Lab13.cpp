// LP_Lab13.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include "Error.h"
#include "In.h"
#include "Log.h"
#include "Parm.h"
#include "FST.h"
#include "LT.h"
#include "IT.h"
#include "LexAnalizator.h"
#include "Polish.h"
#include "MFST.h"
#include <iostream>
#include "DefaultLib.h"
#include "CodeGeneration.h"
#include "Semantic.h"

using namespace std;
#define MFST_TRACE_START cout << setw(4) << left << "Шаг " << ": " << setw(20) << left << " Правило" << setw(30) << left << " Входная лента" \
							<< setw(20) << left << " Стек" << endl;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE, "rus");
	system("color 02");	
	try {
		Parm::PARM parm = Parm::getparm(argc, argv);
		In::IN in = In::getin(parm.in);
		Log::LOG logger = Log::getlog(parm.log);

		Log::WriteLog(logger);
		Log::WriteParm(logger, parm); 
		Log::WriteIn(logger, in);
		
		Semantic::Functions funcs = Semantic::GetFunction();
		DefaultLib::DL defaultLib;
		In::processToken(in);
		Lexer::LEX lex = Lexer::RunAnalysis(in, logger, defaultLib, funcs);
		 
		WriteLexems(logger, lex.Lextable);
		WriteItentifiers(logger, lex.IDtable);
		MFST_TRACE_START
			std::cout << std::endl;
		MFST::Mfst mfst(lex.Lextable, GRB::getGreibach());
		if (mfst.start(logger)) std::cout << "Syntaxer is COMPLETE" << std::endl;
		CodeGeneration::Generate(parm.out, lex.Lextable, lex.IDtable, defaultLib);
		WriteLexems(logger, lex.Lextable);

		Log::Close(logger);
	
//		mfst.printrules();
	}
	catch (Error::ERROR e){
		std::cout << "Ошибка " << e.id << ": " << e.message << std::endl << std::endl;
		std::cout << "Строка " << e.inext.line + 1 << " позиция " << e.inext.col << std::endl << std::endl;;
	}

	system("pause");
	return 0;
}

