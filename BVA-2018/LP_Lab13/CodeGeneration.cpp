#include "stdafx.h"
#include "CodeGeneration.h"
#include <iostream>
#include "Polish.h"
#include "DefaultLib.h"

#define LInt(i)   "\tL" << i << '\t' << '\t' << "DWORD" << '\t'
#define LStr(i)   "\tL" << i << '\t' << '\t' << "DB" << '\t'
#define LFloat(i) "\tL" << i << '\t' << '\t' << "REAL4" << '\t'
#define LBool(i)  "\tL" << i << '\t' << '\t' <<	 "BYTE" << '\t'
#define VInt(i)   "" << i << '\t' << '\t' << "SDWORD" << '\t'
#define VStr(i)   "" << i << '\t' << '\t' << "DWORD" << '\t'
#define VFloat(i) "" << i << '\t' << '\t' << "REAL4" << '\t'
#define VBool(i)  "" << i << '\t' << '\t' << "BYTE" << '\t'
#define VFLD(i)	  "\tFLD " << i << '\n'
#define LFLD(i)   "\tFLD L" << i << '\n'

namespace CodeGeneration
{
	
	void Generate(wchar_t outfile[], LT::LexTable& lex, IT::IdTable& ids, DefaultLib::DL& DLib)
	{
		std::ofstream *out = new std::ofstream(outfile, std::ofstream::out);
		/*std::ofstream out;
		out.open(outfile, std::ofstream::out);*/
		if (out->fail()) {
			throw ERROR_THROW(112);
		}
		*out << ".586\n\t.model flat, stdcall\n\tincludelib libucrt.lib\n\tincludelib kernel32.lib\n\tincludelib default_lib.lib\n\tExitProcess PROTO :DWORD\n\n";
		*out << "stdlen PROTO :DWORD\n" <<
			"strsearch PROTO : WORD, : WORD\n" <<
			"mabs PROTO : REAL4\n" <<
			"dgr  PROTO : DWORD, : DWORD\n" <<
			"mcos PROTO : REAL4\n" <<
			"mexp PROTO : REAL4\n" <<
			"mln  PROTO : REAL4\n" <<
			"msin PROTO : REAL4\n" <<
			"msqr PROTO : REAL4\n" <<
			"mtan PROTO : REAL4\n" <<
			"print1 PROTO : DWORD\n" <<
			"print2 PROTO : DWORD\n" <<
			"print3 PROTO : REAL4\n";
		*out << "\n.stack 4096\n";
		PrintLiterals(out, ids);
		PrintId(out, ids);
		DecideBlocks(out, ids, lex, DLib);
		
	}

	void PrintLiterals(std::ofstream* out, IT::IdTable& ids)
	{
		int litCounter = 0;
		char* buffer = new char[20];
		*out << ".const\n";
		for (short i = 0; i < ids.size; i++)
		{
			if (ids.table[i].idtype == IT::IDTYPE::L)
			{
				switch (ids.table[i].iddatatype)
				{
				case IT::IDDATATYPE::BOOL :
					*out << LBool(litCounter++) << ids.table[i].value.vbool << std::endl;
					break;
				case IT::IDDATATYPE::INT :
					*out << LInt(litCounter++) << ids.table[i].value.vint << std::endl;
					break;
				case IT::IDDATATYPE::FLOAT:
					
					snprintf(buffer, sizeof buffer, "%f", ids.table[i].value.vfloat);
					if (strstr(buffer, "."))
						*out << LFloat(litCounter++) << buffer << std::endl;
					else
						*out << LFloat(litCounter++) << buffer << ".0" << std::endl;
					break;
				case IT::IDDATATYPE::STR :
					*out << LStr(litCounter++) << "'" << ids.table[i].value.vstr.str << "', 0" << std::endl;
					break;
				default:
					break;
				}
			}
		}
	}

	void PrintId(std::ofstream* out, IT::IdTable& ids)
	{
		*out << ".data\n";
		*out << "\ttempReal4 REAL4 0.0" << std::endl;
		for (short i = 0; i < ids.size; i++)
		{
			if (ids.table[i].idtype == IT::IDTYPE::V)
			{
				switch (ids.table[i].iddatatype)
				{
				case IT::IDDATATYPE::BOOL:
					*out << ids.table[i].vis <<  VBool(ids.table[i].id) << "?" << std::endl;
					break;
				case IT::IDDATATYPE::INT:
					*out << ids.table[i].vis << VInt(ids.table[i].id) << "?" << std::endl;
					break;
				case IT::IDDATATYPE::FLOAT:
					*out << ids.table[i].vis << VFloat(ids.table[i].id) << "?" << std::endl;
					break;
				case IT::IDDATATYPE::STR:
					*out << ids.table[i].vis << VStr(ids.table[i].id) << "?" << std::endl;
					break;
				default:
					break;
				}
			}
		}
	}

