#pragma once
#include "In.h"

#define N_GRAPHS 38
#define FST_SEPARATORS 2,\
	Fst::NODE(11, Fst::RELATION(';',1), Fst::RELATION('=',1),\
				  Fst::RELATION(',',1), Fst::RELATION('{',1),\
				  Fst::RELATION('}',1), Fst::RELATION('(',1),\
				  Fst::RELATION(')',1), Fst::RELATION('*',1),\
				  Fst::RELATION('+',1), Fst::RELATION('-',1),\
				  Fst::RELATION('/',1)),\
	Fst::NODE()

#define FST_ARYTHM 2,\
	Fst::NODE(11, Fst::RELATION('*',1), Fst::RELATION('+',1),\
			      Fst::RELATION('-',1), Fst::RELATION('/',1)),\
	Fst::NODE()
#define FST_ARYTHM_PLUS 2,\
	Fst::NODE(11, Fst::RELATION('+',1)),\
	Fst::NODE()

#define FST_ARYTHM_MINUS 2,\
	Fst::NODE(11, Fst::RELATION('-',1)),\
	Fst::NODE()

#define FST_ARYTHM_MULT 2,\
	Fst::NODE(11, Fst::RELATION('*',1)),\
	Fst::NODE()

#define FST_MORE 2,\
	Fst::NODE(11, Fst::RELATION('>',1)),\
	Fst::NODE()

#define FST_LESS 2,\
	Fst::NODE(11, Fst::RELATION('<',1)),\
	Fst::NODE()

#define FST_ARYTHM_DIV 2,\
	Fst::NODE(11, Fst::RELATION('/',1)),\
	Fst::NODE()
#define FST_SEMICOLON 2,\
	Fst::NODE(1,Fst::RELATION(';',1)),\
	Fst::NODE()
#define FST_EQUALS 2,\
	Fst::NODE(1,Fst::RELATION('=',1)),\
	Fst::NODE()
#define FST_COMMA 2,\
	Fst::NODE(1,Fst::RELATION(',',1)),\
	Fst::NODE()
#define FST_LEFT_BRACE 2,\
	Fst::NODE(1,Fst::RELATION('{',1)),\
	Fst::NODE()
#define FST_RIGHT_BRACE 2,\
	Fst::NODE(1,Fst::RELATION('}',1)),\
	Fst::NODE()
#define FST_OPEN_PARENTHESIS 2,\
	Fst::NODE(1,Fst::RELATION('(',1)),\
	Fst::NODE()
#define FST_CLOSE_PARENTHESIS 2,\
	Fst::NODE(1,Fst::RELATION(')',1)),\
	Fst::NODE()

#define FST_SUBSTR 7, \
	Fst::NODE(1,Fst::RELATION('s',1)),\
	Fst::NODE(1,Fst::RELATION('u',2)),\
	Fst::NODE(1,Fst::RELATION('b',3)),\
	Fst::NODE(1,Fst::RELATION('s',4)),\
	Fst::NODE(1,Fst::RELATION('t',5)),\
    Fst::NODE(1,Fst::RELATION('r',6)),\
	Fst::NODE()

#define FST_STRLEN 7,\
	Fst::NODE(1,Fst::RELATION('s',1)),\
	Fst::NODE(1,Fst::RELATION('t',2)),\
	Fst::NODE(1,Fst::RELATION('d',3)),\
	Fst::NODE(1,Fst::RELATION('l',4)),\
	Fst::NODE(1,Fst::RELATION('e',5)),\
	Fst::NODE(1,Fst::RELATION('n',6)),\
	Fst::NODE()

#define FST_STRSEARCH 10,\
	Fst::NODE(1,Fst::RELATION('s',1)),\
	Fst::NODE(1,Fst::RELATION('t',2)),\
	Fst::NODE(1,Fst::RELATION('r',3)),\
	Fst::NODE(1,Fst::RELATION('s',4)),\
	Fst::NODE(1,Fst::RELATION('e',5)),\
	Fst::NODE(1,Fst::RELATION('a',6)),\
	Fst::NODE(1,Fst::RELATION('r',7)),\
	Fst::NODE(1,Fst::RELATION('c',8)),\
	Fst::NODE(1,Fst::RELATION('h',9)),\
	Fst::NODE()

#define FST_POW 4,\
	Fst::NODE(1,Fst::RELATION('d',1)),\
	Fst::NODE(1,Fst::RELATION('g',2)),\
	Fst::NODE(1,Fst::RELATION('r',3)),\
	Fst::NODE()

#define FST_MSIN 5,\
	Fst::NODE(1,Fst::RELATION('m',1)),\
	Fst::NODE(1,Fst::RELATION('s',2)),\
	Fst::NODE(1,Fst::RELATION('i',3)),\
	Fst::NODE(1,Fst::RELATION('n',4)),\
	Fst::NODE()

