#define COMMANDS_H
#pragma once

#include<vector>
#include"HotelRoom.h"

void printBanner();
void populateRoomList(std::vector<HotelRoom>& roomList, int amountOfRooms);
void removeRoomReservation(std::vector<HotelRoom>& roomList, std::vector<HotelRoom>& reservedRoomsList, RoomType roomType);
void reserveRoom(std::vector<HotelRoom>& roomList, std::vector<HotelRoom>& reservedRoomsList, RoomType roomType);
void searchByReservationNumber(std::vector<Reservation>& reservations);
void printPrice(std::vector<HotelRoom>& reservedRoomsList);
void printReservedRooms(std::vector<HotelRoom>& reservedRoomsList);
void waitForEnter();