	void DecideBlocks(std::ofstream* out, IT::IdTable& ids, LT::LexTable& lex, DefaultLib::DL& DLib)
	{
		*out << ".code" << std::endl;
		int literal_counter = 0;
		bool flagFunc   = false,
			 flagReturn = false,
			 flagMain   = false,
			 flagIf     = false,
			 flagElse   = false,
			 flagWhile	= false;
		int  ifcounter  = 0,
			whcounter   = 0,
			dlibcounter = 0;
		char* fid;
		for (int i = 0; i < lex.size ; i++)
		{
			switch (lex.table[i].lexema[0])
			{
			case LEX_FUNCTION:
				i++;
				fid = ids.table[lex.table[i++].idxTI].id;
				*out << fid << " PROC" << "\t";
				for (i; lex.table[i].lexema[0] && (lex.table[i].lexema[0] != LEX_LEFTBRACE); i++)
				{
					flagFunc = true;
					if (lex.table[i].lexema[0] == LEX_LEFTTHESIS ||
						lex.table[i].lexema[0] == LEX_RIGHTHESIS) {
					}
					else
					{
						switch (lex.table[i].lexema[0])
						{
						case LEX_COMMA:
							*out << LEX_COMMA << " ";
							break;
						case LEX_INTEGER:
							break;
						case LEX_ID:
							*out << " " << ids.table[lex.table[i].idxTI].vis << ids.table[lex.table[i].idxTI].id << " : ";
							switch (ids.table[i].iddatatype)
							{
							case IT::IDDATATYPE::BOOL:
								*out << "BYTE";
								break;
							case IT::IDDATATYPE::INT:
								*out << "DWORD";
								break;
							case IT::IDDATATYPE::FLOAT:
								*out << "REAL4";
								break;
							case IT::IDDATATYPE::STR:
								*out << "BYTE";
								break;
							default:
								break;
							}
							break;
						default:
							break;
						}
					}
				}
				*out << std::endl;
				DecideCode(out, ids, lex, i, literal_counter, whcounter, ifcounter, DLib, dlibcounter);
				*out << fid << " ENDP" << std::endl;
				break;
			case LEX_MAIN:
				*out << "main PROC" << std::endl;
				DecideCode(out, ids, lex, i, literal_counter, whcounter, ifcounter, DLib, dlibcounter);
				*out << "\tpush 0" << std::endl;
				*out << "\tcall ExitProcess" << std::endl;
				*out << "main ENDP" << std::endl;
				*out << "end main" << std::endl;
				break;
			default:
				break;
			}
		}
	}

	void PushLiteral(std::ofstream* out, IT::IdTable& ids, LT::LexTable& lex, int& pos, int& literal_counter)
	{
		switch (ids.table[lex.table[pos].idxTI].iddatatype)
		{
		case IT::IDDATATYPE::STR:
			*out << "\tPUSH OFFSET\tL" << literal_counter++ << std::endl;
			break;
		case IT::IDDATATYPE::FLOAT:
			*out << "\tPUSH \tL" << literal_counter++ << std::endl;
			break;
		default:
			*out << "\tPUSH\tL" << literal_counter++ << std::endl;
			break;
		}
	}

	void PushVar(std::ofstream* out, IT::IdTable& ids, LT::LexTable& lex, int& pos)
	{
		switch (ids.table[lex.table[pos].idxTI].iddatatype)
		{
		case IT::IDDATATYPE::STR:
			*out << "\tPUSH\t" << ids.table[lex.table[pos].idxTI].vis << ids.table[lex.table[pos].idxTI].id << std::endl;
			break;
		case IT::IDDATATYPE::FLOAT :
			*out << "\tPUSH\t" <<  ids.table[lex.table[pos].idxTI].vis << ids.table[lex.table[pos].idxTI].id << std::endl;
			break;
		default:
			*out << "\tPUSH\t" << ids.table[lex.table[pos].idxTI].vis << ids.table[lex.table[pos].idxTI].id << std::endl;
			break;
		}
	}