#define FST_MCOS 5,\
	Fst::NODE(1,Fst::RELATION('m',1)),\
	Fst::NODE(1,Fst::RELATION('c',2)),\
	Fst::NODE(1,Fst::RELATION('o',3)),\
	Fst::NODE(1,Fst::RELATION('s',4)),\
	Fst::NODE()

#define FST_MTAN 5,\
	Fst::NODE(1,Fst::RELATION('m',1)),\
	Fst::NODE(1,Fst::RELATION('t',2)),\
	Fst::NODE(1,Fst::RELATION('a',3)),\
	Fst::NODE(1,Fst::RELATION('n',4)),\
	Fst::NODE()

#define FST_MEXP 5,\
	Fst::NODE(1,Fst::RELATION('m',1)),\
	Fst::NODE(1,Fst::RELATION('e',2)),\
	Fst::NODE(1,Fst::RELATION('x',3)),\
	Fst::NODE(1,Fst::RELATION('p',4)),\
	Fst::NODE()

#define FST_MLN 4,\
	Fst::NODE(1,Fst::RELATION('m',1)),\
	Fst::NODE(1,Fst::RELATION('l',2)),\
	Fst::NODE(1,Fst::RELATION('n',3)),\
	Fst::NODE()

#define FST_MABS 5,\
	Fst::NODE(1,Fst::RELATION('m',1)),\
	Fst::NODE(1,Fst::RELATION('a',2)),\
	Fst::NODE(1,Fst::RELATION('b',3)),\
	Fst::NODE(1,Fst::RELATION('s',4)),\
	Fst::NODE()

#define FST_MSQR 5,\
	Fst::NODE(1,Fst::RELATION('m',1)),\
	Fst::NODE(1,Fst::RELATION('s',2)),\
	Fst::NODE(1,Fst::RELATION('q',3)),\
	Fst::NODE(1,Fst::RELATION('r',4)),\
	Fst::NODE()

#define FST_FORWARD_SLASH 2,\
	Fst::NODE(1,Fst::RELATION('/',1)),\
	Fst::NODE()

#define FST_INT_LITERAL 2, \
	Fst::NODE(20,	\
	Fst::RELATION('1', 0), Fst::RELATION('2', 0), Fst::RELATION('3', 0), Fst::RELATION('4', 0), Fst::RELATION('5', 0), Fst::RELATION('6', 0),\
	Fst::RELATION('7', 0), Fst::RELATION('8', 0), Fst::RELATION('9', 0), Fst::RELATION('0', 0),\
	\
	Fst::RELATION('1', 1), Fst::RELATION('2', 1), Fst::RELATION('3', 1), Fst::RELATION('4', 1), Fst::RELATION('5', 1), Fst::RELATION('6', 1),\
	Fst::RELATION('7', 1), Fst::RELATION('8', 1), Fst::RELATION('9', 1), Fst::RELATION('0', 1)),\
	Fst::NODE()

#define FST_FLOAT_LITERAL 2,	\
	Fst::NODE(21,	\
	Fst::RELATION('1', 0), Fst::RELATION('2', 0), Fst::RELATION('3', 0), Fst::RELATION('4', 0), Fst::RELATION('5', 0), Fst::RELATION('6', 0),\
	Fst::RELATION('7', 0), Fst::RELATION('8', 0), Fst::RELATION('9', 0), Fst::RELATION('0', 0), Fst::RELATION('.', 0), \
	Fst::RELATION('1', 1), Fst::RELATION('2', 1), Fst::RELATION('3', 1), Fst::RELATION('4', 1), Fst::RELATION('5', 1), Fst::RELATION('6', 1),\
	Fst::RELATION('7', 1), Fst::RELATION('8', 1), Fst::RELATION('9', 1), Fst::RELATION('0', 1), Fst::RELATION('.', 1)), \
	Fst::NODE()

