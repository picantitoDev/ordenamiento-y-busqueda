#include "raylib.h"

#define ScreenWidth 1200
#define ScreenHeight 800

#define minScreenWidth 500
#define minScreenHeight 800

#define FPS 60

#define NUM_BARS 100
#define SORT_STEPS_PER_FRAME 3  // Número de pasos de ordenamiento por fotograma

// Variables globales para Shell Sort
int shellInterval, shellI, shellJ, shellK;
void ShellSortStep(int array[], int size);

int main() {
    // Configuración de la ventana
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(ScreenWidth, ScreenHeight, "Sorting Test");
    SetWindowMinSize(minScreenWidth, minScreenHeight);

    // FPS
    SetTargetFPS(FPS);

    // Inicializar array con valores aleatorios
    int array[NUM_BARS];
    for (int i = 0; i < NUM_BARS; i++) {
        array[i] = GetRandomValue(50, ScreenHeight - 50);
    }

    // Inicialización de variables para Shell Sort
    shellInterval = NUM_BARS / 2;
    shellI = 0;
    shellJ = -1; // Inicializamos en -1 para evitar resaltar barras al inicio
    shellK = -1;

    bool sorting = true;

    while (!WindowShouldClose()) {
        // Lógica de ordenamiento
        if (sorting) {
            for (int step = 0; step < SORT_STEPS_PER_FRAME; step++) {
                ShellSortStep(array, NUM_BARS);
                if (shellInterval == 0 && shellI >= NUM_BARS - 1) {
                    sorting = false; 
                    shellJ = -1; 
                    shellK = -1;
                    break;
                }
            }
        }

        // Dibujado
        BeginDrawing();
        ClearBackground(BLACK);
        // Dibujar título
        DrawText("ShellSort", 30, 40, 50, WHITE);
        // Dibujar barras
        for (int k = 0; k < NUM_BARS; k++) {
            if (sorting && ((k == shellJ && shellJ >= 0 && k < NUM_BARS - 2) || (k == shellK && shellK >= 0 && k < NUM_BARS - 1))) { 
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

void ShellSortStep(int array[], int size) {
    if (shellInterval > 0) {
        if (shellI < size) {
            shellJ = shellI - shellInterval;
            while (shellJ >= 0) {
                shellK = shellJ + shellInterval;
                if (array[shellJ] <= array[shellK]) {
                    break;
                } else {
                    int temp = array[shellK];
                    array[shellK] = array[shellJ];
                    array[shellJ] = temp;
                    shellJ -= shellInterval;
                }
            }
            shellI++;
        } else {
            shellI = 0;
            shellInterval /= 2;
        }
    }
}