#define QUERIES_H
#pragma once

bool checkIfRoomTypeAvailable(std::vector<HotelRoom>& roomList, RoomType roomType);
int getRandomEvenNumberBetween(int low, int high);
int getRandomNumberBetween(int low, int high);
int getRoomSizeFromUser();
int getStayDurationFromUser();
int getIntInRangeFromUserWithEscape(int min, int max);
int getIntInRangeFromUser(int min, int max);