#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Some Defines
//----------------------------------------------------------------------------------
#define STD_SIZE_X 30
#define STD_SIZE_Y 30
#define SCREEN_BORDER 4

typedef struct Hero {
    Rectangle pos;
    Color color;
    int speed;
} Hero;

typedef struct Enemy {
    Rectangle pos;
    Color color;
    int speed;
    int direction;
} Enemy;

typedef struct Map {
    Rectangle barries[10];
    int num_barriers;
    Rectangle door;
    Color color;
    Enemy enemy;
} Map;



//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------
static const int screenWidth = 800;
static const int screenHeight = 450;

Hero barbarian;
Map map;

//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
void InitGame(void);         // Initialize game
void UpdateGame(void);       // Update game (one frame)
void DrawGame(void);         // Draw game (one frame)
void UnloadGame(void);       // Unload game
void UpdateDrawFrame(void);  // Update and Draw (one frame)

//------------------------------------------------------------------------------------
// Auxiliar Functions Declaration
//------------------------------------------------------------------------------------
void draw_borders();
void draw_map();
void map1_setup();
int barrier_collision(Rectangle *t);
void update_enemy_pos(Enemy *e);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //---------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "Aedsinho's quest");
    SetTargetFPS(120);
    
    InitGame();
    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        // Update and Draw
        //----------------------------------------------------------------------------------
        UpdateDrawFrame();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    // UnloadGame();         // Unload loaded data (textures, sounds, models...)

    // CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
//------------------------------------------------------------------------------------
// Module Functions Definitions (local)
//------------------------------------------------------------------------------------

// Initialize game variables
void InitGame(void){
    barbarian.pos = (Rectangle) { 150, 300, STD_SIZE_X, STD_SIZE_Y};
    barbarian.color = BLACK;
    barbarian.speed = 6;

    map1_setup();
}

// Update game (one frame)
void UpdateGame(void)
{
    // process events
    if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        if(barbarian.pos.x > SCREEN_BORDER)
            barbarian.pos.x -= barbarian.speed;
        if(barrier_collision(&barbarian.pos)) barbarian.pos.x += barbarian.speed;

    } else if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        if(barbarian.pos.x + barbarian.pos.width < screenWidth - SCREEN_BORDER)
            barbarian.pos.x += barbarian.speed;
        if(barrier_collision(&barbarian.pos)) barbarian.pos.x -= barbarian.speed;

    } else if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        if(barbarian.pos.y > SCREEN_BORDER)
            barbarian.pos.y -= barbarian.speed;
        if(barrier_collision(&barbarian.pos)) barbarian.pos.y += barbarian.speed;

    } else if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        if(barbarian.pos.y + barbarian.pos.height < screenHeight - SCREEN_BORDER)
            barbarian.pos.y += barbarian.speed;
        if(barrier_collision(&barbarian.pos)) barbarian.pos.y -= barbarian.speed;
    }
}

// Draw game (one frame)
void DrawGame(void)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawRectangle(0, 0, screenWidth, screenHeight, GRAY);
    draw_borders();
    draw_map();
    DrawRectangleRec(barbarian.pos, barbarian.color);
    
    EndDrawing();
}

// Unload game variables
void UnloadGame(void)
{
    return;
    // TODO: Unload all dynamic loaded data (textures, sounds, models...)
}

// Update and Draw (one frame)
void UpdateDrawFrame(void)
{
    UpdateGame();
    DrawGame();
}

void draw_borders()
{
    DrawRectangle(0, 0, SCREEN_BORDER, screenHeight, BLACK);
    DrawRectangle(0, 0, screenWidth, SCREEN_BORDER, BLACK);
    DrawRectangle(screenWidth-SCREEN_BORDER, 0, screenWidth, screenHeight, BLACK);
    DrawRectangle(0, screenHeight-SCREEN_BORDER, screenWidth, screenHeight, BLACK);
}

void map1_setup(){
    map.num_barriers = 1;
    map.barries[0] = (Rectangle) {screenWidth/2, 0, 2, 0.8 * screenHeight};
    map.color = GRAY;
    map.door = (Rectangle) {screenWidth-SCREEN_BORDER, screenHeight/3, SCREEN_BORDER, 50};
    map.enemy.pos = (Rectangle) { 2*screenWidth/3, 2*screenHeight/3, STD_SIZE_X, STD_SIZE_Y};
    map.enemy.color = BLACK;
    map.enemy.speed = 6;
    map.enemy.direction = KEY_DOWN;
}

void draw_map(){
    for(int i = 0; i < map.num_barriers; i++){
        DrawRectangleRec(map.barries[i], BLACK);
    }
    DrawRectangleRec(map.door, RED);
    update_enemy_pos(&map.enemy);
    DrawRectangleRec(map.enemy.pos, PINK);
}

void update_enemy_pos(Enemy *e){
    
    if(e->direction == KEY_LEFT) {
        if(e->pos.x > SCREEN_BORDER)
            e->pos.x -= e->speed;
        else{
            printf("ENTREI\n");
            e->direction = KEY_RIGHT + (rand() % 4);
        }
        if(barrier_collision(&e->pos)){
            e->pos.x += e->speed;
            e->direction = KEY_RIGHT + (rand() % 4);
        }

    } else if(e->direction == KEY_RIGHT) {
        if(e->pos.x + e->pos.width < screenWidth - SCREEN_BORDER)
            e->pos.x += e->speed;
        else
            e->direction = KEY_RIGHT + (rand() % 4);
        
        if(barrier_collision(&e->pos)){
            e->pos.x -= e->speed;
            e->direction = KEY_RIGHT + (rand() % 4);
        }
        
    } else if(e->direction == KEY_UP) {
        if(e->pos.y > SCREEN_BORDER)
            e->pos.y -= e->speed;
        else
            e->direction = KEY_RIGHT + (rand() % 4);
        
        if(barrier_collision(&e->pos)){
            e->pos.y += e->speed;
            e->direction = KEY_RIGHT + (rand() % 4);
        }
    } else if(e->direction == KEY_DOWN) {
        if(e->pos.y + e->pos.height < screenHeight - SCREEN_BORDER)
            e->pos.y += e->speed;
        else
            e->direction = KEY_RIGHT + (rand() % 4);
        
        if(barrier_collision(&e->pos)){
            e->pos.y -= e->speed;
            e->direction = KEY_RIGHT + (rand() % 4);
        }
    }
    if(rand() % 20 == 1)
        e->direction = KEY_RIGHT + (rand() % 4);
}

int barrier_collision(Rectangle *t){
    for(int i = 0; i < map.num_barriers; i++){
        if(CheckCollisionRecs(*t, map.barries[i])){
            return 1;
        }
    }
    return 0;
}
