#include"screens.h"
#include"queries.h"
#include"commands.h"

#include<iostream>


void printBanner() {
    std::cout << "=== Hotellihuoneiden varausohjelma ===" << std::endl;
}


void printPrice(std::vector<HotelRoom>& reservedRoomsList) {
    int discountRoll = getRandomNumberBetween(1, 3);
    float discount = 1;

    if (discountRoll == 2) {
        discount = 0.9;
        std::cout << "Sait 10 % alennuksen!" << std::endl;
    }
    else if (discountRoll == 3) {
        discount = 0.8;
        std::cout << "Sait 20 % alennuksen!" << std::endl;
    }

    int singleRoomNights = 0;
    int doubleRoomNights = 0;

    for (HotelRoom r : reservedRoomsList) {
        if (r.getRoomType() == RoomType::Single) {
            singleRoomNights += r.getStayDuration();
        }
        else {
            doubleRoomNights += r.getStayDuration();
        }
    }

    int price = (singleRoomNights * 100) + (doubleRoomNights * 150);
    int discountedPrice = price * discount;

    std::cout << "Huoneiden hinta yhteensä: " << price << " euroa." << std::endl;
    if (discountRoll != 1) {
        std::cout << "Huoneiden hinta alennuksen jälkeen: " << discountedPrice << " euroa." << std::endl;
    }
}



void printReservedRooms(std::vector<HotelRoom>& reservedRoomsList) {
    if (reservedRoomsList.size() != 0) {
        std::vector<HotelRoom> singleRooms;
        std::vector<HotelRoom> doubleRooms;

        for (HotelRoom r : reservedRoomsList) {
            if (r.getRoomType() == RoomType::Single) singleRooms.push_back(r);
            else doubleRooms.push_back(r);
        }
        std::cout << "Varatut huoneet:" << std::endl;
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
    }
}

void removeRoomReservation(std::vector<HotelRoom>& roomList, std::vector<HotelRoom>& reservedRoomsList, RoomType roomType) {
    bool roomTypeFound = false;

    for (int i = 0; i < reservedRoomsList.size(); i++) {
        if (reservedRoomsList.at(i).getRoomType() == roomType) {
            int roomNumber = reservedRoomsList.at(i).getRoomNumber();
            for (int j = 0; j < roomList.size(); j++) {
                if (roomList.at(j).getRoomNumber() == roomNumber) {
                    roomList.at(j).checkout();
                }
            }

            reservedRoomsList.erase(reservedRoomsList.begin() + i);
            roomTypeFound = true;
            break;
        }
    }

    if (!roomTypeFound) {
        std::cout << "Ei " << (roomType == RoomType::Single ? "yhden hengen " : "kahden hengen ") << "huonetta varattuna." << std::endl;
        waitForEnter();
    }
}

void reserveRoom(
    std::vector<HotelRoom>& roomList,
    std::vector<HotelRoom>& reservedRoomsList,
    RoomType roomType
) {
    bool roomTypeAvailable = true;

    if (reservedRoomsList.size() >= (roomList.size() / 2) - 1) {
        roomTypeAvailable = checkIfRoomTypeAvailable(roomList, roomType);
    }
    if (roomTypeAvailable) {
        while (true) {
            int randomNumber = getRandomNumberBetween(0, roomList.size() - 1);
            if (roomList.at(randomNumber).checkIsReserved() == false
                && roomList.at(randomNumber).getRoomType() == roomType) {
                int stayDuration = getStayDurationFromUser();
                roomList.at(randomNumber).reserve(stayDuration);
                reservedRoomsList.push_back(roomList.at(randomNumber));
                break;
            }
        }
    }
    else {
        std::cout << "Kaikki " << (roomType == RoomType::Single ? "yhden hengen" : "kahden hengen")
            << " huoneet on jo varattu." << std::endl;
        waitForEnter();
    }
}

void waitForEnter() {
    std::cout << "Paina Enter jatkaaksesi...";
    std::cin.clear();
    std::cin.ignore();
    std::cin.clear();
    std::cin.ignore();
}


void searchByReservationNumber(std::vector<Reservation>& reservations) {
    clearScreen();
    printBanner();
    std::cout << "===              HAKU              ===" << std::endl;
    std::cout << std::endl;
    std::cout << "-1. Palaa varauksiin" << std::endl;
    std::cout << "Syötä varausnumero:" << std::endl;
    std::cout << std::endl;

    for (int i = 0; i < reservations.size(); i++) {
        std::cout << i + 1 << ". Varausnro: " << reservations.at(i).getNumber() << ", " << reservations.at(i).getName() << std::endl;
    }


    int choice = getIntInRangeFromUserWithEscape(10000, 99999);
    bool reservationFound = false;

    switch (choice) {
    case -1:
        break;
    default:
        if (choice != -1) {
            for (Reservation r : reservations) {
                if (r.getNumber() == choice) {
                    r.printReservationInfo();
                    reservationFound = true;
                    waitForEnter();
                    searchByReservationNumber(reservations);
                }
            }
        }
        if (!reservationFound) {
            std::cout << "Varausta ei löytynyt." << std::endl;
            waitForEnter();
            searchByReservationNumber(reservations);
        }
    }
}


void populateRoomList(std::vector<HotelRoom>& roomList, int amountOfRooms) {
    roomList.clear();
    for (int i = 0; i < amountOfRooms; i++) {
        if (i <= (amountOfRooms / 2) - 1) {
            HotelRoom room(i + 1, RoomType::Single);
            roomList.push_back(room);
        }
        else {
            HotelRoom room(i + 1, RoomType::Double);
            roomList.push_back(room);
        }
    }
}
