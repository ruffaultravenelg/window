#include "../window.h"
#include <stdio.h>
#include <math.h>
#include <windows.h>

void drawRainbowGradient(window* win) {
    int width = getWindowWidth(win);
    int height = getWindowHeight(win);

    // Définir les couleurs de l'arc-en-ciel
    Color colors[] = {
        {255, 0, 0, 255},   // Rouge
        {255, 165, 0, 255}, // Orange
        {255, 255, 0, 255}, // Jaune
        {0, 255, 0, 255},   // Vert
        {0, 0, 255, 255},   // Bleu
        {75, 0, 130, 255},  // Indigo
        {238, 130, 238, 255} // Violet
    };
    int numColors = sizeof(colors) / sizeof(Color);

    // Hauteur de chaque bande de couleur
    int bandHeight = height / (numColors - 1);

    for (int y = 0; y < height; ++y) {
        // Calculer dans quelle bande se trouve la ligne actuelle
        int band = y / bandHeight;
        if (band >= numColors - 1) band = numColors - 2;

        // Interpolation entre les deux couleurs de la bande actuelle
        float ratio = (float)(y % bandHeight) / (float)bandHeight;
        Color startColor = colors[band];
        Color endColor = colors[band + 1];

        Color c;
        c.r = (int)(startColor.r * (1 - ratio) + endColor.r * ratio);
        c.g = (int)(startColor.g * (1 - ratio) + endColor.g * ratio);
        c.b = (int)(startColor.b * (1 - ratio) + endColor.b * ratio);
        c.a = 255;

        // Dessiner une ligne horizontale avec la couleur interpolée
        fillRect(win, 0, y, width, 1, c);
    }
}

int main() {
    window* win = create_window();
    setWindowTitle(win, "Gradient Window");
    setWindowWidth(win, 800);
    setWindowHeight(win, 600);
    showWindow(win);

    // Couleurs de départ et de fin pour le dégradé
    Color startColor = {255, 255, 255, 255}; // Blanc
    Color endColor = {0, 0, 0, 255};         // Noir

    // Dessiner le dégradé
    drawRainbowGradient(win);

    // Attendre avant de fermer pour voir le résultat
    Sleep(5000);

    destroy_window(win);
    return 0;
}
