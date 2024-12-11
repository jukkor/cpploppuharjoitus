#include "HotelRoom.h"
#include <iostream>

HotelRoom::HotelRoom()
	: roomNumber(0), roomType(RoomType::Single), isReserved(false), stayDuration(0)
{
}

HotelRoom::HotelRoom(int roomNumber)
	: roomNumber(roomNumber), roomType(RoomType::Single), isReserved(false), stayDuration(0)
{
}

HotelRoom::HotelRoom(int roomNumber, RoomType roomType)
	: roomNumber(roomNumber), roomType(roomType), isReserved(false), stayDuration(0)
{
}

int HotelRoom::getRoomNumber() const {
	return roomNumber;
}

RoomType HotelRoom::getRoomType() const {
	return roomType;
}

bool HotelRoom::checkIsReserved() const
{
	return isReserved;
}

int HotelRoom::getStayDuration() const {
	return stayDuration;
}

void HotelRoom::reserve(int days)
{
	isReserved = true;
	stayDuration = days;
}

void HotelRoom::checkout()
{
	isReserved = false;
	stayDuration = 0;
}

void HotelRoom::printRoomInfo() const
{
	std::cout
		<< "Room number: " << roomNumber << std::endl
		<< "Room type: " << roomTypeToString(roomType) << std::endl
		<< "Is reserved: " << isReserved << std::endl
		<< std::endl;
}
