
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "room.h"
#include "utils.h"

void menu() {
    int choice;
    do {
        printf("\nHotel Reservation System - Admin Module\n");
        printf("1. Add Room\n");
        printf("2. List All Rooms\n");
        printf("3. Reserve Room\n");
        printf("4. Cancel Reservation\n");
        printf("5. Generate Report\n");
        printf("6. Search by Room Number\n");
        printf("7. Search by Guest Name\n");
        printf("8. Modify Guest Name\n");
        printf("9. Show Only Reserved/Available Rooms\n");
        printf("10. Delete Room\n");
        printf("11. Show Room Statistics\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addRoom(); break;
            case 2: listRooms(); break;
            case 3: reserveRoom(); break;
            case 4: cancelReservation(); break;
            case 5: generateReport(); break;
            case 6: searchByRoomNumber(); break;
            case 7: searchByGuestName(); break;
            case 8: modifyGuestName(); break;
            case 9: showReservedOrAvailable(); break;
            case 10: deleteRoom(); break;
            case 11: showRoomStats(); break;
            case 12: printf("Exiting... Goodbye!\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 12);
}

void addRoom() {
    Room room;
    printf("Enter room number: ");
    scanf("%d", &room.roomNumber);
    if (roomExists(room.roomNumber)) {
        printf("Room already exists.\n");
        return;
    }
    room.isReserved = 0;
    printf("Enter guest name (or '-' if no guest): ");
    scanf("%s", room.guestName);
    saveRoom(room);
    printf("Room added successfully.\n");
}

void listRooms() {
    int count;
    Room* rooms = loadRooms(&count);
    if (count == 0) {
        printf("No rooms found.\n");
        return;
    }
    printf("Room Number\tStatus\t\tGuest Name\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t\t%s\t\t%s\n", rooms[i].roomNumber, 
               rooms[i].isReserved ? "Reserved" : "Available", 
               rooms[i].guestName);
    }
    free(rooms);
}

void reserveRoom() {
    int number;
    printf("Enter room number to reserve: ");
    scanf("%d", &number);
    int count;
    Room* rooms = loadRooms(&count);
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (rooms[i].roomNumber == number && !rooms[i].isReserved) {
            printf("Enter guest name: ");
            scanf("%s", rooms[i].guestName);
            rooms[i].isReserved = 1;
            found = 1;
            break;
        }
    }
    if (found) {
        saveAllRooms(rooms, count);
        printf("Room reserved successfully.\n");
    } else {
        printf("Room not found or already reserved.\n");
    }
    free(rooms);
}

void cancelReservation() {
    int number;
    printf("Enter room number to cancel reservation: ");
    scanf("%d", &number);
    int count;
    Room* rooms = loadRooms(&count);
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (rooms[i].roomNumber == number && rooms[i].isReserved) {
            rooms[i].isReserved = 0;
            strcpy(rooms[i].guestName, "-");
            found = 1;
            break;
        }
    }
    if (found) {
        saveAllRooms(rooms, count);
        printf("Reservation cancelled.\n");
    } else {
        printf("Room not found or not reserved.\n");
    }
    free(rooms);
}

void generateReport() {
    listRooms();
}

void searchByRoomNumber() {
    int number;
    printf("Enter room number: ");
    scanf("%d", &number);
    int count;
    Room* rooms = loadRooms(&count);
    for (int i = 0; i < count; i++) {
        if (rooms[i].roomNumber == number) {
            printf("Room %d is %s. Guest: %s\n", number, 
                   rooms[i].isReserved ? "Reserved" : "Available", 
                   rooms[i].guestName);
            free(rooms);
            return;
        }
    }
    printf("Room not found.\n");
    free(rooms);
}

void searchByGuestName() {
    char name[50];
    printf("Enter guest name: ");
    scanf("%s", name);
    int count;
    Room* rooms = loadRooms(&count);
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(rooms[i].guestName, name) == 0) {
            printf("Room %d is reserved by %s\n", rooms[i].roomNumber, name);
            found = 1;
        }
    }
    if (!found) printf("No reservation found for %s\n", name);
    free(rooms);
}

void modifyGuestName() {
    int number;
    char newName[50];
    printf("Enter room number to modify: ");
    scanf("%d", &number);
    int count;
    Room* rooms = loadRooms(&count);
    for (int i = 0; i < count; i++) {
        if (rooms[i].roomNumber == number && rooms[i].isReserved) {
            printf("Enter new guest name: ");
            scanf("%s", newName);
            strcpy(rooms[i].guestName, newName);
            saveAllRooms(rooms, count);
            printf("Guest name updated.\n");
            free(rooms);
            return;
        }
    }
    printf("Room not found or not reserved.\n");
    free(rooms);
}

void showReservedOrAvailable() {
    int choice;
    printf("1. Show Reserved\n2. Show Available\nChoice: ");
    scanf("%d", &choice);
    int count;
    Room* rooms = loadRooms(&count);
    for (int i = 0; i < count; i++) {
        if ((choice == 1 && rooms[i].isReserved) || (choice == 2 && !rooms[i].isReserved)) {
            printf("Room %d - %s\n", rooms[i].roomNumber, rooms[i].guestName);
        }
    }
    free(rooms);
}

void deleteRoom() {
    int number;
    printf("Enter room number to delete: ");
    scanf("%d", &number);
    int count, newCount = 0;
    Room* rooms = loadRooms(&count);
    Room* newRooms = malloc(count * sizeof(Room));
    for (int i = 0; i < count; i++) {
        if (rooms[i].roomNumber != number) {
            newRooms[newCount++] = rooms[i];
        }
    }
    saveAllRooms(newRooms, newCount);
    free(rooms);
    free(newRooms);
    printf("Room deleted if it existed.\n");
}

void showRoomStats() {
    int count;
    Room* rooms = loadRooms(&count);
    int reserved = 0, available = 0;
    for (int i = 0; i < count; i++) {
        if (rooms[i].isReserved) reserved++;
        else available++;
    }
    printf("Reserved: %d\nAvailable: %d\n", reserved, available);
    free(rooms);
}
