#ifndef WINDOW_H
#define WINDOW_H

#include <stdint.h>

// Définition de la structure Color
typedef struct {
    uint8_t r, g, b, a;
} Color;

// Définition de la structure window (opaque)
typedef struct window window;

// Définition des types d'événements
typedef enum {
    EVENT_NONE,
    EVENT_QUIT,
    EVENT_MOUSE_MOVE,
} EventType;

typedef struct {
    int x, y;
} MouseMoveEvent;

typedef struct {
    EventType type;
    union {
        MouseMoveEvent mouse_move;
        // Ajouter d'autres types d'événements si nécessaire
    };
} windowEvent;

// Fonctions de gestion des fenêtres
window* create_window();
int getWindowWidth(window* win);
int getWindowHeight(window* win);
void setWindowTitle(window* win, const char* title);
void setWindowWidth(window* win, int width);
void setWindowHeight(window* win, int height);
void drawPixel(window* win, int x, int y, Color color);
void fillRect(window* win, int x, int y, int w, int h, Color c);
void showWindow(window* win);
windowEvent pullEvent(window* win);
void destroy_window(window* win);

#endif // WINDOW_H
