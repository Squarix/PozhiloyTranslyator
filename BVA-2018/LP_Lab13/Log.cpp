#include "stdafx.h"
#include "Log.h"
#include "Error.h"
#include <fstream>
#include <stdio.h>  
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <string.h>
#include "Parm.h"

namespace Log
{
	LOG getlog(wchar_t logfile[])// ������� � ��������� ��������� �����
	{
		LOG log;
		wcscpy_s(log.logfile, logfile);
		log.stream = new std::ofstream(logfile, std::ofstream::out);
		if (log.stream->fail()) {
			throw ERROR_THROW(112);
		}
		return log;
	}

	void WriteLine(LOG log, char*c, ...)
	{
		char** pc = &c;            //����� ������� ���������
		int len = 0;
		while (*pc != "") { // ���� ��� ����������� ����� ����� ���������� �����
			len += strlen(*pc);
			pc++;
		}
		char *str = new char[len + 1];       //������ ��� ������
		str[0] = 0;                       // ������� ������
		pc = &c;                       // ��������� �� 1-� ��������
		while (*pc != "") // ���� ��� ��������� �����
		{
			strcat(str, *pc);             // ���������� 
			pc++;                       // ������������ �� ���������
		}
		log.stream->write(str, len);
		delete[] str;
	}

	void WriteLine(LOG log, wchar_t*c, ...)
	{
		wchar_t** pc = &c; //����� ������� ��������� 
		int len = 0;
		while (*pc != L"") { // ���� ��� ����������� ����� ����� ���������� �����
			len += wcslen(*pc);
			pc++;
		}
		wchar_t *str = new wchar_t[len + 1]; //������ ��� ������ 
		char* strl = new char[len + 1];
		str[0] = 0; // ������� ������
		pc = &c; // ��������� �� 1-� �������� 
		while (*pc != L"") // ���� ��� ��������� ����� 
		{
			wcscat(str, *pc); // ���������� 
			pc++; // ������������ �� ��������� 
		}
		wcstombs(strl, str, len + 1);
		log.stream->write(strl, len);
		delete[] str;
	}

	void WriteLog(LOG log)
	{
		time_t curTime;
		tm timeStruct;// ��������� � ����� � ��������
		time(&curTime);

		char strTime[30];
		localtime_s(&timeStruct, &curTime);// ����������� ������� � ������� ����

		strftime(strTime, 1024, "%d.%m.%Y %H:%M:%S", &timeStruct);// ����� � ���� � ������
		*log.stream << "---- �������� ------ " << strTime << " ------------------" << std::endl;
	}

	void WriteParm(LOG log, Parm::PARM parm)
	{
		*log.stream << "---- ��������� ------" << std::endl;

		char temp[PARM_MAX_SIZE + 1];
		wcstombs(temp, PARM_LOG, wcslen(PARM_LOG) + 1);
		*log.stream << temp << " ";
		wcstombs(temp, parm.log, wcslen(parm.log) + 1);
		*log.stream << temp << std::endl;

		wcstombs(temp, PARM_OUT, wcslen(PARM_OUT) + 1);
		*log.stream << temp << " ";
		wcstombs(temp, parm.out, wcslen(parm.out) + 1);
		*log.stream << temp << std::endl;

		wcstombs(temp, PARM_IN, wcslen(PARM_IN) + 1);
		*log.stream << temp << " ";
		wcstombs(temp, parm.in, wcslen(parm.in) + 1);
		*log.stream << temp << std::endl;
	}

	void WriteIn(LOG log, In::IN in)
	{
		*log.stream << "---- �������� ������ ------" << std::endl;
		*log.stream << "���������� ��������: " << in.size << std::endl;
		*log.stream << "���������������    : " << in.ignor << std::endl;
		*log.stream << "���������� �����   : " << in.lines << std::endl;
	}

	void WriteError(LOG log, Error::ERROR error)
	{
		*log.stream << "������ " << error.id << ": " << error.message << ", ������ " << error.inext.line << ",������� " << error.inext.col << std::endl;
	}

	void Close(LOG log)
	{
		log.stream->close();
		delete log.stream;
		log.stream = NULL;
	}

