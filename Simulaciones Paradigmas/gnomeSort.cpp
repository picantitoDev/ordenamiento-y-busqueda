#include "raylib.h"

#define ScreenWidth 1200
#define ScreenHeight 800

#define minScreenWidth 500
#define minScreenHeight 800

#define FPS 60

#define NUM_BARS 100
#define SORT_STEPS_PER_FRAME 3  // Número de pasos de ordenamiento por fotograma

int GnomeSortStep(int array[], int size, int index);

int main() {
    // Configuración de la ventana
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(ScreenWidth, ScreenHeight, "Gnome Sort");
    SetWindowMinSize(minScreenWidth, minScreenHeight);

    // FPS
    SetTargetFPS(FPS);

    // Inicializar array con valores aleatorios
    int array[NUM_BARS];
    for (int i = 0; i < NUM_BARS; i++) {
        array[i] = GetRandomValue(50, ScreenHeight - 50);
    }

    bool sorting = true;
    int gnomeIndex = 0;

    while (!WindowShouldClose()) {
        if (sorting) {
            for (int step = 0; step < SORT_STEPS_PER_FRAME; step++) {
                gnomeIndex = GnomeSortStep(array, NUM_BARS, gnomeIndex);
                if (gnomeIndex >= NUM_BARS) {
                    sorting = false; 
                    break;
                }
            }
        }

        // Dibujado
        BeginDrawing();
        ClearBackground(BLACK);
        // Dibujar título
        DrawText("GnomeSort", 30, 40, 50, WHITE);
        
        // Dibujar barras
        for (int k = 0; k < NUM_BARS; k++) {
            if ((k == gnomeIndex || k == gnomeIndex - 1) && sorting) {
                DrawRectangle(k * (ScreenWidth / NUM_BARS), ScreenHeight - array[k], ScreenWidth / NUM_BARS - 2, array[k], RED);
            } else {
                DrawRectangle(k * (ScreenWidth / NUM_BARS), ScreenHeight - array[k], ScreenWidth / NUM_BARS - 2, array[k], WHITE);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

int GnomeSortStep(int array[], int size, int index) {
    if (index < size) {
        if (index == 0) {
            return index + 1;
        } else if (array[index] >= array[index - 1]) {
            return index + 1;
        } else {
            int temp = array[index];
            array[index] = array[index - 1];
            array[index - 1] = temp;
            return index - 1;
        }
    }
    return index;
}