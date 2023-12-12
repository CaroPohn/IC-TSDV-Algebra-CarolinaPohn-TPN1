#include <raylib.h>
#include <vector>

using namespace std;


bool PointInPolygon(Vector2 ballPosition, Vector2 vertices[], int totalVertices);

void main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Dibujar Polígonos y Mover Pelota");

    Vector2 ballPosition = { static_cast<float>(screenWidth) / 2, static_cast<float>(screenHeight) / 2 };
    Vector2 vertices[50];
    int totalVertices = 0;
    Vector2 ballSpeed = { 5.0f, 5.0f };
    float ballRadius = 20.0f;
    Color ballColor = RED;


    bool isDrawingPolygon = false;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update
        if (IsKeyDown(KEY_RIGHT)) ballPosition.x += ballSpeed.x;
        if (IsKeyDown(KEY_LEFT)) ballPosition.x -= ballSpeed.x;
        if (IsKeyDown(KEY_DOWN)) ballPosition.y += ballSpeed.y;
        if (IsKeyDown(KEY_UP)) ballPosition.y -= ballSpeed.y;

        // Check if ball is inside any polygon
        bool insidePolygon = false;

        if (totalVertices >= 3)  // Check if there are enough vertices to form a polygon
        {
            insidePolygon = PointInPolygon(ballPosition, vertices, totalVertices);
        }

        if (insidePolygon)
            ballColor = GREEN;
        else
            ballColor = RED;

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            isDrawingPolygon = true;
            vertices[totalVertices].y = GetMousePosition().y;
            vertices[totalVertices].x = GetMousePosition().x;
            totalVertices++;
        }
        else if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        {
            isDrawingPolygon = false;
        }

        if (totalVertices > 1)
        {
            for (int i = 0; i < totalVertices - 1; i++)
            {
                DrawLineV(vertices[i], vertices[i + 1], RED);
            }

            if (isDrawingPolygon)
            {
                DrawLineEx(vertices[totalVertices - 1], GetMousePosition(), 2, BLACK);
            }
        }

        DrawCircleV(ballPosition, ballRadius, ballColor);

        EndDrawing();
    }

    CloseWindow();
}


bool PointInPolygon(Vector2 ballPosition, Vector2 vertices[], int totalVertices)
{
    int crossings = 0;

    for (int i = 0, j = totalVertices - 1; i < totalVertices; j = i++)
    {
        if (((vertices[i].y > ballPosition.y) != (vertices[j].y > ballPosition.y)) && //ball.y tiene que estar entre y1 e y2 primero
            (ballPosition.x < vertices[j].x + ((ballPosition.y - vertices[j].y) / (vertices[i].y - vertices[j].y)) * (vertices[i].x - vertices[j].x)))
        {
            crossings++;
        }
    }

    return (crossings % 2 == 1);
}