	char* GetOperand(std::ofstream* out, IT::IdTable& ids, LT::LexTable& lex, int pos, int& literal_counter)
	{
		char* buffer = new char[20];
		char* buff2 = new char[20];
		switch (ids.table[lex.table[pos].idxTI].idtype)
		{
			case IT::IDTYPE::L:
				strcpy(buffer, _itoa(literal_counter++, buff2, 10));
				strcpy(buff2, "L");
				return strcat(buff2, buffer);
				break;
			case IT::IDTYPE::V:
				strcpy(buffer, ids.table[lex.table[pos].idxTI].vis);
				strcat(buffer, ids.table[lex.table[pos].idxTI].id);
				return buffer;
				break;
			case IT::IDTYPE::P:
				strcpy(buffer, ids.table[lex.table[pos].idxTI].vis);
				strcat(buffer, ids.table[lex.table[pos].idxTI].id);
				return buffer;
				break;

		default:
			return "";
			break;
		}
	}

	void DecideCode(std::ofstream* out, IT::IdTable& ids, LT::LexTable& lex, int& pos, int& literal_counter, int& whcounter, int& ifcounter, DefaultLib::DL& DLib, int& DLibCounter)
	{
		int j;
		int result_position, funcPos;
		char* operand1 = new char[15];
		char* operand2 = new char[15];
		bool flagRet = true;
		for (pos; lex.table[pos].lexema[0] != LEX_BRACELET; pos++)
		{
			switch (lex.table[pos].lexema[0])
			{
			case LEX_EQUALITY:

				Polish::PolishNotation(pos, lex, ids);
				result_position = pos - 1;

				for (pos; lex.table[pos].lexema[0] &&
					(lex.table[pos].lexema[0] != LEX_SEMICOLON); pos++)
				{
					switch (ids.table[lex.table[result_position].idxTI].iddatatype)
					{
					case IT::IDDATATYPE::INT :
						switch (lex.table[pos].lexema[0])
						{
						case LEX_ID:
							switch (ids.table[lex.table[pos].idxTI].idtype)
							{
							case IT::IDTYPE::F:
								funcPos = pos++;
								while (lex.table[pos].lexema[0] != LEX_RIGHTHESIS &&
									lex.table[pos].lexema[0] != IN_CODE_ENDL)
								{
									switch (lex.table[pos].lexema[0])
									{
									case LEX_ID:
										PushVar(out, ids, lex, pos);
										break;
									case LEX_LITERAL:
										PushLiteral(out, ids, lex, pos, literal_counter);
										break;
									default:
										break;
									}
									pos++;
								}
								*out << "\tcall " << ids.table[lex.table[funcPos].idxTI].id << std::endl;
								*out << "\tPUSH EAX" << std::endl;
								break;
							case IT::IDTYPE::V:
								PushVar(out, ids, lex, pos);
								break;
							default:
								break;
							}
							break;
						case LEX_LITERAL:
							PushLiteral(out, ids, lex, pos, literal_counter);
							break;
						case LEX_PLUS:
							*out << "\tPOP\t EDX" << std::endl;
							*out << "\tPOP\t EBX" << std::endl;
							*out << "\tADD\t EBX, EDX" << std::endl;
							*out << "\tPUSH\t EBX" << std::endl;
							break;
						case LEX_MINUS:
							if (lex.table[pos - 1].idxTI != (-1)) {
								*out << "\tPOP\t EDX" << std::endl;
								*out << "\tPOP\t EBX" << std::endl;
								*out << "\tSUB\t EBX, EDX" << std::endl;
								*out << "\tPUSH\t EBX" << std::endl;
							} else {
								ERROR_THROW_IN(128, lex.table[pos-1].sn, 0);
							}
							break;
						case LEX_STAR:
							*out << "\tPOP\t EBX" << std::endl;
							*out << "\tPOP\t EAX" << std::endl;
							*out << "\tMOV\t EDX, 0" << std::endl;
							*out << "\tMUL\t EBX" << std::endl;
							*out << "\tMOV\t EBX, EAX" << std::endl;
							*out << "\tPUSH\t EAX" << std::endl;
							break;
						case LEX_DIRSLASH:
							*out << "\tPOP\t EBX" << std::endl;
							*out << "\tPOP\t EAX" << std::endl;
							*out << "\tMOV\t EDX, 0" << std::endl;
							*out << "\tDIV\t EBX" << std::endl;
							*out << "\tMOV\t EBX, EAX" << std::endl;
							*out << "\tPUSH\t EAX" << std::endl;
							break;
						case LEX_DLIB:
							funcPos = pos++;
							while (lex.table[pos].lexema[0] != LEX_RIGHTHESIS &&
								lex.table[pos].lexema[0] != IN_CODE_ENDL)
							{
								switch (lex.table[pos].lexema[0])
								{
								case LEX_ID:
									PushVar(out, ids, lex, pos);
									break;
								case LEX_LITERAL:
									PushLiteral(out, ids, lex, pos, literal_counter);
									break;
								default:
									break;
								}
								pos++;
							}
							*out << "\tcall " << DLib.functions[DLibCounter++] << std::endl;
							*out << "\tPUSH EAX" << std::endl;
							break;
						default:
							break;
						}
						break;
					case IT::IDDATATYPE::FLOAT:
						switch (lex.table[pos].lexema[0])
						{
						case LEX_ID:
							switch (ids.table[lex.table[pos].idxTI].idtype)
							{
							case IT::IDTYPE::F:
								funcPos = pos++;
								while (lex.table[pos].lexema[0] != LEX_RIGHTHESIS &&
									   lex.table[pos].lexema[0] != IN_CODE_ENDL)
								{
									pos++;
									switch (lex.table[pos].lexema[0])
									{
									case LEX_ID:
										PushVar(out, ids, lex, pos);
										break;
									case LEX_LITERAL:
										PushLiteral(out, ids, lex, pos, literal_counter);
										break;
									default:
										break;
									}
								}
								*out << "\tcall " << ids.table[lex.table[funcPos].idxTI].id << std::endl;
								*out << "\tMOV tempReal4, EAX" << std::endl;
								*out << "\tFLD DWORD PTR[tempReal4]" << std::endl;
								break;
							case IT::IDTYPE::V:
								*out << VFLD(ids.table[lex.table[funcPos].idxTI].id);
								break;
							default:
								break;
							}
							break;
						case LEX_LITERAL:
							*out << LFLD(literal_counter++);
							break;
						case LEX_PLUS:
							*out << "\tFADDP " << std::endl;
							break;
						case LEX_MINUS:
							*out << "\tFSUB " << std::endl;
							break;
						case LEX_STAR:
							*out << "\tFMUL " << std::endl;
							break;
						case LEX_DIRSLASH:
							*out << "\tFDIV " << std::endl;
							break;
						case LEX_DLIB:
							funcPos = pos++;
							while (lex.table[pos].lexema[0] != LEX_RIGHTHESIS &&
								lex.table[pos].lexema[0] != IN_CODE_ENDL)
							{
								pos++;
								switch (lex.table[pos].lexema[0])
								{
								case LEX_ID:
									PushVar(out, ids, lex, pos);
									break;
								case LEX_LITERAL:
									PushLiteral(out, ids, lex, pos, literal_counter);
									break;
								default:
									break;
								}
							}
							*out << "\tcall " << DLib.functions[DLibCounter++] << std::endl;
							*out << "\tMOV tempReal4, EAX" << std::endl;
							*out << "\tFLD DWORD PTR[tempReal4]" << std::endl;	
							break;
						default:
							break;	
						}
						break;
					case IT::IDDATATYPE::STR :
						switch (lex.table[pos].lexema[0])
						{
						case LEX_ID :
							switch (ids.table[lex.table[pos].idxTI].idtype)
							{
							case IT::IDTYPE::F:
								funcPos = pos++;
								while (lex.table[pos].lexema[0] != LEX_RIGHTHESIS &&
									   lex.table[pos].lexema[0] != IN_CODE_ENDL)
								{
									pos++;
									switch (lex.table[pos].lexema[0])
									{
									case LEX_ID:
										PushVar(out, ids, lex, pos);
										break;
									case LEX_LITERAL:
										PushLiteral(out, ids, lex, pos, literal_counter);
										break;
									default:
										break;
									}
								}
								*out << "\tcall " << ids.table[lex.table[funcPos].idxTI].id << std::endl;
								*out << "\tPUSH EAX" << std::endl;
								break;
							case IT::IDTYPE::V:
								PushVar(out, ids, lex, pos);
								break;
							default:
								break;
							}
							break;
						case LEX_LITERAL :
							PushLiteral(out, ids, lex, pos, literal_counter);
							break;
						case LEX_DLIB:
							funcPos = pos++;
							while (lex.table[pos].lexema[0] != LEX_RIGHTHESIS &&
								lex.table[pos].lexema[0] != IN_CODE_ENDL)
							{
								pos++;
								switch (lex.table[pos].lexema[0])
								{
								case LEX_ID:
									PushVar(out, ids, lex, pos);
									break;
								case LEX_LITERAL:
									PushLiteral(out, ids, lex, pos, literal_counter);
									break;
								default:
									break;
								}
							}
							*out << "\tcall " << DLib.functions[DLibCounter++] << std::endl;
							*out << "\tPUSH EAX" << std::endl;
							break;
						default:
							break;
						}
					default:
						break;
					}
				}
				switch (ids.table[lex.table[result_position].idxTI].iddatatype)
				{
				case IT::IDDATATYPE::FLOAT :
					*out << "\tFSTP " << ids.table[lex.table[result_position].idxTI].vis << ids.table[lex.table[result_position].idxTI].id << std::endl;
					break;
				case IT::IDDATATYPE::INT :
					*out << "\tPOP\tEAX\n\tMOV\t" << ids.table[lex.table[result_position].idxTI].vis << ids.table[lex.table[result_position].idxTI].id << ", EAX" << std::endl;
					break;
				case IT::IDDATATYPE::STR:
					*out << "\tPOP " << ids.table[lex.table[result_position].idxTI].vis << ids.table[lex.table[result_position].idxTI].id << std::endl;
					break;
				default:
					break;
				}

				break;
			case LEX_IF:
				while (flagRet)
				{
					switch (lex.table[pos].lexema[0])
					{
					case LEX_EQUALITY:
						strcpy(operand1, GetOperand(out, ids, lex, pos-1, literal_counter));
						strcpy(operand2, GetOperand(out, ids, lex, pos+1, literal_counter));
						*out << "\tMOV EAX, " << operand1 << std::endl;
						*out << "\tcmp EAX, " << operand2 << std::endl;
						*out << "\tje if0" << ifcounter << std::endl;
						*out << "\tja if0end" << ifcounter << std::endl;
						*out << "\tjb if0end" << ifcounter << std::endl;
						*out << "if0" << ifcounter << ":" << std::endl;
						pos += 2;
						DecideCode(out, ids, lex, pos, literal_counter, whcounter, ifcounter, DLib, DLibCounter);
						*out << "if0end" << ifcounter << ":" << std::endl;
						flagRet = false;
						break;
					case LEX_MORE:
						strcpy(operand1, GetOperand(out, ids, lex, pos-1, literal_counter));
						strcpy(operand2, GetOperand(out, ids, lex, pos+1, literal_counter));
						*out << "\tMOV EAX, " << operand1 << std::endl;
						*out << "\tcmp EAX, " << operand2 << std::endl;
						*out << "\tja if0" << ifcounter << std::endl;
						*out << "\tje if0end" << ifcounter << std::endl;
						*out << "\tjb if0end" << ifcounter << std::endl;
						*out << "\tif0" << ifcounter << ":" << std::endl;
						pos += 2;
						DecideCode(out, ids, lex, pos, literal_counter, whcounter, ifcounter, DLib, DLibCounter);
						*out << "if0end" << ifcounter << ":" << std::endl;
						flagRet = false;
						break;
					case LEX_LESS:
						strcpy(operand1, GetOperand(out, ids, lex, pos-1, literal_counter));
						strcpy(operand2, GetOperand(out, ids, lex, pos+1, literal_counter));
						*out << "\tMOV EAX, " << operand1 << std::endl;
						*out << "\tcmp EAX, " << operand2 << std::endl;
						*out << "\tjb if0" << ifcounter << std::endl;
						*out << "\tja if0end" << ifcounter << std::endl;
						*out << "\tje if0end" << ifcounter << std::endl;
						*out << "if0" << ifcounter << ":" << std::endl;
						pos += 2;
						DecideCode(out, ids, lex, pos, literal_counter, whcounter, ifcounter, DLib, DLibCounter);
						*out << "if0end" << ifcounter << ":" << std::endl;
						flagRet = false;
						break;
					default:
						break;
					}
					pos++;
				}
				flagRet = true;
				pos--;
				ifcounter++;
				break;
			case LEX_WHILE:
				*out << "while" << whcounter << ":" << std::endl;
				while (flagRet)
				{
					switch (lex.table[pos].lexema[0])
					{
					case LEX_EQUALITY:
						strcpy(operand1, GetOperand(out, ids, lex, pos-1, literal_counter));
						strcpy(operand2, GetOperand(out, ids, lex, pos+1, literal_counter));
						*out << "\tMOV EAX, " << operand1 << std::endl;
						*out << "\tcmp EAX, " << operand2 << std::endl;
						*out << "\tje whileblock" << whcounter << std::endl;
						*out << "\tja whilend" << whcounter << std::endl;
						*out << "\tjb whilend" << whcounter << std::endl;
						*out << "whileblock" << whcounter << ":" << std::endl;
						pos += 2;
						DecideCode(out, ids, lex, pos, literal_counter, whcounter, ifcounter, DLib, DLibCounter);
						*out << "\tjmp while" << whcounter << std::endl;
						*out << "whilend" << whcounter << ":" << std::endl;
						flagRet = false;
						break;
					case LEX_MORE:
						strcpy(operand1, GetOperand(out, ids, lex, pos-1, literal_counter));
						strcpy(operand2, GetOperand(out, ids, lex, pos+1, literal_counter));
						*out << "\tMOV EAX, " << operand1 << std::endl;
						*out << "\tcmp EAX, " << operand2 << std::endl;
						*out << "\tja whileblock" << whcounter << std::endl;
						*out << "\tje whilend" << whcounter << std::endl;
						*out << "\tjb whilend" << whcounter << std::endl;
						*out << "whileblock" << whcounter << ":" << std::endl;
						pos += 2;
						DecideCode(out, ids, lex, pos, literal_counter, whcounter, ifcounter, DLib, DLibCounter);
						*out << "\tjmp while" << whcounter << std::endl;
						*out << "whilend" << whcounter << ":" << std::endl;
						flagRet = false;
						break;
					case LEX_LESS:
						strcpy(operand1, GetOperand(out, ids, lex, pos-1, literal_counter));
						strcpy(operand2, GetOperand(out, ids, lex, pos+1, literal_counter));
						*out << "\tMOV EAX, " << operand1 << std::endl;
						*out << "\tcmp EAX, " << operand2 << std::endl;
						*out << "\tjb whileblock" << whcounter << std::endl;
						*out << "\tja whilend" << whcounter << std::endl;
						*out << "\tje whilend" << whcounter << std::endl;
						*out << "whileblock" << whcounter << ":" << std::endl;
						pos += 2;
						DecideCode(out, ids, lex, pos, literal_counter, whcounter, ifcounter, DLib, DLibCounter);
						*out << "\tjmp while" << whcounter << std::endl;
						*out << "whilend" << whcounter << ":" << std::endl;
						flagRet = false;
						break;
					default:
						break;
					}
					pos++;
				}
				flagRet = true;
				pos--;
				ifcounter++;
				break;
			case LEX_RETURN:
				switch (ids.table[lex.table[++pos].idxTI].iddatatype) {
				case IT::IDDATATYPE::INT:
					*out << "\tMOV EAX, " << ids.table[lex.table[pos].idxTI].vis << ids.table[lex.table[pos].idxTI].id << std::endl; // �������� ��� float
					*out << "\tret\n";
					break;
				case IT::IDDATATYPE::FLOAT:
					*out << "\tMOV EAX, OFFSET " << ids.table[lex.table[pos].idxTI].vis << ids.table[lex.table[pos].idxTI].id << std::endl;
					*out << "\tret\n";
					break;
				case IT::IDDATATYPE::STR:
					*out << "\tMOV EAX, OFFSET " << ids.table[lex.table[pos].idxTI].vis << ids.table[lex.table[pos].idxTI].id << std::endl;
					*out << "\tret\n";
					break;
				default:
					break;
				}
				break;
			case LEX_PRINT:
				pos++;
				switch (ids.table[lex.table[pos].idxTI].idtype) {
				case IT::IDTYPE::L:
					PushLiteral(out, ids, lex, pos, literal_counter);
					break;
				default:
					PushVar(out, ids, lex, pos);
					break;
				}
				*out << "\tcall print" << ids.table[lex.table[pos].idxTI].iddatatype << std::endl;
				break;
			default:
				break;
			}
		}
		return;
	}
}