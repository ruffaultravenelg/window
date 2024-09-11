#include "../window.h"
#include <stdio.h>

/*
    Compile :
    cd ..
    gcc test\draw.c window.c -o prog -lgdi32

*/

#define WIDTH 800
#define HEIGHT 500

int main() {
    // Création de la fenêtre
    window* win = create_window();
    setWindowTitle(win, "Example Window");
    setWindowWidth(win, WIDTH);
    setWindowHeight(win, HEIGHT);

    // Affiche la fenetre
    showWindow(win);

    // Définition des couleurs
    Color red = {255, 0, 0, 255};
    Color white = {255, 255, 255, 255};

    // Boucle principale d'événements
    while (1) {
        
        // Pull event
        windowEvent event = pullEvent(win);

        // Quit
        if (event.type == EVENT_QUIT)
            break;

        // Draw
        if (event.type == EVENT_MOUSE_MOVE)
            drawPixel(win, event.mouse_move.x, event.mouse_move.y, red);

    }

    // Nettoyage
    destroy_window(win);
    return 0;
}