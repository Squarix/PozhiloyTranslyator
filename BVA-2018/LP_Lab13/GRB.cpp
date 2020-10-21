#include "stdafx.h"
#include "GRB.h"
#define GRB_ERROR_SERIES 120

typedef short GRBALPHABET;
namespace GRB
{
#define NS(n) GRB::Rule::Chain::N(n)
#define TS(n) GRB::Rule::Chain::T(n)

	Greibach greibach(NS('S'), TS('$'), 9,
		Rule(NS('S'), GRB_ERROR_SERIES + 0, 2, // программные блоки: main{...}; | type function identifier(params list) {...};
			Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')), // tfi(F){NrE;};S
			Rule::Chain(4, TS('m'), TS('{'), NS('N'), TS('}')) // m{NrE;};
			//Rule::Chain(9, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'),	TS(';'), TS('}'), TS(';'), NS('S')), // m{NrE;};S

			//Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')), // tfi(F){NrE;};
		),
		Rule(NS('N'), GRB_ERROR_SERIES + 1, 17, // операторы: define type identifier; | identifier = expression; | ...
			Rule::Chain(5, TS('d'), TS('t'), TS('i'), TS(';'), NS('N')), //dti;N
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')), //i=E;N
			Rule::Chain(7, TS('d'), TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')), //dti=E;N

			Rule::Chain(8, TS('w'), TS('('), NS('K'), TS(')'), TS('{'), NS('N'), TS('}'), NS('N')), //
			Rule::Chain(8, TS('c'), TS('('), NS('K'), TS(')'), TS('{'), NS('N'), TS('}'), NS('N')), //
			Rule::Chain(4, TS('r'), NS('E'), TS(';'), NS('N')), //rE;N
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')), //i=E;N

			Rule::Chain(4, TS('d'), TS('t'), TS('i'), TS(';')), //dti;
			Rule::Chain(3, TS('r'), NS('E'), TS(';')), //rE;
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')), //i=E;

			Rule::Chain(3, TS('p'), TS('i'), TS(';')), //pi;
			Rule::Chain(4, TS('p'), TS('i'), TS(';'), NS('N')), //pi;N
			Rule::Chain(3, TS('p'), TS('l'), TS(';')), //pl;
			Rule::Chain(4, TS('p'), TS('l'), TS(';'), NS('N')), //pl;N

			Rule::Chain(6, TS('d'), TS('t'), TS('i'), TS('='), NS('E'), TS(';')), //dti=E;

			Rule::Chain(7, TS('c'), TS('('), NS('K'), TS(')'), TS('{'), NS('N'), TS('}')), //
			Rule::Chain(7, TS('w'), TS('('), NS('K'), TS(')'), TS('{'), NS('N'), TS('}')) //

		),
		Rule(NS('E'), GRB_ERROR_SERIES + 2, 9, // выражения: (identifier + literal)*function(params)
			Rule::Chain(2, TS('i'), NS('M')), //iM
			Rule::Chain(2, TS('l'), NS('M')), //lM
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')), //(E)M
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M')), //i(W)M

			Rule::Chain(1, TS('i')), //i

			Rule::Chain(1, TS('l')), //l

			Rule::Chain(3, TS('('), NS('E'), TS(')')), //(E)

			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')), //i(W)
			Rule::Chain(4, TS('z'), TS('('), NS('W'), TS(')')) //z(W)

		),
		Rule(NS('F'), GRB_ERROR_SERIES + 3, 2, // список параметров функции в ее определении
			Rule::Chain(2, TS('t'), TS('i')), //ti
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F')) //ti,F
		),
		Rule(NS('W'), GRB_ERROR_SERIES + 4, 4, // список параметров функции при вызове
			Rule::Chain(1, TS('i')), //i
			Rule::Chain(3, TS('i'), TS(','), NS('W')), //i,W

			Rule::Chain(1, TS('l')), //l
			Rule::Chain(3, TS('l'), TS(','), NS('W')) //l,W
		),
		Rule(NS('M'), GRB_ERROR_SERIES + 5, 4, // вспомогательный нетерминал для 'E', позволяет рекурсивно определять составные выражения
			Rule::Chain(2, TS('+'), NS('E')), // +E
			Rule::Chain(2, TS('-'), NS('E')), // -E
			Rule::Chain(2, TS('*'), NS('E')), // *E
			Rule::Chain(2, TS('/'), NS('E')) // /E
		),
		Rule(NS('K'), GRB_ERROR_SERIES + 6, 9,
			Rule::Chain(3, TS('i'), TS('>'), TS('i')),
			Rule::Chain(3, TS('i'), TS('<'), TS('i')),
			Rule::Chain(3, TS('i'), TS('='), TS('i')),
			Rule::Chain(3, TS('l'), TS('>'), TS('i')),
			Rule::Chain(3, TS('l'), TS('<'), TS('i')),
			Rule::Chain(3, TS('l'), TS('='), TS('i')),
			Rule::Chain(3, TS('i'), TS('>'), TS('l')),
			Rule::Chain(3, TS('i'), TS('<'), TS('l')),
			Rule::Chain(3, TS('i'), TS('='), TS('l'))
		)
	);

	Rule::Chain::Chain(short psize, GRBALPHABET s, ...)
	{
		nt = new GRBALPHABET[size = psize];
		int* p = (int*)&s;
		for (short i = 0; i < psize; ++i)
			nt[i] = (GRBALPHABET)p[i];
	};

	Rule::Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...)
	{
		nn = pnn;
		iderror = piderror;
		chains = new Chain[size = psize];
		Chain* p = &c;
		for (int i = 0; i < size; ++i)
			chains[i] = p[i];
	};


	Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottom, short psize, Rule r, ...)
	{
		startN = pstartN;
		stbottomT = pstbottom;
		rules = new Rule[size = psize];
		Rule* p = &r;
		for (int i = 0; i < size; ++i)
			rules[i] = p[i];
	}

	Greibach getGreibach()
	{
		return greibach;
	}

	short Greibach::getRule(GRBALPHABET pnn, Rule& prule)
	{
		short rc = -1;
		short k = 0;
		while (k < size && rules[k].nn != pnn)
			++k;
		if (k < size)
			prule = rules[rc = k];
		return rc;
	}

	Rule Greibach::getRule(short n)
	{
		Rule rc;
		if (n < size)
			rc = rules[n];
		return rc;
	};

	char* Rule::getCRule(char* b, short nchain)
	{
		char bchain[200];
		b[0] = Chain::alphabet_to_char(nn);
		b[1] = '-';
		b[2] = '>';
		b[3] = 0x00;
		chains[nchain].getCChain(bchain);
		strcat_s(b, sizeof(bchain) + 5, bchain);
		return b;
	};

	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j)
	{
		short rc = -1;
		while (j < size && chains[j].nt[0] != t)
			++j;
		rc = (j < size ? j : -1);
		if (rc >= 0)
			pchain = chains[rc];
		return rc;
	}

	char* Rule::Chain::getCChain(char* b)
	{
		for (int i = 0; i < size; ++i)
			b[i] = alphabet_to_char(nt[i]);
		b[size] = 0x00;
		return b;
	}
}