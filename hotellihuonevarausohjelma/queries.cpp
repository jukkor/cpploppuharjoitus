#include"screens.h"
#include"queries.h"
#include"commands.h"
#include <random>
#include <iostream>


int getRandomEvenNumberBetween(int low, int high) {
    int randomNumber = getRandomNumberBetween(low, high);

    if (randomNumber % 2 != 0) {
        randomNumber += 1;
    }

    return randomNumber;
}

bool checkIfRoomTypeAvailable(std::vector<HotelRoom>& roomList, RoomType roomType) {
    for (HotelRoom r : roomList) {
        if (r.getRoomType() == roomType
            && r.checkIsReserved() == false) return true;
    }
    return false;
}

int getRandomNumberBetween(int low, int high) {
    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(low, high);

    int randomNumber = distribution(generator);

    return randomNumber;
}

int getRoomSizeFromUser() {
    std::cout << "Anna huoneen koko (1 yhden hengen huoneelle, 2 kahden hengen huoneelle): ";
    return getIntInRangeFromUserWithEscape(1, 2);
}

int getStayDurationFromUser() {
    std::cout << "Anna öiden lukumäärä (1-30): ";
    return getIntInRangeFromUser(1, 30);
}

int getIntInRangeFromUserWithEscape(int min, int max) {
    int input;

    while (!(std::cin >> input) || input < min || input > max) {
        if (input == -1) return input;
        std::cout << "Virheellinen syöte. Syötteen tulee olla numero välillä " << min << "-" << max << ": ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return input;
}

int getIntInRangeFromUser(int min, int max) {
    int input;

    while (!(std::cin >> input) || input < min || input > max) {
        std::cout << "Virheellinen syöte. Syötteen tulee olla numero välillä " << min << "-" << max << ": ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return input;
}