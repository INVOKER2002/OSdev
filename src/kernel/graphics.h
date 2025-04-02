#include <stdint.h>
#ifndef GRAPHICS_H
#define GRAPHICS_H

#define COLOR_VIBRANT_BLUE  0x01
#define COLOR_WHITE         0x0F

// Function prototypes
int set_graphics_mode(uint16_t width, uint16_t height, uint8_t depth);
void init_palette();
void init_framebuffer();
void put_pixel(uint16_t x, uint16_t y, uint8_t color);
void draw_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t color);
void draw_text(uint16_t x, uint16_t y, const char* text, uint8_t color);

#endif