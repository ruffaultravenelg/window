# Bibliothèque de gestion de fenêtres en C

Cette bibliothèque C fournit une API simple pour créer et gérer des fenêtres, traiter des événements et dessiner des éléments graphiques de base. Elle est conçue pour être minimaliste et facile à intégrer dans des applications nécessitant des interfaces graphiques simples. Celle-ci ne nécessite pas de fichier `.dll` pour fonctionner.

## Fonctionnalités

- Création et gestion de fenêtres.
- Gestion des événements, comme les mouvements de souris et la fermeture de la fenêtre.
- Dessin de pixels et de rectangles dans la fenêtre avec des couleurs RGBA.
- Modifications dynamiques des dimensions et du titre de la fenêtre.

## Contenu

### Structures de données

#### 1. **`Color`**
Représente une couleur en utilisant le modèle RGBA.

```c
typedef struct {
    uint8_t r, g, b, a;
} Color;
```

- `r`, `g`, `b` : Composantes de couleur rouge, verte et bleue.
- `a` : Composante alpha (transparence).

#### 2. **`window`**
Structure opaque représentant une fenêtre. Sa définition est cachée, et elle est manipulée via des pointeurs.

#### 3. **`EventType`**
Enumération représentant les différents types d'événements pouvant être capturés.

```c
typedef enum {
    EVENT_NONE,      // Aucun événement
    EVENT_QUIT,      // L'utilisateur ferme la fenêtre
    EVENT_MOUSE_MOVE // Mouvement de la souris
} EventType;
```

#### 4. **`MouseMoveEvent`**
Structure pour représenter les coordonnées de la souris lorsqu'un mouvement est détecté.

```c
typedef struct {
    int x, y;
} MouseMoveEvent;
```

#### 5. **`windowEvent`**
Structure pour encapsuler un événement dans la fenêtre, avec la possibilité de contenir différents types d'événements.

```c
typedef struct {
    EventType type;   // Type d'événement
    union {
        MouseMoveEvent mouse_move;  // Données de l'événement de mouvement de souris
    };
} windowEvent;
```

### Fonctions

#### Création et destruction de fenêtre

- **`window* create_window()`**  
  Crée une nouvelle fenêtre et renvoie un pointeur vers celle-ci.

- **`void destroy_window(window* win)`**  
  Détruit la fenêtre spécifiée et libère la mémoire associée.

#### Gestion des propriétés de la fenêtre

- **`int getWindowWidth(window* win)`**  
  Renvoie la largeur actuelle de la fenêtre.

- **`int getWindowHeight(window* win)`**  
  Renvoie la hauteur actuelle de la fenêtre.

- **`void setWindowTitle(window* win, const char* title)`**  
  Définit le titre de la fenêtre.

- **`void setWindowWidth(window* win, int width)`**  
  Modifie la largeur de la fenêtre.

- **`void setWindowHeight(window* win, int height)`**  
  Modifie la hauteur de la fenêtre.

#### Affichage et dessin

- **`void drawPixel(window* win, int x, int y, Color color)`**  
  Dessine un pixel à la position `(x, y)` avec la couleur spécifiée.

- **`void fillRect(window* win, int x, int y, int w, int h, Color color)`**  
  Remplit un rectangle de dimensions `(w, h)` à partir de la position `(x, y)` avec la couleur spécifiée.

- **`void showWindow(window* win)`**  
  Affiche la fenêtre à l'écran.

#### Gestion des événements

- **`windowEvent pullEvent(window* win)`**  
  Récupère le prochain événement dans la file d'attente des événements. Si aucun événement n'est disponible, il retourne `EVENT_NONE`.

## Exemples d'utilisation

### 1. Création d'une fenêtre et dessin d'un pixel rouge

```c
#include "window.h"

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
```

## Installation

1. Inclure les fichiers dans votre projet.
2. Compiler en ajoutant lien `window.c` et le drapeau `-lgdi32`

## Licence

Ce projet est sous licence MIT. Vous pouvez l'utiliser et le modifier librement sous condition de me crediter.