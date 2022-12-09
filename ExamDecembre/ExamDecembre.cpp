#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include "DateTime/DateTime.h"
#include "Window/Reservation/AddReservation/AddReservation.h"
#include "Singleton/Singleton.h"
#include "Reservation/Reservation.h"
#include <string>
#include <math.h>
#include <commctrl.h>


int main()
{
    Singleton::GetInstance()->AddReservation(new Reservation("Jean", "Paul", 10, new DateTime(10, 12, 2022), new DateTime(11, 12, 2022)));
    Singleton::GetInstance()->AddReservation(new Reservation("Jean", "Marie", 10, new DateTime(10, 12, 2022), new DateTime(11, 12, 2022)));
     AddReservation res = AddReservation();
  
   
}
