#ifndef ROOM_H
#define ROOM_H

typedef struct {
    int roomNumber;
    char guestName[50];
    int isReserved;
} Room;

void menu();
void addRoom();
void listRooms();
void reserveRoom();
void cancelReservation();
void generateReport();
void searchByRoomNumber();
void searchByGuestName();
void modifyGuestName();
void showReservedOrAvailable();
void deleteRoom();
void showRoomStats();

#endif