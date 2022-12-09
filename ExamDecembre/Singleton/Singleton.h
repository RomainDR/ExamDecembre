#pragma once
#include <vector>

class Reservation;

class Singleton
{
#pragma region f/p
private:
	static inline std::vector<Reservation*> reservations = std::vector<Reservation*>();
	static inline Singleton* instance;
#pragma endregion f/p

public:
	Singleton()
	{
		instance = this;
	}
	~Singleton() {
		reservations.clear();
		delete instance;
		instance = nullptr;
	}

	static Singleton* GetInstance()
	{
		if (instance == nullptr)
			instance = new Singleton();
		return instance;
	}

#pragma region methods
public:
	static void AddReservation(Reservation* _reservation)
	{
		if (IndexOf(_reservation) == -1)
			reservations.push_back(_reservation);
	}

	static void RemoveReservation(Reservation* _reservatation)
	{
		const int _index = IndexOf(_reservatation);
		if (_index != -1)
			reservations.erase(reservations.begin() + _index);
	}

	static int IndexOf(Reservation* _reservation)
	{
		int index = -1;
		const int _size = reservations.size();
		for (int i = 0; i < _size; i++)
		{
			if (reservations.at(i) == _reservation)
				return i;
		}
		return index;
	}
	static std::vector<Reservation*> GetReservation() {
		return reservations;
	}
#pragma endregion methods
};
