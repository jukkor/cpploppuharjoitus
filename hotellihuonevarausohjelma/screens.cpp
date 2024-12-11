#include"screens.h"
#include"queries.h"
#include"commands.h"

#include<iostream>


void clearScreen() {
#ifdef _WIN32
    system("cls"); // Clear screen for Windows
#else
    system("clear"); // Clear screen for Unix/Linux/Mac
#endif
}


void mainMenu(
    std::vector<HotelRoom>& roomList,
    std::vector<HotelRoom>& reservedRoomsList,
    std::vector<Reservation>& reservations
) {
    clearScreen();
    printBanner();
    std::cout << "===           PÄÄVALIKKO           ===" << std::endl;
    std::cout << std::endl;
    std::cout << "-1. Poistu ohjelmasta" << std::endl;
    std::cout << "1. Varaa huoneita" << std::endl;
    std::cout << "2. Katso varauksia" << std::endl;
    std::cout << std::endl;

    int choice = getIntInRangeFromUserWithEscape(1, 2);

    switch (choice) {
    case -1:
        break;
    case 1:
        reserveRoomsScreen(roomList, reservedRoomsList, reservations);
        break;
    case 2:
        browseReservationsScreen(roomList, reservedRoomsList, reservations);
        break;
    default:
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        break;
    }
}

void reserveRoomsScreen(
    std::vector<HotelRoom>& roomList,
    std::vector<HotelRoom>& reservedRoomsList,
    std::vector<Reservation>& reservations
) {
    clearScreen();
    printBanner();
    std::cout << "===           VARAUSSIVU           ===" << std::endl;
    std::cout << std::endl;
    std::cout << "-1. Poistu päävalikkoon" << std::endl;
    std::cout << "1. Varaa yhden hengen huone" << std::endl;
    std::cout << "2. Varaa kahden hengen huone" << std::endl;
    std::cout << "3. Poista yhden hengen huone varauksesta" << std::endl;
    std::cout << "4. Poista kahden hengen huone varauksesta" << std::endl;
    std::cout << "5. Viimeistele tilaus" << std::endl;
    std::cout << std::endl;

    printReservedRooms(reservedRoomsList);

    int choice = getIntInRangeFromUserWithEscape(1, 5);

    switch (choice) {
    case -1:
        mainMenu(roomList, reservedRoomsList, reservations);
        break;
    case 1:
        reserveRoom(roomList, reservedRoomsList, RoomType::Single);
        reserveRoomsScreen(roomList, reservedRoomsList, reservations);
        break;
    case 2:
        reserveRoom(roomList, reservedRoomsList, RoomType::Double);
        reserveRoomsScreen(roomList, reservedRoomsList, reservations);
        break;
    case 3:
        removeRoomReservation(roomList, reservedRoomsList, RoomType::Single);
        reserveRoomsScreen(roomList, reservedRoomsList, reservations);
        break;
    case 4:
        removeRoomReservation(roomList, reservedRoomsList, RoomType::Double);
        reserveRoomsScreen(roomList, reservedRoomsList, reservations);
        break;
    case 5:
        finalizeOrderScreen(roomList, reservedRoomsList, reservations);
        reserveRoomsScreen(roomList, reservedRoomsList, reservations);
        break;
    }
}

void finalizeOrderScreen(
    std::vector<HotelRoom>& roomList,
    std::vector<HotelRoom>& reservedRoomsList,
    std::vector<Reservation>& reservations
) {
    clearScreen();
    printBanner();
    std::cout << "===     VARAUKSEN VIIMEISTELY      ===" << std::endl;
    std::cout << std::endl;
    printReservedRooms(reservedRoomsList);
    printPrice(reservedRoomsList);
    std::cout << std::endl;
    std::cout << "-1. Palaa" << std::endl;
    std::cout << "0. Peru ja poista varaukset" << std::endl;
    std::cout << "1. Viimeistele varaus" << std::endl;
    std::cout << std::endl;

    int choice = getIntInRangeFromUserWithEscape(0, 1);

    switch (choice) {
    case -1:
        break;
    case 0:
        for (int i = 0; i < roomList.size(); i++) {
            roomList.at(i).checkout();
        }
        reservedRoomsList.clear();
        break;
    case 1:
        std::cout << "Anna varaajan nimi: ";
        std::string name;
        std::cin.clear();
        std::cin.ignore();
        std::getline(std::cin, name);
        int reservationNumber = getRandomNumberBetween(10000, 99999);

        Reservation res(name, reservationNumber, reservedRoomsList);
        reservations.push_back(res);
        reservedRoomsList.clear();
        std::cout << "Kiitos varauksestasi!" << std::endl;
        std::cin.clear();
        std::cin.ignore();
        reserveRoomsScreen(roomList, reservedRoomsList, reservations);
        break;
    }
}

void browseReservationsScreen(
    std::vector<HotelRoom>& roomList,
    std::vector<HotelRoom>& reservedRoomsList,
    std::vector<Reservation>& reservations
) {
    clearScreen();
    printBanner();
    std::cout << "===          VARAUKSET             ===" << std::endl;
    std::cout << std::endl;
    std::cout << "-1. Poistu päävalikkoon" << std::endl;
    std::cout << "0. Hae varausnumerolla" << std::endl;
    std::cout << std::endl;

    for (int i = 0; i < reservations.size(); i++) {
        std::cout << i + 1 << ". Varausnumero: " << reservations.at(i).getNumber() << ", " << reservations.at(i).getName() << std::endl;
    }


    int reservationsCount = reservations.size();
    int choice = getIntInRangeFromUserWithEscape(0, 99);

    switch (choice) {
    case -1:
        mainMenu(roomList, reservedRoomsList, reservations);
        break;
    case 0:
        searchByReservationNumber(reservations);
        browseReservationsScreen(roomList, reservedRoomsList, reservations);
        break;
    default:
        if (choice <= reservations.size()) {
            reservations.at(choice - 1).printReservationInfo();
            waitForEnter();
        }
        browseReservationsScreen(roomList, reservedRoomsList, reservations);
        break;
    }
}