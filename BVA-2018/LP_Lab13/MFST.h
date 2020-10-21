#pragma once
#include "stdafx.h"
#include "GRB.h"
#include <stack>
#include "LT.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Log.h"

#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3
typedef std::stack<short> MFSTSTSTACK;
#define MFST_TRACE_START	*log.stream << std::setw( 4) << std::left << " Øàã" << ':'\
										<< std::setw(20) << std::left << " Ïðàâèëî "\
										<< std::setw(30) << std::left << " Âõîäíàÿ ëåíòà"\
										<< std::setw(20) << std::left << " Ñòåê" << std::endl;


namespace MFST
{
	struct MfstState				
	{
		short lenta_position;		
		short nrulechain;			
		short nrule;				
		MFSTSTSTACK st;				
		MfstState();
		MfstState(short pposition, MFSTSTSTACK pst, short pnrulechain);
		MfstState(
			short pposition,       
			MFSTSTSTACK pst,       
			short pnrule,         
			short pnrulechain     
		);
	};

	struct Mfst
	{

		enum RC_STEP {						
			NS_OK,					
			NS_NORULE,				
			NS_NORULECHAIN,			
			NS_ERROR,				
			TS_OK,					
			TS_NOK,					
			LENTA_END,				
			SURPRISE				
		};

		struct MfstDiagnosis		
		{
			short lenta_position;		
			RC_STEP rc_step;				
			short nrule;					
			short nrule_chain;			
			MfstDiagnosis();
			MfstDiagnosis(			 
				short plenta_position,	
				RC_STEP prc_step,		
				short pnrule,			
				short pnrule_chain		
			);
		} diagnosis[MFST_DIAGN_NUMBER];

		GRBALPHABET* lenta;
		int FST_TRACE_n = 0;
		short lenta_position;
		short nrule;
		short nrulechain;
		short lenta_size;
		GRB::Greibach grebach;
		LT::LexTable lexTable;
		MFSTSTSTACK st;
		std::stack<MfstState> storestate;
		Mfst();
		Mfst(LT::LexTable& lexTable, GRB::Greibach pgrebach);
		char* getCSt(char* buf);
		char* getCLenta(char* buf, short pos, short n = 25);
		char* getDiagnosis(short n, char* buf);
		bool savestate(Log::LOG log);
		bool restate(Log::LOG log);
		bool push_chain(GRB::Rule::Chain chain);
		RC_STEP step(Log::LOG log);
		bool start(Log::LOG log);
		bool savediagnosis(RC_STEP pprc_step);
		void printrules(Log::LOG log);

		struct Deducation
		{
			short size;
			short* nrules;
			short* nrulechains;
			Deducation() { size = 0; nrules = 0; nrulechains = 0; }
		} deducation;
		bool savededucation();
	};
}