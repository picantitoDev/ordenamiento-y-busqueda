#include "raylib.h"

#define MAX 5 // Número de elementos del arreglo

int main(void)
{
    // Inicializamos la ventana
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Ordenamiento");
    
    // Declaramos un arreglo de números y lo llenamos con enteros al azar [0-100]
    int elements[MAX];
    for (int i = 0; i < MAX; i++)
    {
        elements[i] = GetRandomValue(0, 100);
    }
    
    // Variables para el ordenamiento
    bool swapped = false;
    int swapCounter = 0;
    int indexOfLastUnsortedElement = MAX;
    
    SetTargetFPS(60); // Configuramos los FPS
    
    while (!WindowShouldClose()) 
    {
        // Gestionamos el evento para la barra espaciadora
        if (IsKeyPressed(KEY_SPACE))
        {
            // Usamos la misma lógica que en la página de referencia (VisuAlgo.net)
            swapped = false;
            for (int i = 0; i < indexOfLastUnsortedElement - 1; i++)
            {
                int leftElement = elements[i];
                int rightElement = elements[i + 1];
                
                if (leftElement > rightElement)
                {
                    // Intercambio de elementos
                    int temp = elements[i];
                    elements[i] = elements[i + 1];
                    elements[i + 1] = temp;
                    
                    swapped = true;
                    swapCounter++;
                }
            }
            if (!swapped)
                indexOfLastUnsortedElement--;
        }
        
        // Comenzamos el dibujado del canvas
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Calculamos la posición inicial de las barras
        int barWidth = 30; 
        int gap = 10;      // Espacio entre las barras
        int startX = (screenWidth - (MAX * barWidth + (MAX - 1) * gap)) / 2;
        int startY = (screenHeight - 200) / 2 + 20;

        // Dibujamos los elementos como barras con números
        for (int i = 0; i < MAX; i++)
        {
            int barHeight = (elements[i] * (screenHeight - 200)) / 100; // Cálculo ajustado de la altura

            // Coordenadas para dibujar
            int barX = startX + i * (barWidth + gap);
            int barY = startY + 200 - barHeight;

            // Dibujar las barras
            DrawRectangle(barX, barY, barWidth, barHeight, SKYBLUE);

            // Dibujar el valor del elemento encima de las barras
            DrawText(TextFormat("%d", elements[i]), barX + (barWidth / 4), barY - 25, 20, BLACK);

            // Dibujar la posición del arreglo debajo de las barras
            DrawText(TextFormat("%d", i), barX + (barWidth / 4), startY + 210, 20, BLACK);
        }
        
        DrawText(TextFormat("Swaps: %d", swapCounter), 10, 10, 20, BLACK);
        DrawText("VisuAlgo", screenWidth/2 - 47, 25, 30, BLACK);
        
        EndDrawing();
    }
    
    CloseWindow(); 
    return 0;
}
