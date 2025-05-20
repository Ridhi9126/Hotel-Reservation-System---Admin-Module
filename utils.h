#ifndef UTILS_H
#define UTILS_H

#include "room.h"

void saveRoom(Room room);
Room* loadRooms(int* count);
int roomExists(int roomNumber);
void saveAllRooms(Room* rooms, int count);

#endif