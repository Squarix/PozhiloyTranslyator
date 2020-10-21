#include "stdafx.h"
#include "LexAnalizator.h"
#include "DefaultLib.h"
#include "Semantic.h"

namespace Lexer
{
	Graph graph[N_GRAPHS] =
	{
		{ Fst::FST(FST_INT_LITERAL),       'l'},
		{ Fst::FST(FST_STRING_LITERAL),    'l'},
		{ Fst::FST(FST_FLOAT_LITERAL),	   'l'},
		{ Fst::FST(FST_MAIN),			   'm'},
		{ Fst::FST(FST_INTEGER),		   't'},
		{ Fst::FST(FST_STRING),			   't'},
		{ Fst::FST(FST_FLOAT),			   't'},
		{ Fst::FST(FST_FUNCTION),		   'f'},
		{ Fst::FST(FST_RETURN),			   'r'},
		{ Fst::FST(FST_DECLARE),		   'd'},
		{ Fst::FST(FST_PRINT),			   'p'},
		{ Fst::FST(FST_SUBSTR),			   'z'},
		{ Fst::FST(FST_STRLEN),			   'z'},
		{ Fst::FST(FST_STRSEARCH),		   'z'},
		{ Fst::FST(FST_POW),			   'z'},
		{ Fst::FST(FST_MABS),			   'z'},
		{ Fst::FST(FST_MCOS),			   'z'},
		{ Fst::FST(FST_MEXP),			   'z'},
		{ Fst::FST(FST_MLN),			   'z'},
		{ Fst::FST(FST_MSIN),			   'z'},
		{ Fst::FST(FST_MSQR),			   'z'},
		{ Fst::FST(FST_MTAN),			   'z'},
		{ Fst::FST(FST_WHILE),			   'w'},
		{ Fst::FST(FST_IF),				   'c'},
		{ Fst::FST(FST_ID),				   'i'},
		{ Fst::FST(FST_ARYTHM_PLUS),       '+'},
		{ Fst::FST(FST_ARYTHM_MINUS),      '-'},
		{ Fst::FST(FST_ARYTHM_MULT),       '*'},
		{ Fst::FST(FST_ARYTHM_DIV),        '/'},
		{ Fst::FST(FST_SEMICOLON),		   ';'},
		{ Fst::FST(FST_EQUALS),			   '='},
		{ Fst::FST(FST_COMMA),			   ','},
		{ Fst::FST(FST_LEFT_BRACE),		   '{'},
		{ Fst::FST(FST_RIGHT_BRACE),	   '}'},
		{ Fst::FST(FST_OPEN_PARENTHESIS),  '('},
		{ Fst::FST(FST_CLOSE_PARENTHESIS), ')'},
		{ Fst::FST(FST_MORE),			   '>'},
		{ Fst::FST(FST_LESS),			   '<'},
	};

