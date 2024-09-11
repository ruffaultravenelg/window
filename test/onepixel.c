#include "../window.h"

int main() {

    // Création de la fenêtre
    window* win = create_window();
    setWindowTitle(win, "Ma fenetre");
    setWindowWidth(win, 500);
    setWindowHeight(win, 500);

    // Affiche la fenêtre
    showWindow(win);

    // Dessine un pixel rouge
    Color red = {255, 0, 0, 255};
    drawPixel(win, 250, 250, red);

    while (1) {

        // Récupère un évènement
        windowEvent ev = pullEvent(win);

        // Fermeture de l'application
        if (ev.type == EVENT_QUIT)
            break;

    }

    // Ferme la fenêtre et libère la mémoire
    destroy_window(win);
    return 0;

}