#define FST_STRING_LITERAL 3, \
	Fst::NODE(1, Fst::RELATION('\'',1)),\
	Fst::NODE(64,Fst::RELATION('a',1),Fst::RELATION('b',1), \
				 Fst::RELATION('c', 1), Fst::RELATION('d', 1), \
				 Fst::RELATION('e', 1), Fst::RELATION('f', 1), \
				 Fst::RELATION('g', 1), Fst::RELATION('h', 1), \
				 Fst::RELATION('i', 1), Fst::RELATION('j', 1), \
				 Fst::RELATION('k', 1), Fst::RELATION('l', 1), \
				 Fst::RELATION('m', 1), Fst::RELATION('n', 1), \
				 Fst::RELATION('o', 1), Fst::RELATION('p', 1), \
				 Fst::RELATION('q', 1), Fst::RELATION('r', 1), \
				 Fst::RELATION('s', 1), Fst::RELATION('t', 1), \
				 Fst::RELATION('u', 1), Fst::RELATION('v', 1), \
				 Fst::RELATION('w', 1), Fst::RELATION('x', 1), \
				 Fst::RELATION('y', 1), Fst::RELATION('z', 1), \
				 Fst::RELATION('0', 1), Fst::RELATION('1',1),	\
				 Fst::RELATION('3', 1), Fst::RELATION('2',1),	\
				 Fst::RELATION('5', 1), Fst::RELATION('4',1),	\
				 Fst::RELATION('7', 1), Fst::RELATION('6',1),	\
				 Fst::RELATION('9', 1), Fst::RELATION('8',1), \
				 Fst::RELATION('A', 1),	 Fst::RELATION('B', 1), \
				 Fst::RELATION('C', 1),  Fst::RELATION('D', 1), \
				 Fst::RELATION('E', 1),  Fst::RELATION('F', 1), \
				 Fst::RELATION('G', 1),  Fst::RELATION('H', 1), \
				 Fst::RELATION('I', 1),  Fst::RELATION('J', 1), \
				 Fst::RELATION('K', 1),  Fst::RELATION('L', 1), \
				 Fst::RELATION('M', 1),  Fst::RELATION('N', 1), \
				 Fst::RELATION('O', 1),  Fst::RELATION('P', 1), \
				 Fst::RELATION('Q', 1),  Fst::RELATION('R', 1), \
				 Fst::RELATION('S', 1),  Fst::RELATION('T', 1), \
				 Fst::RELATION('U', 1),  Fst::RELATION('V', 1), \
				 Fst::RELATION('W', 1),  Fst::RELATION('X', 1), \
				 Fst::RELATION('Y', 1),  Fst::RELATION('Z', 1), \
				 Fst::RELATION(' ', 1), Fst::RELATION('\'',2)),\
	Fst::NODE()

#define FST_MAIN 5, \
	Fst::NODE(1,Fst::RELATION('m',1)),\
	Fst::NODE(1,Fst::RELATION('a',2)),\
	Fst::NODE(1,Fst::RELATION('i',3)),\
	Fst::NODE(1,Fst::RELATION('n',4)),\
	Fst::NODE()


#define FST_INTEGER 4, \
	Fst::NODE(1,Fst::RELATION('i',1)),\
	Fst::NODE(1,Fst::RELATION('n',2)),\
	Fst::NODE(1,Fst::RELATION('t',3)),\
	Fst::NODE()

#define FST_FLOAT 6, \
	Fst::NODE(1,Fst::RELATION('f',1)),\
	Fst::NODE(1,Fst::RELATION('l',2)),\
	Fst::NODE(1,Fst::RELATION('o',3)),\
	Fst::NODE(1,Fst::RELATION('a',4)),\
	Fst::NODE(1,Fst::RELATION('t',5)),\
	Fst::NODE()

#define FST_BOOL 5, \
	Fst::NODE(1,Fst::RELATION('b',1)),\
	Fst::NODE(1,Fst::RELATION('o',2)),\
	Fst::NODE(1,Fst::RELATION('o',3)),\
	Fst::NODE(1,Fst::RELATION('l',4)),\
	Fst::NODE()

#define FST_STRING 4, \
	Fst::NODE(1,Fst::RELATION('s',1)),\
	Fst::NODE(1,Fst::RELATION('t',2)),\
	Fst::NODE(1,Fst::RELATION('r',3)),\
	Fst::NODE()

#define FST_FUNCTION 9, \
	Fst::NODE(1, Fst::RELATION('f', 1)),\
    Fst::NODE(1, Fst::RELATION('u', 2)),\
    Fst::NODE(1, Fst::RELATION('n', 3)),\
    Fst::NODE(1, Fst::RELATION('c', 4)),\
    Fst::NODE(1, Fst::RELATION('t', 5)),\
    Fst::NODE(1, Fst::RELATION('i', 6)),\
    Fst::NODE(1, Fst::RELATION('o', 7)),\
    Fst::NODE(1, Fst::RELATION('n', 8)),\
    Fst::NODE()

#define FST_WHILE 6, \
	Fst::NODE(1, Fst::RELATION('w', 1)),\
    Fst::NODE(1, Fst::RELATION('h', 2)),\
    Fst::NODE(1, Fst::RELATION('i', 3)),\
    Fst::NODE(1, Fst::RELATION('l', 4)),\
    Fst::NODE(1, Fst::RELATION('e', 5)),\
	Fst::NODE()

#define FST_IF 3, \
	Fst::NODE(1, Fst::RELATION('i', 1)),\
    Fst::NODE(1, Fst::RELATION('f', 2)),\
    Fst::NODE()

