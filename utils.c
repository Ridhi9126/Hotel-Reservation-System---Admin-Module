#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define ROOM_FILE "rooms.txt"

void saveRoom(Room room) {
    FILE* file = fopen(ROOM_FILE, "a");
    if (!file) {
        perror("Error opening file");
        return;
    }
    fprintf(file, "%d %d %s\n", room.roomNumber, room.isReserved, room.guestName);
    fclose(file);
}

Room* loadRooms(int* count) {
    FILE* file = fopen(ROOM_FILE, "r");
    if (!file) {
        *count = 0;
        return malloc(0);
    }

    Room* rooms = NULL;
    Room room;
    *count = 0;

    while (fscanf(file, "%d %d %49s", &room.roomNumber, &room.isReserved, room.guestName) == 3) {
        rooms = realloc(rooms, (*count + 1) * sizeof(Room));
        rooms[*count] = room;
        (*count)++;
    }

    fclose(file);
    return rooms;
}

int roomExists(int roomNumber) {
    int count;
    Room* rooms = loadRooms(&count);
    for (int i = 0; i < count; i++) {
        if (rooms[i].roomNumber == roomNumber) {
            free(rooms);
            return 1;
        }
    }
    free(rooms);
    return 0;
}

void saveAllRooms(Room* rooms, int count) {
    FILE* file = fopen(ROOM_FILE, "w");
    if (!file) return;
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %d %s\n", rooms[i].roomNumber, rooms[i].isReserved, rooms[i].guestName);
    }
    fclose(file);
}