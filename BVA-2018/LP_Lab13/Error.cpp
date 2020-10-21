#include "stdafx.h"
#include "Error.h"
namespace Error
{
	
	ERROR errors[ERROR_MAX_ENTRY] = // ������� ������
	{
		ERROR_ENTRY(0, "������������ ��� ������"), // ��� ������ ��� �������� 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(1, "��������� ����"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "�������� -in ������ ���� �����"),
		ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "��������� ����� �������� ���������"),
		ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107), ERROR_ENTRY_NODEF(108),
		ERROR_ENTRY(109, "������ ��� �������� ����� � ��������� �����(-out)"),
		ERROR_ENTRY(110, "������ ��� �������� ����� � �������� ����� (-in)"),
		ERROR_ENTRY(111, "������������ ������ � �������� ����� (-in)"),
		ERROR_ENTRY(112, "������ ��� �������� ����� ��������� (-log)"),


		ERROR_ENTRY(113, "����������� ������� �� ������� �����"), 
		ERROR_ENTRY(114, "����������� �������������"), 


		ERROR_ENTRY(115, "������������ ����� ����������� � ���������"),
		ERROR_ENTRY(116, "����� ��������������� �� ������ ��������� 10 ��������"),
		ERROR_ENTRY(117, "���/���������� ���������� ���������� ������� ������ ��������� � �����/�����������\n����������� ����������, ���������� � �������."),
		ERROR_ENTRY(118, "���������� ����������� ����������, ���������� � ������� ������ ��������������� ���������� ���������� ���������� ���������� �������."), 
		ERROR_ENTRY(119, "����������� �������� ��� ������� ����"),
		
		ERROR_ENTRY(120, "����������� ����������� � ����������� �����"),
		ERROR_ENTRY(121, "����������� ����������� � ����� �������"),
		ERROR_ENTRY(122, "����������� ����������� � ���������"),
		ERROR_ENTRY(123, "����������� ����������� � ������ ���������� ������� ��� �����������"),
		ERROR_ENTRY(124, "����������� ����������� � ������ ���������� ������� ��� ������"),
		ERROR_ENTRY(125, "����������� �������� � ���������"),
		ERROR_ENTRY(126, "����������� �������� ���������"),

		ERROR_ENTRY(127, "������� �� ����"),
		ERROR_ENTRY(128, "������� ������ ������������� �����"),
		ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY_NODEF100(600),
		ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
	};
	ERROR geterror(int id)
	{
		ERROR e;
		if (id > 0 && id < ERROR_MAX_ENTRY)
		{
			e = errors[id];
		}
		else
		{
			e = errors[0];
		}
		return e;
	}

	ERROR geterrorin(int id, int line = -1, int col = -1)
	{
		ERROR e;
		if (id > 0 && id < ERROR_MAX_ENTRY)
		{
			e = errors[id];
			e.inext.line = line;
			e.inext.col = col;
		}
		else
		{
			e = errors[0];
			e.inext.line = line;
			e.inext.col = col;
		}
		return e;
	}
}