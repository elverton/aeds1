#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

//----------------------------------------------------------------------------------
// Some Defines
//----------------------------------------------------------------------------------
#define STD_SIZE_X 30
#define STD_SIZE_Y 30
#define STD_SIZE_BOMB_X 30
#define STD_SIZE_BOMB_Y 30
#define SCREEN_BORDER 4

typedef struct Bomb{
    Rectangle pos;
    Rectangle explosion_right;
    Rectangle explosion_left;
    Rectangle explosion_up;
    Rectangle explosion_down;
    int isActive;
    int distance;
    int time;
}Bomb;

typedef struct Hero {
    Rectangle pos;
    Color color;
    int speed;
    int special;
    int draw_bomb;
    int put_bomb;
    int num_bombs;
    Bomb bombs[10];
} Hero;

typedef struct Map {
    Rectangle barriers[10];
    int num_barriers;
    Color color;
    int next_map;
    int prev_map;
} Map;

typedef struct Game { 
    Map maps[10];
    int num_maps;
    int curr_map;
    Hero hero;
    int screenWidth;
    int screenHeight;
    int gameover;
} Game;

//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
void InitGame(Game *g);         // Initialize game
void UpdateGame(Game *g);       // Update game (one frame)
void DrawGame(Game *g);         // Draw game (one frame)
void UpdateDrawFrame(Game *g);  // Update and Draw (one frame)

//------------------------------------------------------------------------------------
// Auxiliar Functions Declaration
//------------------------------------------------------------------------------------
void draw_borders(Game *g);
void draw_map(Game *g);
void draw_bomb(Game *g);
void update_hero_pos(Game *g);
void update_bomb(Game *g);

int barrier_collision(Map *m, Rectangle t);
void map0_setup(Game *g);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    Game game;
    game.screenWidth = 800;
    game.screenHeight = 450;

    InitWindow(game.screenWidth, game.screenHeight, "Aedsinho's quest");
    SetTargetFPS(60);
    
    InitGame(&game);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame(&game);
        if(game.gameover) break;
    }
    while(!IsKeyDown(KEY_ENTER)){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("GAME OVER", GetScreenWidth()/2 - MeasureText("GAME OVER", 20)/2, GetScreenHeight()/2 - 50, 20, BLACK);
        EndDrawing();
    }
    return 0;
}
//------------------------------------------------------------------------------------
// Module Functions Definitions (local)
//------------------------------------------------------------------------------------

// Initialize game variables
void InitGame(Game *g){

    g->curr_map = 0;
    g->num_maps = 10;
    g->hero.pos = (Rectangle) { 150, 300, STD_SIZE_X, STD_SIZE_Y};
    g->hero.color = BLACK;
    g->hero.speed = 6;
    g->hero.special = 0;
    g->gameover = 0;
    g->hero.num_bombs = 5;
    g->hero.put_bomb = 0;
    g->hero.draw_bomb = 0;
    map0_setup(g);
}

// Update game (one frame)
void UpdateGame(Game *g)
{
    update_hero_pos(g);
    update_bomb(g);

    Map *map = &g->maps[g->curr_map];
}

// Draw game (one frame)
void DrawGame(Game *g)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawRectangle(0, 0, g->screenWidth, g->screenHeight, GRAY);
    draw_borders(g);
    draw_map(g);
    draw_bomb(g);
    DrawRectangleRec(g->hero.pos, g->hero.color);

    EndDrawing();
}

// Update and Draw (one frame)
void UpdateDrawFrame(Game *g)
{
    UpdateGame(g);
    DrawGame(g);
}

void draw_borders(Game *g)
{
    DrawRectangle(0, 0, SCREEN_BORDER, g->screenHeight, BLACK);
    DrawRectangle(0, 0, g->screenWidth, SCREEN_BORDER, BLACK);
    DrawRectangle(g->screenWidth-SCREEN_BORDER, 0, g->screenWidth, g->screenHeight, BLACK);
    DrawRectangle(0, g->screenHeight-SCREEN_BORDER, g->screenWidth, g->screenHeight, BLACK);
}

void draw_map(Game *g){
    Map *map = &g->maps[g->curr_map];
    for(int i = 0; i < map->num_barriers; i++){
        DrawRectangleRec(map->barriers[i], BLACK);
    }
}

void draw_bomb(Game *g){
    for(int i = 0; i < g->hero.num_bombs; i++){
        if(g->hero.bombs[i].isActive == 1){
            DrawRectangleRec(g->hero.bombs[i].pos, RED);
            DrawRectangleRec(g->hero.bombs[i].explosion_right, RED);
            DrawRectangleRec(g->hero.bombs[i].explosion_left, RED);
            DrawRectangleRec(g->hero.bombs[i].explosion_up, RED);
            DrawRectangleRec(g->hero.bombs[i].explosion_down, RED);
        }
    }
}

void update_hero_pos(Game *g){

    Hero *h = &g->hero;
    Map *m = &g->maps[g->curr_map];

    if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        if(h->pos.x > SCREEN_BORDER)
            h->pos.x -= h->speed;
        if(barrier_collision(m, h->pos)) h->pos.x += h->speed;

    } else if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        if(h->pos.x + h->pos.width < g->screenWidth - SCREEN_BORDER)
            h->pos.x += h->speed;
        if(barrier_collision(m, h->pos)) h->pos.x -= h->speed;

    } else if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        if(h->pos.y > SCREEN_BORDER)
            h->pos.y -= h->speed;
        if(barrier_collision(m, h->pos)) h->pos.y += h->speed;

    } else if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        if(h->pos.y + h->pos.height < g->screenHeight - SCREEN_BORDER)
            h->pos.y += h->speed;
        if(barrier_collision(m, h->pos)) h->pos.y -= h->speed;
    }
}

