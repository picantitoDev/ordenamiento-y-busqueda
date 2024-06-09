#include "raylib.h"
#include <cmath>

#define MAX_ARRAY_SIZE 100
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define BAR_WIDTH 6
#define BAR_SPACING 2

int jumpSearch(int arr[], int size, int key);

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Jump Search");

    int array[MAX_ARRAY_SIZE];
    for (int i = 0; i < MAX_ARRAY_SIZE; i++) {
        array[i] = i * 2; 
    }

    int searchKey = 0;
    int index = -1;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ENTER)) {
            searchKey = GetRandomValue(0, MAX_ARRAY_SIZE * 2);
            index = jumpSearch(array, MAX_ARRAY_SIZE, searchKey);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < MAX_ARRAY_SIZE; i++) {
            int barHeight = array[i] * (SCREEN_HEIGHT - 100) / (MAX_ARRAY_SIZE * 2);

            Rectangle bar = {
                i * (BAR_WIDTH + BAR_SPACING),        // X pos
                SCREEN_HEIGHT - barHeight - 50,       // Y pos
                BAR_WIDTH,                            // Width 
                barHeight                             // Height 
            };

            Color barColor = (i == index) ? GREEN : DARKGRAY;
            DrawRectangleRec(bar, barColor);
        }
 
        DrawText("Presiona Enter para buscar un número aleatorio", 10, 10, 20, BLACK);
        DrawText(TextFormat("Número aleatorio: %d", searchKey), 10, 40, 20, BLACK);

        if (index != -1) {
            DrawText(TextFormat("Elemento encontrado en el índice %d", index), 10, SCREEN_HEIGHT - 30, 20, LIME);
        } else {
            DrawText("Elemento no encontrado", 10, SCREEN_HEIGHT - 30, 20, RED);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

int jumpSearch(int arr[], int size, int key) {
    int start = 0;
    int end = sqrt(size);

    while (end < size && arr[end] < key) {
        start = end;
        end += sqrt(size);
        if (end > size) {
            end = size;
        }
    }

    for (int i = start; i < end; i++) {
        if (arr[i] == key) {
            return i;
        }
    }

    return -1;
}