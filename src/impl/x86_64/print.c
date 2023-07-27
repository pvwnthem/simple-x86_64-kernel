#include "print.h"

const size_t VGA_WIDTH = 80;
const size_t VGA_HEIGHT = 25;

struct Char {
    uint8_t character;
    uint8_t color;
};

struct Char* buffer = (struct Char*) 0xB8000;
size_t col = 0;
size_t row = 0;
uint8_t color = PRINT_COLOR_WHITE | PRINT_COLOR_BLACK << 4;

void clear_row(size_t row) {
    struct Char empty = (struct Char) {
        character: ' ',
        color: color,
    };

    for (size_t col = 0; col < VGA_WIDTH; col++) {
        buffer[col + row * VGA_WIDTH] = empty;
    }
}

void print_clear() {
    for (size_t i = 0; i < VGA_HEIGHT; i++) {
        clear_row(i);
    }
}

void print_newline() {
    col = 0;

    if (row < VGA_HEIGHT - 1) {
        row++;
        return;
    }

    for (size_t row = 1; row < VGA_HEIGHT; row++) {
        for (size_t col = 0; col < VGA_WIDTH; col++) {
            struct Char character = buffer[col + row * VGA_WIDTH];
            buffer[col + (row - 1) * VGA_WIDTH] = character;
        }
    }

    clear_row(VGA_HEIGHT - 1);
}

void print_char(char character) {
    if (character == '\n') {
        print_newline();
        return;
    } else {
        buffer[col + row * VGA_WIDTH] = (struct Char) {
            character: (uint8_t) character,
            color: color,
        };
        col++;
    }

    if (col >= VGA_WIDTH) {
        col = 0;
        row++;
    }

    if (row >= VGA_HEIGHT) {
        for (size_t row = 1; row < VGA_HEIGHT; row++) {
            for (size_t col = 0; col < VGA_WIDTH; col++) {
                struct Char character = buffer[col + row * VGA_WIDTH];
                buffer[col + (row - 1) * VGA_WIDTH] = character;
            }
        }

        clear_row(VGA_HEIGHT - 1);
        row = VGA_HEIGHT - 1;
    }
}

void print_str(char* str) {
    for (size_t i = 0; 1; i++) {
        char character = (uint8_t) str[i];
        if (character == '\0') {
            return;
        }
        print_char(character);
    }
}

void print_set_color(uint8_t foreground, uint8_t background) {
    color = foreground + (background << 4);
}