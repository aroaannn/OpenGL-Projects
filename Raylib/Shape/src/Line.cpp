#include <iostream>
#include <raylib.h>

int WIDTH = 800;
int HEIGHT = 450;

int main() {
  InitWindow(WIDTH, HEIGHT, "Hello raylib!");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {

    BeginDrawing();

    ClearBackground(WHITE);

    DrawText("Hello World!", 400, HEIGHT / 2 - 30, 24, GRAY);
    DrawLine(0, HEIGHT / 2 , WIDTH, HEIGHT / 2, BLACK);

    EndDrawing();
  }
  CloseWindow();
  return 0;
};