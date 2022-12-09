#include "Reservation.h"
#include "../DateTime/DateTime.h"
#include <format>

Reservation::Reservation(const std::string& _first, const std::string& _last, const int& _peoples, DateTime* _start, DateTime* _end)
{
	firstName = _first;
	lastName = _last;
	peoples = _peoples;
	dateStart = _start;
	dateEnd = _end;
	if (dateStart->operator>(dateEnd))
		throw std::exception("Date end cannot be before dateStart");
}

Reservation::Reservation(const Reservation& _copy)
{
	firstName = _copy.firstName;
	lastName = _copy.lastName;
	peoples = _copy.peoples;
	dateStart = _copy.dateStart;
	dateEnd = _copy.dateEnd;
}

std::string Reservation::GetFirstName() const
{
	return firstName;
}

std::string Reservation::GetLastName() const
{
	return lastName;
}

int Reservation::GetPeoples() const
{
	return peoples;
}

std::string Reservation::GetDateStart() const
{
	return dateStart->ToString();
}

std::string Reservation::GetDateEnd() const
{
	return dateEnd->ToString();
}

std::string Reservation::ToString()
{
	return std::format("FirstName {}, LastName {}, peoples {}, dateStart: {}, dateEnd: {}", firstName, lastName, peoples, dateStart->ToString(), dateEnd->ToString());
}

std::string Reservation::GetName() const
{
	return firstName + " " + lastName;
}

bool Reservation::operator==(const Reservation* _res) const
{
	return firstName == _res->firstName &&
		lastName == _res->lastName &&
		peoples == _res->peoples &&
		dateStart == _res->dateStart &&
		dateEnd == _res->dateEnd;
}