	LEX RunAnalysis(In::IN& in, Log::LOG &log, DefaultLib::DL defaultLib, Semantic::Functions func) {
		LEX lex_out;
		lex_out.Lextable = LT::Create(in.tokensSize);
		lex_out.IDtable = IT::Create(in.tokensSize);
		LT::Entry new_lexem;
		IT::Entry new_identifier;
		bool isFunction  = false;
		bool isDeclare   = false;
		bool openParen   = false;
		bool isInteger   = false;
		bool isString    = false;
		bool isFloat     = false;
		bool isBool		 = false;
		bool openFunc	 = false;
		bool isCondition = true;
		int* params		 = new int[10];
		int currentType  = 0;
		char* functionID = new char[20];
		short paramsCounter = 0;
		char visibility[10][ID_MAXSIZE+1]; // максимальная степень вложенности - 10
		strcpy(visibility[0], "GLOBAL");
		int current_vis_level = 0;
		bool wait_for_semicolon = false;

		for (int i = 0; i < in.tokensSize; i++) {
			bool recognized = false;
			for (int j = 0; j < N_GRAPHS; j++) {
				Fst::FST fst_test(in.tokens[i].token, graph[j].graph);
				if (Fst::execute(fst_test)) { 
					new_lexem.sn = in.tokens[i].line;
					recognized = true;
					if (graph[j].lexema == 'l') {
						
						new_lexem.lexema[0] = LEX_LITERAL;
						new_identifier.idtype = IT::IDTYPE::L; // тип - литерал
						if (j == 0) { 
							new_identifier.iddatatype = IT::IDDATATYPE::INT; 
							new_identifier.value.vint = atoi(in.tokens[i].token); 
						} else if (j == 1) { 
							new_identifier.iddatatype = IT::IDDATATYPE::STR; 
							new_identifier.value.vstr.len = strlen(in.tokens[i].token) - 2;
							strncpy(new_identifier.value.vstr.str, in.tokens[i].token + 1, new_identifier.value.vstr.len);
							new_identifier.value.vstr.str[new_identifier.value.vstr.len] = 0 ;
						} else {
							new_identifier.iddatatype = IT::IDDATATYPE::FLOAT;
							new_identifier.value.vfloat = atof(in.tokens[i].token);
						}

						if (openFunc && openParen) {
							params[paramsCounter++] = new_identifier.iddatatype;
						}
						else {
							if (!currentType)
							{
								currentType = new_identifier.iddatatype;
							}

							if (new_identifier.iddatatype != currentType)
							{
								throw ERROR_THROW_IN(115, in.tokens[i].line, in.tokens[i].pos);
							}
						}

						strcpy(new_identifier.vis, visibility[current_vis_level]);
						new_lexem.idxTI = IT::Add(lex_out.IDtable, new_identifier); // после добавления нового идентификатора сохраняем его id в лексеме
						int lexid = LT::Add(lex_out.Lextable, new_lexem); // сохраняем id лексемы после ее добавления
						lex_out.IDtable.table[new_lexem.idxTI].idxfirstLE = lexid ; // в таблице идентификаторов указываем id лексемы
						isInteger = false;
						isString = false;

						if (lex_out.Lextable.size - 4 >= 0) { //значения
							int s = lex_out.Lextable.size - 1;
							if (lex_out.Lextable.table[s - 1].lexema[0] == '=' && lex_out.Lextable.table[s - 2].lexema[0] == 'i' && 
								lex_out.Lextable.table[s - 3].lexema[0] == 't' && lex_out.Lextable.table[s - 4].lexema[0] == 'd') {
								if (new_identifier.iddatatype != lex_out.IDtable.table[lex_out.Lextable.table[s - 2].idxTI].iddatatype) {
									throw ERROR_THROW_IN(115, in.tokens[i].line, in.tokens[i].pos);
								}
								if (new_identifier.iddatatype == IT::IDDATATYPE::INT) {
									lex_out.IDtable.table[lex_out.Lextable.table[s - 2].idxTI].value.vint = new_identifier.value.vint ;
								} else {
									strcpy(lex_out.IDtable.table[lex_out.Lextable.table[s - 2].idxTI].value.vstr.str, new_identifier.value.vstr.str); 
									lex_out.IDtable.table[lex_out.Lextable.table[s - 2].idxTI].value.vstr.len = new_identifier.value.vstr.len;
								}
							}
					/*		else if (lex_out.Lextable.table[s - 1].lexema[0] == '=' && lex_out.Lextable.table[s - 2].lexema[0] == 'i') {
								if (new_identifier.iddatatype != lex_out.IDtable.table[lex_out.Lextable.table[s - 2].idxTI].iddatatype) {
									throw ERROR_THROW_IN(115, in.tokens[i].line, in.tokens[i].pos);
								}
								if (new_identifier.iddatatype == IT::IDDATATYPE::INT) {
									lex_out.IDtable.table[lex_out.Lextable.table[s - 2].idxTI].value.vint = new_identifier.value.vint;
								}
								else {
									strcpy(lex_out.IDtable.table[lex_out.Lextable.table[s - 2].idxTI].value.vstr.str, new_identifier.value.vstr.str);
									lex_out.IDtable.table[lex_out.Lextable.table[s - 2].idxTI].value.vstr.len = new_identifier.value.vstr.len;
								}
							} */
						}   

					} else if (graph[j].lexema == 't') { 
						if (j == 4) { // GRAPH_INTEGER
							new_lexem.lexema[0] = LEX_INTEGER;
							isInteger = true;
							isString  = false;
							isBool	  = false;
							isFloat	  = false;
						} else if (j == 5) { // GRAPH_STRING
							new_lexem.lexema[0] = LEX_STRING;
							isInteger = false;
							isString  = true;
							isBool	  = false;
							isFloat	  = false;
						}
						else if (j == 6) {
							new_lexem.lexema[0] = LEX_FLOAT;
							isInteger = false;
							isString  = false;
							isBool	  = false;
							isFloat   = true;
						}
						LT::Add(lex_out.Lextable, new_lexem);
					} else
						if (graph[j].lexema == 'i') { 
						
						{	// зануление стартовых значенiй идентификатора
							new_identifier.value.vint = 0;
							strcpy(new_identifier.value.vstr.str, "");
							new_identifier.value.vstr.len = 0;
						}

						if (strlen(in.tokens[i].token) > 10) { 
							throw ERROR_THROW_IN(116, in.tokens[i].line, in.tokens[i].pos);
						} else {
							strcpy(new_identifier.id, in.tokens[i].token); 
						}
						new_lexem.lexema[0] = LEX_ID; 

						if (isDeclare) {
							new_identifier.idtype = IT::IDTYPE::V;
							strcpy(new_identifier.vis, visibility[current_vis_level]); // для переменной только устанавливаем текущий уровень видимости
						}
						else if (isFunction && !openParen) {
							new_identifier.idtype = IT::IDTYPE::F;
							strcpy(new_identifier.vis, visibility[current_vis_level]); // встретили функцию, то устанавливаем ей текущий уровень видимости
							current_vis_level++; // увеличиаем уровень
							strcpy(visibility[current_vis_level], new_identifier.id); // теперь новый уровень видимости это сама функция
							strcpy(functionID, new_identifier.id);
						}
						else if (isFunction && openParen) {
							new_identifier.idtype = IT::IDTYPE::P;
							strcpy(new_identifier.vis, visibility[current_vis_level]); // для переменной только устанавливаем текущий уровень видимости
						}
						else {
							strcpy(new_identifier.vis, visibility[current_vis_level]); // для переменной только устанавливаем текущий уровень видимости
						}

						if (isInteger) {
							new_identifier.iddatatype = IT::IDDATATYPE::INT;
						} else if (isString) {
							new_identifier.iddatatype = IT::IDDATATYPE::STR;
						} else if (isFloat) {
							new_identifier.iddatatype = IT::IDDATATYPE::FLOAT;
						} else if (isBool) {
							new_identifier.iddatatype = IT::IDDATATYPE::BOOL;
						} else {
							new_identifier.iddatatype = IT::IDDATATYPE::UNKNOWN;
						}
						
						
						// declare integer a;
						// declare integer function b(integer c);
						// a = b + c;
						if (new_identifier.iddatatype == IT::IDDATATYPE::UNKNOWN) {
							int idx = IT::IsId(lex_out.IDtable, new_identifier.id, new_identifier.vis);
							if (idx != TI_NULLIDX) {
								new_lexem.idxTI = idx; // устанавливаем номер идентификатора в таблице идентификаторов для лексемы
								LT::Add(lex_out.Lextable, new_lexem); // добавляем лексему в таблицу лексем
								new_identifier.iddatatype = lex_out.IDtable.table[idx].iddatatype;
								new_identifier.idtype = lex_out.IDtable.table[idx].idtype;
							} else {
								throw ERROR_THROW_IN(114, in.tokens[i].line, in.tokens[i].pos);
							}
						} else {
				
							new_lexem.idxTI = IT::Add(lex_out.IDtable, new_identifier);
							int lexid = LT::Add(lex_out.Lextable, new_lexem);
							lex_out.IDtable.table[new_lexem.idxTI].idxfirstLE = lexid ; // в таблице идентификаторов указываем id лексемы
						}
						if (new_identifier.idtype == IT::IDTYPE::F) {
							openFunc = true;
							strcpy(functionID, new_identifier.id);
						}
						if (openFunc && openParen) {
							params[paramsCounter++] = new_identifier.iddatatype;
						}
						else {
							if (!currentType)
							{
								currentType = new_identifier.iddatatype;
							}

							if (new_identifier.iddatatype != currentType)
							{
								throw ERROR_THROW_IN(115, in.tokens[i].line, in.tokens[i].pos);
							}
						}
						isDeclare = false;
						isInteger = false;
						isString  = false;
						isBool	  = false;
						isFloat	  = false;
					} else if (graph[j].lexema == 'z') {
						new_lexem.lexema[0] = graph[j].lexema;
						strcpy(functionID, defaultLib.Add(j, func));
						openFunc = true;
						LT::Add(lex_out.Lextable, new_lexem);
					} else { // все остальные лексемы разбираются одинаково
						new_lexem.lexema[0] = graph[j].lexema;
						new_lexem.idxTI = LT_TI_NULLIDX;
						LT::Add(lex_out.Lextable, new_lexem);
						if (graph[j].lexema == 'c' || graph[j].lexema == 'w') {
							isCondition = true;
						}
						
						if (graph[j].lexema == ';') {
							currentType = 0;
							if (functionID) {
								if (Semantic::CheckFunction(functionID, func, params)) {
									memset(params, 0, sizeof(int) * 10);
									paramsCounter = 0;
									openFunc = false;
									strcpy(functionID, "");
								}
								else {
									throw ERROR_THROW_IN(117, new_lexem.sn, 0);
								}
							}
						}
						if (wait_for_semicolon) {
							strcpy(functionID, "");
							current_vis_level--;
							isFunction = false;
							isInteger = false;
							isString = false;
							isBool = false;
							isFloat = false;
							wait_for_semicolon = false;
							
						}

						if (graph[j].lexema == '/') {
							if (!strcmp(in.tokens[i + 1].token, "0"))
								throw ERROR_THROW_IN(127, in.tokens[i].line, in.tokens[i].pos);
						}
						if (graph[j].lexema == 'f') {
							isFunction = true;
							isDeclare  = false;
						} else if (graph[j].lexema == 'd') {
							isFunction  = false;
							isDeclare   = true;
							currentType = 0;
						} else if (graph[j].lexema == '(') {
							openParen = true;
						} else if (graph[j].lexema == ')') {
							if (openFunc && isFunction) {
								Semantic::AddFunction(functionID, params, func);
								memset(params, 0, sizeof(int)*10);
								openFunc = false;
								if (isFunction)
									strcpy(functionID, "");
							}
							openParen = false;
							if (isFunction) {
								wait_for_semicolon = true;
								currentType = 0;
							}
						} else if (graph[j].lexema == '}') {
							if (!isCondition)
								wait_for_semicolon = true;
							else
								isCondition = false;
							currentType = 0;
						}
						else if (graph[j].lexema == '{') {
							currentType = 0;
						}
					}
					break;
				}
			}
			if (!recognized) {
				throw ERROR_THROW_IN(113, in.tokens[i].line, in.tokens[i].pos); 
			}
		}
		return lex_out;
	}
}