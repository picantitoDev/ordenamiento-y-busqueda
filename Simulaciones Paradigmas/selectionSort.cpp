#include "raylib.h"

#define ScreenWidth 1200
#define ScreenHeight 800

#define minScreenWidth 500
#define minScreenHeight 800

#define FPS 60

#define NUM_BARS 100
#define SORT_STEPS_PER_FRAME 3  // Número de pasos de ordenamiento por fotograma

// Variables globales para Selection Sort
int selI = 0, selJ = 0, minIndex;

void SelectionSortStep(int array[], int size);

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

    bool sorting = true;

    while (!WindowShouldClose()) {
        // Lógica de ordenamiento
        if (sorting) {
            for (int step = 0; step < SORT_STEPS_PER_FRAME; step++) {
                SelectionSortStep(array, NUM_BARS);
                if (selI >= NUM_BARS - 1) {
                    sorting = false; // Finaliza el ordenamiento cuando termina la pasada completa
                    break;
                }
            }
        }

        // Dibujado
        BeginDrawing();
        ClearBackground(BLACK);
        // Dibujar título
        DrawText("SelectionSort", 30, 40, 50, WHITE);
        // Dibujar barras
        for (int k = 0; k < NUM_BARS; k++) {
            if (sorting && (k == selI || k == minIndex)) { // Las dos barras involucradas en el paso de Selection Sort
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

void SelectionSortStep(int array[], int size) {
    if (selI < size - 1) {
        if (selJ == 0) {
            minIndex = selI;
            selJ = selI + 1;
        }

        if (selJ < size) {
            if (array[selJ] < array[minIndex]) {
                minIndex = selJ;
            }
            selJ++;
        } else {
            if (minIndex != selI) {
                int temp = array[minIndex];
                array[minIndex] = array[selI];
                array[selI] = temp;
            }
            selI++;
            selJ = 0;
        }
    }
}