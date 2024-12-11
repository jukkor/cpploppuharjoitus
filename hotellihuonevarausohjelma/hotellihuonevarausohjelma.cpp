#include <iostream>
#include <random>
#include "HotelRoom.h"
#include "Reservation.h"

#include"screens.h"
#include"queries.h"
#include"commands.h"


int main()
{
    std::setlocale(LC_ALL, "fi_FI");
    const int amountOfRooms = getRandomEvenNumberBetween(40, 300);
    std::vector<HotelRoom> roomList;
    populateRoomList(roomList, amountOfRooms);
    std::vector<HotelRoom> reservedRoomsList;
    std::vector<Reservation> reservations;

    mainMenu(roomList, reservedRoomsList, reservations);
    return 0;
}


