#include "DateTime.h"
#include <format>

DateTime::DateTime(const unsigned int& _day, const unsigned int& _month, const unsigned int& _year)
{
	day = _day;
	month = _month;
	year = _year;

	while (day > 30)
	{
		month++;
		day -= 30;
	}

	while (month > 12)
	{
		year++;
		month -= 12;
	}
}

DateTime::DateTime(const DateTime& _copy)
{
	day = _copy.day;
	month = _copy.month;
	year = _copy.year;
}

std::string DateTime::ToString()
{
	return std::format("{:02}/{:02}/{:02}", day, month, year);
}

bool DateTime::operator>(const DateTime* _dt) const
{
	if (year > _dt->year) return true;
	else if (month > _dt->month) return true;
	else if (day > _dt->day) return true;
	return false;
}

bool DateTime::operator==(const DateTime* _dt) const
{
	return year == _dt->year && month == _dt->month && day == _dt->day;
}


