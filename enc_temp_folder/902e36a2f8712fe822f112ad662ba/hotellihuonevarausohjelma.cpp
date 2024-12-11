#include <iostream>
#include <random>
#include "HotelRoom.h"
#include "Reservation.h"

// Screens
void clearScreen();
void mainMenu(std::vector<HotelRoom>& roomList, std::vector<HotelRoom>& reservedRoomsList, std::vector<Reservation>& reservations);
void reserveRoomsScreen(std::vector<HotelRoom>& roomList, std::vector<HotelRoom>& reservedRoomsList, std::vector<Reservation>& reservations);
void finalizeOrderScreen(std::vector<HotelRoom>& roomList,
    std::vector<HotelRoom>& reservedRoomsList,
    std::vector<Reservation>& reservations);
void browseReservationsScreen(std::vector<HotelRoom>& roomList, std::vector<HotelRoom>& reservedRoomsList, std::vector<Reservation>& reservations);

// Commands
void printBanner();
void populateRoomList(std::vector<HotelRoom>& roomList, int amountOfRooms);
void removeRoomReservation(std::vector<HotelRoom>& roomList, std::vector<HotelRoom>& reservedRoomsList, RoomType roomType);
void reserveRoom(std::vector<HotelRoom>& roomList, std::vector<HotelRoom>& reservedRoomsList, RoomType roomType);
void searchByReservationNumber(std::vector<Reservation>& reservations);
void printPrice(std::vector<HotelRoom>& reservedRoomsList);
void printReservedRooms(std::vector<HotelRoom>& reservedRoomsList);
void waitForEnter();

// Queries
bool checkIfRoomTypeAvailable(std::vector<HotelRoom>& roomList, RoomType roomType);
int getRandomEvenNumberBetween(int low, int high);
int getRandomNumberBetween(int low, int high);
int getRoomSizeFromUser();
int getStayDurationFromUser();
int getIntInRangeFromUserWithEscape(int min, int max);
int getIntInRangeFromUser(int min, int max);


int main()
{
    std::setlocale(LC_ALL, "fi_FI");
    const int amountOfRooms = getRandomEvenNumberBetween(10, 20);
    std::vector<HotelRoom> roomList;
    populateRoomList(roomList, amountOfRooms);
    std::vector<HotelRoom> reservedRoomsList;
    std::vector<Reservation> reservations;

    mainMenu(roomList, reservedRoomsList, reservations);
    return 0;
}

void waitForEnter() {
        std::cout << "Paina Enter jatkaaksesi...";
        std::cin.clear();
        std::cin.ignore();
        std::cin.clear();
        std::cin.ignore();
}

void printBanner() {
    std::cout << "=== Hotellihuoneiden varausohjelma ===" << std::endl;
}

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
        while (reservedRoomsList.size() > 0) {
            removeRoomReservation(roomList, reservedRoomsList, RoomType::Single);
            removeRoomReservation(roomList, reservedRoomsList, RoomType::Double);
        }
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
        break;
    }
}

void printPrice(std::vector<HotelRoom>& reservedRoomsList) {
    int discountRoll = getRandomNumberBetween(1, 3);
    float discount = 1;
    
    if (discountRoll == 2) {
        discount = 0.9;
        std::cout << "Sait 10 % alennuksen!" << std::endl;
    } else if (discountRoll == 3) {
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

    std::cout << "Remove, Reserved Room List" << std::endl;
    for (HotelRoom r : reservedRoomsList) {
        r.printRoomInfo();
    }

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

    std::cout << "Add, Room List" << std::endl;
    for (HotelRoom r : roomList) {
        r.printRoomInfo();
    }

    std::cout << "Add, reserved Room List" << std::endl;
    for (HotelRoom r : reservedRoomsList) {
        r.printRoomInfo();
    }

    if (reservedRoomsList.size() >= (roomList.size() / 2)-1) {
        roomTypeAvailable = checkIfRoomTypeAvailable(roomList, roomType);
    }
    if (roomTypeAvailable) {
        while (true) {
            int randomNumber = getRandomNumberBetween(0, roomList.size()-1);
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

bool checkIfRoomTypeAvailable(std::vector<HotelRoom>& roomList, RoomType roomType) {
    for (HotelRoom r : roomList) {
        if (r.getRoomType() == roomType
            && r.checkIsReserved() == false) return true;
    }
    return false;
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
        std::cout << i+1 << ". Varausnumero: " << reservations.at(i).getNumber() << ", " << reservations.at(i).getName() << std::endl;
    }


    int reservationsCount = reservations.size();
    int choice = getIntInRangeFromUserWithEscape(0, 99);

    switch (choice) {
        case -1:
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


    // kierrä varattujen huoneiden läpi ja printtaa ne. userInput - 1 on indeksi
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
            HotelRoom room(i+1, RoomType::Single);
            roomList.push_back(room);
        }
        else {
            HotelRoom room(i+1, RoomType::Double);
            roomList.push_back(room);
        }
    }
}


int getRandomEvenNumberBetween(int low, int high) {
    int randomNumber = getRandomNumberBetween(low, high);

    if (randomNumber % 2 != 0) {
        randomNumber += 1;
    }

    return randomNumber;
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