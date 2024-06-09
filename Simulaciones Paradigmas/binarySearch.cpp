#include "raylib.h"
#include <cmath>

#define MAX_ARRAY_SIZE 100
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define BAR_WIDTH 6
#define BAR_SPACING 2

int binarySearch(int arr[], int left, int right, int key);

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Binary Search");

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
            index = binarySearch(array, 0, MAX_ARRAY_SIZE - 1, searchKey);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < MAX_ARRAY_SIZE; i++) {
            int barHeight = array[i] * (SCREEN_HEIGHT - 100) / (MAX_ARRAY_SIZE * 2);
            Rectangle bar = {i * (BAR_WIDTH + BAR_SPACING), SCREEN_HEIGHT - barHeight - 50, BAR_WIDTH, barHeight};
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

int binarySearch(int arr[], int left, int right, int key) {
    while (left <= right) {
        int middle = left + (right - left) / 2;
        
        if (arr[middle] == key) {
            return middle;
        }
        if (arr[middle] < key) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    return -1;
}