void update_bomb(Game *g){
    Map *actual_map = &g->maps[g->curr_map];

    if(IsKeyPressed(KEY_SPACE)){
        g->hero.put_bomb = 1;
    }

    if(g->hero.put_bomb == 1){
        for(int i = 0; i < g->hero.num_bombs; i++){
            if(g->hero.bombs[i].isActive == 0){
                g->hero.bombs[i].isActive = 1;
                g->hero.bombs[i].pos = (Rectangle) {g->hero.pos.x, g->hero.pos.y, STD_SIZE_BOMB_X, STD_SIZE_BOMB_Y};
                g->hero.bombs[i].explosion_right = (Rectangle) {g->hero.pos.x, g->hero.pos.y, STD_SIZE_BOMB_X, STD_SIZE_BOMB_Y};
                g->hero.bombs[i].explosion_left = (Rectangle) {g->hero.pos.x, g->hero.pos.y, STD_SIZE_BOMB_X, STD_SIZE_BOMB_Y};
                g->hero.bombs[i].explosion_down = (Rectangle) {g->hero.pos.x, g->hero.pos.y, STD_SIZE_BOMB_X, STD_SIZE_BOMB_Y};
                g->hero.bombs[i].explosion_up = (Rectangle) {g->hero.pos.x, g->hero.pos.y, STD_SIZE_BOMB_X, STD_SIZE_BOMB_Y};

                g->hero.bombs[i].time = GetTime();
                break;
            }
        }
    }
    for(int i = 0; i < g->hero.num_bombs; i++){
        if(g->hero.bombs[i].isActive == 1){
            if(fabs(g->hero.bombs[i].time - GetTime()) > 3 && fabs(g->hero.bombs[i].time - GetTime()) < 5){
                Rectangle verify_bomb;
                Rectangle rectangle_bomb;
                int grow_tax = g->hero.bombs[i].distance;
                if(g->hero.bombs[i].explosion_right.width < g->hero.bombs[i].distance * STD_SIZE_X){
                    rectangle_bomb = g->hero.bombs[i].explosion_right;
                    Rectangle verify_bomb = (Rectangle){ rectangle_bomb.x, rectangle_bomb.y, rectangle_bomb.width + grow_tax,  rectangle_bomb.height};
                    if(!barrier_collision(actual_map, verify_bomb)){
                        g->hero.bombs[i].explosion_right.width += grow_tax;
                    }
                }

                if(g->hero.bombs[i].explosion_left.width < g->hero.bombs[i].distance * STD_SIZE_X){
                    rectangle_bomb = g->hero.bombs[i].explosion_left;
                    Rectangle verify_bomb = (Rectangle){ rectangle_bomb.x - grow_tax, rectangle_bomb.y, rectangle_bomb.width + grow_tax,  rectangle_bomb.height};
                    if(!barrier_collision(actual_map, verify_bomb)){
                        g->hero.bombs[i].explosion_left.width += grow_tax;
                        g->hero.bombs[i].explosion_left.x -= grow_tax;
                    }
                }

                if(g->hero.bombs[i].explosion_up.height < g->hero.bombs[i].distance * STD_SIZE_Y){
                    rectangle_bomb = g->hero.bombs[i].explosion_up;
                    Rectangle verify_bomb = (Rectangle){ rectangle_bomb.x, rectangle_bomb.y, rectangle_bomb.width, rectangle_bomb.height + grow_tax};
                    if(!barrier_collision(actual_map, verify_bomb)){
                        g->hero.bombs[i].explosion_up.height += grow_tax;
                    }
                }

                if(g->hero.bombs[i].explosion_down.height < g->hero.bombs[i].distance * STD_SIZE_Y){
                    rectangle_bomb = g->hero.bombs[i].explosion_down;
                    Rectangle verify_bomb = (Rectangle){ rectangle_bomb.x, rectangle_bomb.y - grow_tax, rectangle_bomb.width, rectangle_bomb.height + grow_tax};
                    if(!barrier_collision(actual_map, verify_bomb)){
                        g->hero.bombs[i].explosion_down.height += grow_tax;
                        g->hero.bombs[i].explosion_down.y -= grow_tax;
                    }
                }
            }else if(fabs(g->hero.bombs[i].time - GetTime()) > 3){
                g->hero.bombs[i].isActive = 0;
            }
        }
    }

    g->hero.put_bomb = 0;
}


int barrier_collision(Map *map, Rectangle target){
    for(int i = 0; i < map->num_barriers; i++){
        if(CheckCollisionRecs(target, map->barriers[i])){
            return 1;
        }
    }
    return 0;
}

// Maps Setup
void map0_setup(Game *g){
    g->maps[0].num_barriers = 1;
    g->maps[0].barriers[0] = (Rectangle) {g->screenWidth/2, 0, 20, 0.8 * g->screenHeight};
    g->maps[0].color = GRAY;
    g->maps[0].prev_map = -1;
    g->maps[0].next_map = 1;
    for(int i = 0; i < g->hero.num_bombs; i++){
        g->hero.bombs[i].isActive = 0;
        g->hero.bombs[i].distance = 3;
    }
}
