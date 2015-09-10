/***********************************************************************
** Author       : zheng yi xiong 
** Date         : 2014-05-11
** Name         : Calendar.cpp
** Description  :
** Modify Record:
***********************************************************************/

#include "Calendar.h"

CCalendar::CCalendar( )
{

}

CCalendar::~CCalendar( )
{

}

bool CCalendar::IsLeapYear(short year)
{
	if (0 != (year % 4))
	{
		return false;
	}
	else if ((0 == (year % 100)) && (0 != (year % 400)))
	{
		return false;
	}
	else
	{
		return true;
	}
}

short CCalendar::GetYearDays(short year, short month, short mday)
{
	short days = 0;

	for(short m=1; m<month; ++m)
	{
		days += GetMonthDays(year, m);
	}

	days += mday;
	return days;
}

short CCalendar::GetMonthDays(short year, short month)
{
	short leapyear = IsLeapYear(year) ? 1 : 0;
	switch(month)
	{
	case 1:
		return 31;
	case 2:
		return 28 + leapyear;
	case 3:
		return 31;
	case 4:
		return 30;
	case 5:
		return 31;
	case 6:
		return 30;
	case 7:
		return 31;
	case 8:
		return 31;
	case 9:
		return 30;
	case 10:
		return 31;
	case 11:
		return 30;
	case 12:
		return 31;
	default:
		return 0;
	}
}

short CCalendar::GetWeekday(short year, short month, short mday)
{
	//应该把某一年做成0-399轮回中的一个，所以应该先减一
	short short_year = (year - 1) % 400;

	long day_sum     = (short_year / 100) * HUNDRED_YEAR_DAYS;

	short_year = short_year % 100;

	day_sum += (short_year / 4) * FOUR_YEAR_DAYS;

	day_sum += (short_year % 4) * ONE_YEAR_DAYS;

	day_sum += GetYearDays(year, month, mday);

	return static_cast<short>(day_sum % SUM_WK_DAYS);
}

