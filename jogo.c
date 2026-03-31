#include "raylib.h"
#include <stdio.h>

#define MAX_BODY 200

int main(void)
{
    int bodyX[MAX_BODY] = {20};
    int bodyY[MAX_BODY] = {20};
    int quantidade = 0;
    int direcao = 0;
    int X = 0, Y = 0;
    int macaX = 0, macaY = 0;
    int V = 1;
    bool gameOver = false;

    Rectangle quadrado = {20, 20, 48, 48};

    InitWindow(800, 450, "Snake Game");
    SetTargetFPS(8);

    macaX = GetRandomValue(0, 15);
    macaY = GetRandomValue(0, 8);

    while (!WindowShouldClose())
    {
        if (!gameOver)
        {
            if (IsKeyDown(KEY_RIGHT) && direcao != 1) direcao = 0;
            if (IsKeyDown(KEY_LEFT) && direcao != 0)  direcao = 1;
            if (IsKeyDown(KEY_UP) && direcao != 3)    direcao = 2;
            if (IsKeyDown(KEY_DOWN) && direcao != 2)  direcao = 3;

            switch (direcao)
            {
                case 0: X += V; break;
                case 1: X -= V; break;
                case 2: Y -= V; break;
                case 3: Y += V; break;
            }

            if (Y > 8)  Y = 0;
            if (X > 15) X = 0;
            if (Y < 0)  Y = 8;
            if (X < 0)  X = 15;

            for (int i = quantidade; i > 0; i--)
            {
                bodyX[i] = bodyX[i - 1];
                bodyY[i] = bodyY[i - 1];
            }
            bodyX[0] = X;
            bodyY[0] = Y;

            for (int i = 1; i <= quantidade; i++) 
            {
                if (X == bodyX[i] && Y == bodyY[i]) 
                {
                    gameOver = true;
                }
            }

            if (X == macaX && Y == macaY)
            {
                quantidade++;

                bodyX[quantidade] = bodyX[quantidade - 1];
                bodyY[quantidade] = bodyY[quantidade - 1];

                bool valido = false;
                while (!valido)
                {
                    macaX = GetRandomValue(0, 15);
                    macaY = GetRandomValue(0, 8);
                    valido = true;
                    for (int i = 0; i <= quantidade; i++)
                    {
                        if (macaX == bodyX[i] && macaY == bodyY[i]) valido = false;
                    }
                }
            }
        } 
        else 
        {
            if (IsKeyPressed(KEY_R)) 
            {
                X = 0; Y = 0;
                quantidade = 0;
                direcao = 0;
                gameOver = false;
                macaX = GetRandomValue(0, 15);
                macaY = GetRandomValue(0, 8);
                for(int i=0; i<MAX_BODY; i++) { bodyX[i] = 0; bodyY[i] = 0; }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                quadrado.x = j * 50;
                quadrado.y = i * 50;
                DrawRectangleRec(quadrado, (Color){34, 40, 34, 255});
                DrawRectangleLines(quadrado.x, quadrado.y, 50, 50, (Color){40, 50, 40, 255});
            }
        }

        DrawRectangle(macaX * 50, macaY * 50, 48, 48, RED);

        for (int i = 1; i <= quantidade; i++)
        {
            DrawRectangle(bodyX[i] * 50, bodyY[i] * 50, 48, 48, (Color){0, 200, 60, 255});
        }

        DrawRectangle(X * 50, Y * 50, 48, 48, (Color){0, 255, 80, 255});

        if (gameOver) 
        {
            DrawRectangle(0, 0, 800, 450, (Color){0, 0, 0, 150});
            DrawText("GAME OVER", 250, 150, 50, RED);
            DrawText("Pressione 'R' para Recomençar", 200, 220, 25, RAYWHITE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}