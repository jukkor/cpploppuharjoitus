#pragma once
#include "RoomType.h"
class HotelRoom
{
private:
	int roomNumber;
	RoomType roomType;
	bool isReserved;
	int stayDuration;
public:
	HotelRoom();
	HotelRoom(int roomNumber);
	HotelRoom(int roomNumber, RoomType roomType);
	int getRoomNumber() const;
	RoomType getRoomType() const;
	bool checkIsReserved() const;
	int getStayDuration() const;
	void reserve(int days);
	void checkout();
	void printRoomInfo() const;
};

