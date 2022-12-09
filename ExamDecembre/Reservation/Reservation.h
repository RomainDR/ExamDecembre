#pragma once
#include "../Object/Object.h"

class DateTime;

class Reservation : public Object
{
#pragma region f/p
private:
	std::string firstName = "";
	std::string lastName = "";
	int peoples = 0;
	DateTime* dateStart = nullptr;
	DateTime* dateEnd = nullptr;
#pragma endregion f/p

#pragma region constructor
public:
	Reservation() = default;
	Reservation(const std::string& _first, const std::string& _last, const int& _peoples, DateTime* _start, DateTime* _end);
	Reservation(const Reservation& _copy);
#pragma endregion constructor

#pragma region methods
public:
	std::string GetFirstName() const;
	std::string GetLastName() const;
	int GetPeoples() const;
	std::string GetDateStart() const;
	std::string GetDateEnd() const;
	std::string ToString() override;
	std::string GetName() const;
#pragma endregion methods

#pragma region operator
public:
	bool operator==(const Reservation* _res) const;
#pragma endregion operator
};

