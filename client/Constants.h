#ifndef BLUESJACKRABBIT_SERVER_CONSTANTS_H
#define BLUESJACKRABBIT_SERVER_CONSTANTS_H


#define MESSAGE_HEADER_LENGTH 0xFFFFFFFF  // 4 bytes

#define OPTION_LENGTH 1
#define OK 0xFF

// GAME PROTOCOL CONSTANTS
#define LEFT 0x1
#define RIGHT 0x2
#define DOWN 0x3
#define UP 0x4

#define CANT_BYTES 1

// MENU PROTOCOL CONSTANTS
#define NEW_GAME 0x20
#define JOIN_GAME 0x21
#define LIST_GAMES 0x22
#define LIST_MAPS 0x23

#define MAP_ID_LENGTH 1


#endif /* BLUESJACKRABBIT_SERVER_CONSTANTS_H */
