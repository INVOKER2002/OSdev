#include <stdint.h>
#include "stdio.h"
#include "memory.h"
#include <hal/hal.h>
#include <arch/i686/irq.h>
#include "graphics.h"

extern uint8_t __bss_start;
extern uint8_t __end;

void crash_me();

void timer(Registers* regs)
{
    printf(".");
}

void __attribute__((section(".entry"))) start(uint16_t bootDrive)
{
    memset(&__bss_start, 0, (&__end) - (&__bss_start));

    HAL_Initialize();

    clrscr();
    
    // Initialize graphics first
    printf("Initializing graphics...\n");
    init_graphics();
    
    // Test GUI drawing
    printf("Drawing GUI elements...\n");
    test_gui();

    printf("Hello from kernel!\n");

    //i686_IRQ_RegisterHandler(0, timer);
    //crash_me();

end:
    for (;;);
}

// Initialize graphics
void init_graphics() {
    // Set up graphics mode
    if(!set_graphics_mode(320, 200, 256)) {
        printf("Failed to set graphics mode!\n");
        return;
    }
    
    // Initialize color palette with vibrant colors
    init_palette();
    
    // Initialize framebuffer
    init_framebuffer();
}

// Draw an animated background pattern
void draw_animated_background() {
    for(int y = 0; y < 200; y++) {
        for(int x = 0; x < 320; x++) {
            uint8_t color = (x/4 + y/4) % 64 + 16;
            put_pixel(x, y, color);
        }
    }
}

// Test GUI by drawing various elements
void test_gui() {
    // Draw animated background
    draw_animated_background();
    
    // Create a window for our "OS"
    draw_window(20, 20, 280, 160, "My Simple OS", COLOR_VIBRANT_BLUE, COLOR_WHITE, 7);
    
    // Draw a welcome message
    draw_text(60, 40, "Welcome to My Simple OS!", COLOR_WHITE);
    
    // Draw some decorative elements
    draw_circle(50, 80, 15, 4);  // Red circle
    draw_filled_circle(270, 80, 15, 2);  // Green circle
    
    // Draw buttons
    draw_button(70, 100, 80, 20, "Button 1", 9, COLOR_WHITE);
    draw_button(170, 100, 80, 20, "Button 2", 2, COLOR_WHITE);
    
    // Draw a progress bar
    draw_progress_bar(70, 130, 180, 10, 75, COLOR_WHITE, 8, 10);
    draw_text(70, 145, "System Status: 75%", COLOR_WHITE);
    
    // Draw decorative lines
    for(int i = 0; i < 10; i++) {
        draw_line(310, 20 + i*5, 320, 20 + i*10, i+5);
    }
    
    // Draw "Hello World!" in large letters across the bottom
    for(int i = 0; i < 12; i++) {
        char c = "Hello World!"[i];
        // Draw each character with a shadow effect
        draw_char(30 + i*20, 180, c, 8);  // Shadow
        draw_char(29 + i*20, 179, c, COLOR_WHITE);  // Main text
    }
}