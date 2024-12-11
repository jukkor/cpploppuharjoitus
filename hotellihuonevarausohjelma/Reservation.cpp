#include "Reservation.h"
#include <iostream>

Reservation::Reservation()
	:reserverName(""), reservationNumber(0), reservedRooms()
{
}

Reservation::Reservation(std::string reserverName, int reservationNumber, std::vector<HotelRoom> reservedRooms)
	:reserverName(reserverName), reservationNumber(reservationNumber), reservedRooms(reservedRooms)
{
}

std::string Reservation::getName()
{
	return reserverName;
}

int Reservation::getNumber()
{
	return reservationNumber;
}

std::vector<HotelRoom> Reservation::getRooms()
{
	return reservedRooms;
}

void Reservation::printReservationInfo() {
	std::cout << "Varausnumero: " << reservationNumber << std::endl;
	std::cout << "Varaaja: " << reserverName << std::endl;

    std::vector<HotelRoom> singleRooms;
    std::vector<HotelRoom> doubleRooms;

    for (HotelRoom r : reservedRooms) {
        if (r.getRoomType() == RoomType::Single) singleRooms.push_back(r);
        else doubleRooms.push_back(r);
    }

    std::cout << "Varatut huoneet:" << std::endl;
    std::cout << std::endl;
    if (singleRooms.size() != 0) {
        std::cout << "Yhden hengen huoneet: " << std::endl;
        for (HotelRoom r : singleRooms) {
            std::cout << "Huone nro: " << r.getRoomNumber() << ", " << r.getStayDuration() << " yötä." << std::endl;
        }
        std::cout << std::endl;
    }
    if (doubleRooms.size() != 0) {
        std::cout << "Kahden hengen huoneet: " << std::endl;
        for (HotelRoom r : doubleRooms) {
            std::cout << "Huone nro: " << r.getRoomNumber() << ", " << r.getStayDuration() << " yötä." << std::endl;
        }
        std::cout << std::endl;
    }

	std::cout << std::endl;
}