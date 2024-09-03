#include "window.h"
#include <windows.h>

// Vérifiez que ces macros sont bien définies
#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#endif

#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))
#endif

struct window {
    HWND hwnd;
    HDC hdc;
    int width;
    int height;
};

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_MOUSEMOVE:
            // Nous pourrions gérer d'autres messages ici.
            break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

window* create_window() {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "ExampleWindowClass";

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        wc.lpszClassName,
        "Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        wc.hInstance,
        NULL
    );

    window* win = (window*)malloc(sizeof(window));
    win->hwnd = hwnd;
    win->hdc = GetDC(hwnd);
    win->width = 800;
    win->height = 600;

    return win;
}

void setWindowTitle(window* win, const char* title) {
    SetWindowText(win->hwnd, title);
}

void setWindowWidth(window* win, int width) {
    win->width = width;
    SetWindowPos(win->hwnd, NULL, 0, 0, width, win->height, SWP_NOMOVE | SWP_NOZORDER);
}

void setWindowHeight(window* win, int height) {
    win->height = height;
    SetWindowPos(win->hwnd, NULL, 0, 0, win->width, height, SWP_NOMOVE | SWP_NOZORDER);
}

int getWindowWidth(window* win){
    return win->width;
}

int getWindowHeight(window* win){
    return win->height;
}

void drawPixel(window* win, int x, int y, Color c) {
    HDC hdc = GetDC(win->hwnd);
    SetPixel(hdc, x, y, RGB(c.r, c.g, c.b));
    ReleaseDC(win->hwnd, hdc);
}

void showWindow(window* win) {
    ShowWindow(win->hwnd, SW_SHOW);
    UpdateWindow(win->hwnd);
}

windowEvent pullEvent(window* win) {
    windowEvent event = {0};
    MSG msg = {0};
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        if (msg.message == WM_QUIT) {
            event.type = EVENT_QUIT;
        } else if (msg.message == WM_MOUSEMOVE) {
            event.type = EVENT_MOUSE_MOVE;
            event.mouse_move.x = GET_X_LPARAM(msg.lParam);
            event.mouse_move.y = GET_Y_LPARAM(msg.lParam);
        }
    }
    return event;
}

void destroy_window(window* win) {
    ReleaseDC(win->hwnd, win->hdc);
    DestroyWindow(win->hwnd);
    free(win);
}

void fillRect(window* win, int x, int y, int w, int h, Color c) {
    HDC hdc = GetDC(win->hwnd);
    
    // Créer une brosse (brush) avec la couleur spécifiée
    HBRUSH brush = CreateSolidBrush(RGB(c.r, c.g, c.b));
    
    // Définir le rectangle à remplir
    RECT rect;
    rect.left = x;
    rect.top = y;
    rect.right = x + w;
    rect.bottom = y + h;
    
    // Remplir le rectangle avec la brosse
    FillRect(hdc, &rect, brush);
    
    // Libérer les ressources
    DeleteObject(brush);
    ReleaseDC(win->hwnd, hdc);
}
