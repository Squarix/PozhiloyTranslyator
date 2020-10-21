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
		result.end_lex = cur;
		if (cur < lextable.size) {
			cur--;
			result.end_lex = cur;
		}
		while (cur > 0 && is_lex_allowed(lextable.table[cur].lexema[0])) // пока не встретили начало списка лексем или не встретили запрещенную лексему
			cur--;
		if (is_lex_allowed(lextable.table[cur].lexema[0])) {
			result.start_lex = cur;
		}
		else {
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
			idtable.table[lex.idxTI].func_param_count = comma_count + 1;
			comma_count = 0;
		}
		else {
			polish_notation[pol_length++] = lex;
		}
	}

	bool PolishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable)
	{
		Lex_Range range = find_lex_range(lextable_pos, lextable); // ищем границы для преобразования в польскую запись

		if (range.end_lex - range.start_lex <= 1) {
			return false; // если в интервале только одна или две лексемы, то такое выражение нельзя преобразовать в польскую запись
		}

		LT::Entry* polish_notation = new LT::Entry[lextable.size]; // сюда сохраняем результирующую польскую нотацию
		int pol_length = 0;

		Pol_Stack st; // стек для алгоритма польской нотации
		st.top = 0; // st.top - указывает на верхнюю свободнюю ячейку

		int comma_count	   = 0;
		int thesis_counter = 0;
		bool is_function   = false;
		for (int i = 0; i < range.start_lex; i++)
			polish_notation[pol_length++] = lextable.table[i]; // сохраняеме лексемы до range.start_lex
		for (int i = range.start_lex; i <= range.end_lex; i++)
		{
			switch (lextable.table[i].lexema[0])
			{
			case LEX_LEFTTHESIS:
				if (is_function) {
					polish_notation[pol_length++] = lextable.table[i];
				} else {
					st.stack[st.top++] = i;
					thesis_counter++;
				}
				break;
			case LEX_LITERAL:
				polish_notation[pol_length++] = lextable.table[i];
				break;
			case LEX_DLIB:
				is_function = true;
				polish_notation[pol_length++] = lextable.table[i];
				break;
			case LEX_RIGHTHESIS:
				if (is_function) {
					polish_notation[pol_length++] = lextable.table[i];
					is_function = false;
				}
				else {
					while (st.top >= 1 && lextable.table[st.stack[st.top - 1]].lexema[0] != LEX_LEFTTHESIS)
					{
						polish_notation[pol_length++] = lextable.table[st.stack[st.top - 1]];
						st.top--;
					}
					if (!st.top)
					{
						return false;
					}
					st.top--;
					thesis_counter++;
				}
				break;
			case LEX_ID:
				if (idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::F)
				{
					is_function = true;

				}
				polish_notation[pol_length++] = lextable.table[i];
				break;
			case LEX_COMMA:
				if (is_function) {
					polish_notation[pol_length++] = lextable.table[i];
				}
				else {
					thesis_counter++;
				}
				break;
			default:
				int lex_priority = get_priority(lextable.table[i].lexema[0]);
				while (st.top >= 1 && get_priority(lextable.table[st.stack[st.top - 1]].lexema[0]) >= lex_priority)
				{
					polish_notation[pol_length++] = lextable.table[st.stack[st.top - 1]];
					st.top--;
				}
				st.stack[st.top++] = i;
				break;
			}
		}
		while (st.top)
		{
			if (lextable.table[st.stack[st.top - 1]].lexema[0] == LEX_LEFTTHESIS || lextable.table[st.stack[st.top - 1]].lexema[0] == LEX_RIGHTHESIS)
				st.top--;
			else
			{
				polish_notation[pol_length++] = lextable.table[st.stack[st.top - 1]];
				st.top--;
			}
		}


		for (int i = range.end_lex + 1; i < lextable.size; i++)
		{
			polish_notation[pol_length++] = lextable.table[i];
		}
		
	//	pol_length -= thesis_counter;
		lextable.size -= thesis_counter;
		for (int i = 0; i < pol_length; i++)
			lextable.table[i] = polish_notation[i];

		// обнуляем лишние лексемы
		delete[] polish_notation;
		return true;
	}
}