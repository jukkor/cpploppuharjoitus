#define SCREENS_H
#pragma once

#include<vector>
#include"HotelRoom.h"
#include"Reservation.h"

// Screens
void clearScreen();
void mainMenu(std::vector<HotelRoom>& roomList, std::vector<HotelRoom>& reservedRoomsList, std::vector<Reservation>& reservations);
void reserveRoomsScreen(std::vector<HotelRoom>& roomList, std::vector<HotelRoom>& reservedRoomsList, std::vector<Reservation>& reservations);
void finalizeOrderScreen(std::vector<HotelRoom>& roomList,
    std::vector<HotelRoom>& reservedRoomsList,
    std::vector<Reservation>& reservations);
void browseReservationsScreen(std::vector<HotelRoom>& roomList, std::vector<HotelRoom>& reservedRoomsList, std::vector<Reservation>& reservations);