#define FST_RETURN 7, \
	Fst::NODE(1,Fst::RELATION('r',1)),\
	Fst::NODE(1,Fst::RELATION('e',2)),\
	Fst::NODE(1,Fst::RELATION('t',3)),\
	Fst::NODE(1,Fst::RELATION('u',4)),\
	Fst::NODE(1,Fst::RELATION('r',5)),\
	Fst::NODE(1,Fst::RELATION('n',6)),\
	Fst::NODE()

#define FST_DECLARE 8, \
    Fst::NODE(1, Fst::RELATION('d', 1)),\
    Fst::NODE(1, Fst::RELATION('e', 2)),\
    Fst::NODE(1, Fst::RELATION('c', 3)),\
    Fst::NODE(1, Fst::RELATION('l', 4)),\
    Fst::NODE(1, Fst::RELATION('a', 5)),\
    Fst::NODE(1, Fst::RELATION('r', 6)),\
    Fst::NODE(1, Fst::RELATION('e', 7)),\
    Fst::NODE()

#define FST_PRINT 4,	\
	Fst::NODE(1, Fst::RELATION('o', 1)),\
    Fst::NODE(1, Fst::RELATION('u', 2)),\
    Fst::NODE(1, Fst::RELATION('t', 3)),\
    Fst::NODE()

#define FST_ID 2, \
	Fst::NODE(26, Fst::RELATION('a',1),  Fst::RELATION('b',1), \
				 Fst::RELATION('c', 1),  Fst::RELATION('d', 1), \
				 Fst::RELATION('e', 1),  Fst::RELATION('f', 1), \
				 Fst::RELATION('g', 1),  Fst::RELATION('h', 1), \
				 Fst::RELATION('i', 1),  Fst::RELATION('j', 1), \
				 Fst::RELATION('k', 1),  Fst::RELATION('l', 1), \
				 Fst::RELATION('m', 1),  Fst::RELATION('n', 1), \
				 Fst::RELATION('o', 1),  Fst::RELATION('p', 1), \
				 Fst::RELATION('q', 1),  Fst::RELATION('r', 1), \
				 Fst::RELATION('s', 1),  Fst::RELATION('t', 1), \
				 Fst::RELATION('u', 1),  Fst::RELATION('v', 1), \
				 Fst::RELATION('w', 1),  Fst::RELATION('x', 1), \
				 Fst::RELATION('y', 1),  Fst::RELATION('z', 1)), \
	Fst::NODE(26, Fst::RELATION('a',1),  Fst::RELATION('b',1), \
				 Fst::RELATION('c', 1),  Fst::RELATION('d', 1), \
				 Fst::RELATION('e', 1),  Fst::RELATION('f', 1), \
				 Fst::RELATION('g', 1),  Fst::RELATION('h', 1), \
				 Fst::RELATION('i', 1),  Fst::RELATION('j', 1), \
				 Fst::RELATION('k', 1),  Fst::RELATION('l', 1), \
				 Fst::RELATION('m', 1),  Fst::RELATION('n', 1), \
				 Fst::RELATION('o', 1),  Fst::RELATION('p', 1), \
				 Fst::RELATION('q', 1),  Fst::RELATION('r', 1), \
				 Fst::RELATION('s', 1),  Fst::RELATION('t', 1), \
				 Fst::RELATION('u', 1),  Fst::RELATION('v', 1), \
				 Fst::RELATION('w', 1),  Fst::RELATION('x', 1), \
				 Fst::RELATION('y', 1),  Fst::RELATION('z', 1))

namespace Fst
{
	struct RELATION //ребро:символ -> вершина графа переходов КА
	{
		char symbol; // символ перехода
		short nnode; // номер смежной вершины
		RELATION(
			char c = 0x00, // символ перехода
			short ns = NULL // новое состояние
			);
	};

	struct NODE // вершина графа переходов
	{
		short n_relation; // количество инцидентных ребер
		RELATION *relations; // инцидентные ребра
		NODE();
		NODE(
			short n, // количество инцидентных ребер
			RELATION rel, ... // список ребер
			);
	};

	struct FST // недетерминированный конечный автомат
	{
		char* string; // цепочка(строка, завершается 0х00)
		short position; // текущая позиция в цепочке
		short nstates; // количество состояний автомата
		NODE* nodes; // граф переходов : [0] - начальное состояние, [nstate-1] - конечное
		short* rstates; // возможные состояния автомата на данной позиции
		FST( 
			char* s, // цепочка(строка, завершается 0х00)
			short ns, // количество состояний автомата
			NODE n, ... // список состояний (граф переходов)
			);
		FST(short ns, NODE n, ...); //		для массива					, количество состояний автомата, список состояний(граф переходов)
		FST(char* s, FST& fst); // цепочка и константный FST
	};

	bool execute( // выполнить распознание цепочки
		FST& fst // недетерминированный КА
		);

}