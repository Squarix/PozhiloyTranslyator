#include "stdafx.h"
#include "Polish.h"

namespace Polish
{

	bool is_lex_allowed(char l)
	{
		switch (l)
		{
		case LEX_INTEGER:
		case LEX_EQUALITY:
		case LEX_FUNCTION:
		case LEX_DECLARE:
		case LEX_PRINT:
		case LEX_MAIN:
		case LEX_SEMICOLON:
		case LEX_LEFTBRACE:
		case LEX_BRACELET:
			return false;
			break;
		}
		return true;
	}

	Lex_Range find_lex_range(int lextable_pos, LT::LexTable& lextable)
	{
		Lex_Range result;
		int cur = lextable_pos;
		while (cur < lextable.size && lextable.table[cur].lexema[0] != ';') // пока не встретили конец списка лексем или не встретили лексему ';'
			cur++;
		result.end_lex = cur ;
		if (cur < lextable.size) {
			cur--;
		 	result.end_lex = cur;
		}
		while (cur > 0 && is_lex_allowed(lextable.table[cur].lexema[0])) // пока не встретили начало списка лексем или не встретили запрещенную лексему
			cur--;
		if (is_lex_allowed(lextable.table[cur].lexema[0])) {
			result.start_lex = cur;
		} else {
			result.start_lex = cur + 1;
		}
		return result;
	}

	int get_priority(char c)
	{
		for (int i = 0; i < P_LEN; i++)
			if (symbols[i] == c) {
				return priority[i];
			}
		return P_ID;
	}

	void Polish_add(LT::Entry* polish_notation, int& pol_length, int& comma_count, LT::LexTable& lextable, IT::IdTable& idtable, LT::Entry& lex)
	{
		if (lex.lexema[0] == 'i' && idtable.table[lex.idxTI].idtype == IT::IDTYPE::F) {
			polish_notation[pol_length++] = LT::Entry('@', lex.sn, lex.idxTI);
			polish_notation[pol_length++] = LT::Entry(comma_count, lex.sn, lex.idxTI);
			idtable.table[lex.idxTI].func_param_count = comma_count + 1;
			comma_count = 0;
		}
		else {
			polish_notation[pol_length++] = lex;
		}
	}

	bool PolishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable) 
	{
		Lex_Range range = find_lex_range(lextable_pos, lextable); 

		if (range.end_lex - range.start_lex <= 1) {
			return false; 
		}

		LT::Entry* polish_notation = new LT::Entry[lextable.size]; 
		int pol_length = 0;

		Pol_Stack st; // стек для алгоритма польской нотации
		st.top = 0; 

		int comma_count = 0;

		for (int i = lextable_pos; i < range.start_lex; i++)
			polish_notation[pol_length++] = lextable.table[i]; 

 		for (int i = range.start_lex; i <= range.end_lex; i++)
		{
			int lex_priority = get_priority(lextable.table[i].lexema[0]);
			if (lextable.table[i].lexema[0] == LEX_LEFTTHESIS) {
				st.stack[st.top++] = i; 
			} else if (lex_priority == P_ID) {
				Polish_add(polish_notation, pol_length, comma_count, lextable, idtable, lextable.table[i]);
			} else if (lextable.table[i].lexema[0] == LEX_RIGHTHESIS) {
				while (st.top > 0 && lextable.table[st.stack[st.top - 1]].lexema[0] != LEX_LEFTTHESIS) { 
					polish_notation[pol_length++] = lextable.table[st.stack[st.top - 1]]; 
					st.top--;
				}
				if (st.top == 0) {
					delete[] polish_notation;
					return false;
				}
				st.top--;
			} else {
				while (st.top > 0 && get_priority(lextable.table[st.stack[st.top - 1]].lexema[0]) >= lex_priority) {
					polish_notation[pol_length++] = lextable.table[st.stack[st.top - 1]];
					st.top--;
				}
				if (lextable.table[i].lexema[0] != LEX_COMMA) {
					st.stack[st.top++] = i; 
				}
				else {
					comma_count++;
				}
			}
		}

		while (st.top > 0) {
			if (lextable.table[st.stack[st.top - 1]].lexema[0] == '(') {
				// лишняя открывающая скобка
				delete[] polish_notation;
				return false;
			}
			Polish_add(polish_notation, pol_length, comma_count, lextable, idtable, lextable.table[st.stack[st.top - 1]]);
			st.top--;
		}

		

		// копирование результатов работы алгоритма польской нотации поверх оригинальной таблицы лексем
		for (int i = 0, j = lextable_pos; i < pol_length; i++, j++)
			lextable.table[j] = polish_notation[i];
		// обнуляем лишние лексемы
		for (int i = lextable_pos + pol_length; i <= range.end_lex + 1; i++)
			lextable.table[i].lexema[0] = ' ';
		
		
		return true;
	}
}