	void WriteLexems(LOG log, const LT::LexTable& lex)
	{
		Log::WriteLine(log, "---- ������� ������ ---- \n", "");
		int j = 0;
		while (j < lex.size) 
		{
			int cur_line = lex.table[j].sn; // ���������� ����� ������ ��� ������� �������
			Log::WriteLine(log, (char *)std::to_string(cur_line).c_str(), " ", ""); // �������� ����� ������
			while (j < lex.size && cur_line == lex.table[j].sn) {
				char lexname[2];
				lexname[0] = lex.table[j].lexema[0];
				lexname[1] = 0;
				std::cout << lexname << "";
				Log::WriteLine(log, (char *)lexname, "");
				j++;
			}
			Log::WriteLine(log, "\n", "");
			std::cout << "\n";
		}
	}

	void WriteItentifiers(LOG log, const IT::IdTable& ids)
	{
		Log::WriteLine(log, "----������� ���������������---- \n", "");
		*log.stream << std::setw(10) << std::right << "��� " << std::setw(10) << std::right << "��� ������ " << std::setw(15) << std::right << "��� �������������� " << std::setw(15) << std::right << "����� ������� ������ " <<
			std::setw(15) << std::right << "������� ��������� " << std::setw(15) << std::right << "����. �� ���������" << std::endl ;
		std::cout << std::setw(10) << std::right << "��� " << std::setw(10) << std::right << "��� ������ " << std::setw(15) << std::right << "��� �������������� " << std::setw(15) << std::right << "����� ������� ������ " <<
			std::setw(15) << std::right << "������� ��������� " << std::setw(15) << std::right << "����. �� ���������" << std::endl;
		for (int i = 0; i < ids.size; i++)
		{
			if (ids.table[i].idtype != IT::IDTYPE::L) {
				*log.stream << std::setw(10) << std::right << ids.table[i].id;
				std::cout << std::setw(10) << std::right << ids.table[i].id;
			} else {
				*log.stream << std::setw(10) << std::right << "Literal";
				std::cout << std::setw(10) << std::right << "Literal";
			}

			if (ids.table[i].iddatatype == IT::IDDATATYPE::INT) {
				*log.stream << std::setw(10) << std::right << "Integer";
				std::cout << std::setw(10) << std::right << "Integer";
			} else if (ids.table[i].iddatatype == IT::IDDATATYPE::STR) {
				*log.stream << std::setw(10) << std::right << "String";
				std::cout << std::setw(10) << std::right << "String";
			} else {
				*log.stream << std::setw(10) << std::right << "Float";
				std::cout << std::setw(10) << std::right << "Float";
			}

			if (ids.table[i].idtype == IT::IDTYPE::V) {
				*log.stream << std::setw(15) << std::right << "Variable";
				std::cout << std::setw(15) << std::right << "Variable";
			} else if (ids.table[i].idtype == IT::IDTYPE::F) {
				*log.stream << std::setw(15) << std::right << "Function";
				std::cout << std::setw(15) << std::right << "Function";
			} else if (ids.table[i].idtype == IT::IDTYPE::P) { 
				*log.stream << std::setw(15) << std::right << "Parameter";
				std::cout << std::setw(15) << std::right << "Parameter";
			} else if (ids.table[i].idtype == IT::IDTYPE::L) {
				*log.stream << std::setw(15) << std::right << "Literal";
				std::cout << std::setw(15) << std::right <<  "Literal";
			}

			*log.stream << std::setw(15) << std::right << ids.table[i].idxfirstLE;
			std::cout << std::setw(15) << std::right << ids.table[i].idxfirstLE;

			*log.stream << std::setw(15) << std::right << ids.table[i].vis;
			std::cout << std::setw(15) << std::right << ids.table[i].vis;

			if (ids.table[i].idtype == IT::IDTYPE::V || ids.table[i].idtype == IT::IDTYPE::L) {
				if (ids.table[i].iddatatype == IT::IDDATATYPE::INT) {
					*log.stream << std::setw(15) << std::right << ids.table[i].value.vint << std::endl;
					std::cout << std::setw(15) << std::right << ids.table[i].value.vint <<std::endl;
				} else {
					*log.stream << std::setw(15) << std::right << "\'" << ids.table[i].value.vstr.str << "\'" << std::endl;
					std::cout << std::setw(15) << std::right << "\'" << ids.table[i].value.vstr.str << "\'" << std::endl;
				}
			} else {
				*log.stream << std::setw(15) << std::right << "none" << std::endl;
				std::cout << std::setw(15) << std::right << "none" << std::endl;
			}
		}
	}
}