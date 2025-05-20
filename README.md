# Hotel Reservation System - Admin Module

## Description
This is a simple C-based Hotel Reservation System for administrators. It allows you to manage rooms, make reservations, and generate reports, using plain text files for data storage.

## Features
- Add Room
- List All Rooms
- Reserve Room
- Cancel Reservation
- Generate Report
- Search by Room Number
- Search by Guest Name
- Modify Guest Name
- Show Only Reserved/Available Rooms
- Delete Room
- Show Room Statistics
- Exit System

## Admin Login
Before accessing the system, an admin login is required.

*Username:* welcome  
*Password:* abcde

## File Structure

- main.c - Entry point, handles login and menu access.
- login.c, login.h - Admin login validation.
- room.c, room.h - Core features and menu logic.
- utils.c, utils.h - Helper functions for file operations.
- rooms.txt - Data file storing room information.
- build.bat - Windows batch script to compile the program.

## Compilation Instructions (Windows)
Ensure you have GCC (MinGW) installed. Then run:

```sh
./build.bat
