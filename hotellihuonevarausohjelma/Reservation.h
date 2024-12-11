#pragma once
#include <string>
#include "HotelRoom.h"
#include <vector>
class Reservation
{
private:
	std::string reserverName;
	int reservationNumber;
	std::vector<HotelRoom> reservedRooms;
public:
	Reservation();
	Reservation(std::string reserverName, int reservationNumber, std::vector<HotelRoom> reservedRooms);
	std::string getName();
	int getNumber();
	std::vector<HotelRoom> getRooms();
	void printReservationInfo();
};

