/***********************************************************************
** Author       : zheng yi xiong 
** Date         : 2014-05-11
** Name         : Calendar.h
** Description  :
** Modify Record:
***********************************************************************/

#ifndef __CALENDAR_H__
#define __CALENDAR_H__


const unsigned long HUNDRED_YEAR_DAYS = 36524;
const unsigned long FOUR_YEAR_DAYS   = 1461;
const unsigned long ONE_YEAR_DAYS   = 365;

enum WEEK_DAY
{
SUNDAY      = 0,
MONDAY      = 1,
TUESDAY     = 2,
WEDNESDAY   = 3,
THURSDAY    = 4,
FRIDAY      = 5,
SATURDAY    = 6,
SUM_WK_DAYS = 7
};

class CCalendar
{
public:
	CCalendar();
	virtual ~CCalendar();

	//����ĳ��ĳ���ж����죬�������ʾ��������
	static short GetMonthDays(short year, short month);

	//����ĳ��ĳ��ĳ��Ϊ���ڼ�
	static short GetWeekday(short year, short month, short mday);

    //�ж��Ƿ�Ϊ����
	static bool IsLeapYear(short year);

	//����ĳ��ĳ��ĳ����һ����ĵڼ���
	static short GetYearDays(short year, short month, short mday);

};

#endif //__CALENDAR_H__

