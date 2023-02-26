#include "raylib.h"

//----------------------------------------------------------------------------------
// Some Defines
//----------------------------------------------------------------------------------
#define MEGAMAN_SPRITE_WALKING_RIGHT 0
#define MEGAMAN_SPRITE_WALKING_LEFT 1
#define MEGAMAN_SPRITE_JUMPING_RIGHT 2
#define MEGAMAN_SPRITE_JUMPING_LEFT 3
#define MEGAMAN_SPRITE_WAITING_RIGHT 4
#define MEGAMAN_SPRITE_WAITING_LEFT 5

typedef struct Sprite {
    Texture2D tex;
    Rectangle srect[11];

    int frames;
    int currentFrame;
    int actualWidth;
    int actualHeight;
    
    long double time;
    float animationTime;
} Sprite;

typedef struct Map {
    Texture2D background;
    
    Rectangle base_floor;
    Rectangle barriers[10];
    int num_barriers;
    
    Rectangle special_item;
    int draw_special_item;
    
    int next_map;
    int prev_map;
} Map;

typedef struct Megaman {
    Vector2 pos;

    Sprite sprites[6];
    int curr_sprite;
    int jumping;
    float jump_speed;
    float jump_acceleration;
    float jump_actual;

    int last_key;

    int speed;
} Megaman;

typedef struct Game { 
    Map maps[10];
    int num_maps;
    int curr_map;
    
    Megaman megaman;


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
void megaman_setup(Game *g);
void draw_map(Game *g);
void update_megaman_pos(Game *g);
void sprite_animate(Sprite* s);
void map0_setup(Game *g);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    Game game;
    game.screenWidth = 620;
    game.screenHeight = 540;

    InitWindow(game.screenWidth, game.screenHeight, "AEDS I's platform");
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

void InitGame(Game *g){

    g->curr_map = 0;
    g->num_maps = 10;

    map0_setup(g);
    megaman_setup(g);

    g->gameover = 0;

}

void UpdateGame(Game *g)
{
    update_megaman_pos(g);
    sprite_animate(&g->megaman.sprites[g->megaman.curr_sprite]);
}

// Draw game (one frame)
void DrawGame(Game *g)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);
    draw_map(g);
    Sprite *s = &(g->megaman.sprites[g->megaman.curr_sprite]);
    DrawTextureRec(s->tex, s->srect[s->currentFrame], 
        g->megaman.pos, (Color) {255, 255, 255, 255});

    EndDrawing();
}

// Update and Draw (one frame)
void UpdateDrawFrame(Game *g)
{
    UpdateGame(g);
    DrawGame(g);
}

void draw_map(Game *g){

    Map *map = &g->maps[g->curr_map];
    DrawTexture(map->background, 0, 0, (Color) {255, 255, 255, 255});
    DrawRectangleRec(map->base_floor, BLACK);
}

void update_megaman_pos(Game *g){

    Megaman *megaman = &g->megaman;
    Map *m = &g->maps[g->curr_map];

    if(megaman->jumping){
        megaman->pos.y -= megaman->jump_actual;
        if((megaman->pos.y + megaman->sprites[megaman->curr_sprite].actualHeight) > m->base_floor.y) {
            if(megaman->last_key == KEY_D) megaman->pos.y = m->base_floor.y - megaman->sprites[MEGAMAN_SPRITE_WAITING_RIGHT].actualHeight;
            else megaman->pos.y = m->base_floor.y - megaman->sprites[MEGAMAN_SPRITE_WAITING_LEFT].actualHeight;
            megaman->jumping = 0;
            return;
        }
        megaman->jump_actual += megaman->jump_acceleration;
    }

    //     if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
    //         megaman->pos.x -= megaman->speed;
    //     } else if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
    //         megaman->pos.x += megaman->speed;
    //     }        
    //     return;
    // }

    if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        megaman->pos.x -= megaman->speed;
        megaman->curr_sprite = MEGAMAN_SPRITE_WALKING_LEFT;
        if(megaman->jumping) megaman->curr_sprite = MEGAMAN_SPRITE_JUMPING_LEFT;
        megaman->last_key = KEY_A;
    }


    if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        megaman->pos.x += megaman->speed;
        megaman->curr_sprite = MEGAMAN_SPRITE_WALKING_RIGHT;
        if(megaman->jumping) megaman->curr_sprite = MEGAMAN_SPRITE_JUMPING_RIGHT;
        megaman->last_key = KEY_D;
    }

    if(IsKeyDown(KEY_SPACE) && !megaman->jumping) {
        megaman->jump_actual = megaman->jump_speed;
        megaman->pos.y -= megaman->speed;
        megaman->jumping = 1;
        if(megaman->last_key == KEY_D) megaman->curr_sprite = MEGAMAN_SPRITE_JUMPING_RIGHT;
        else megaman->curr_sprite = MEGAMAN_SPRITE_JUMPING_LEFT;
    }
    
    if(!(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) &&
        !(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) &&
        !IsKeyDown(KEY_SPACE) && !megaman->jumping) {
            if(megaman->last_key == KEY_D) megaman->curr_sprite = MEGAMAN_SPRITE_WAITING_RIGHT;
            else megaman->curr_sprite = MEGAMAN_SPRITE_WAITING_LEFT;
    }

    if(megaman->pos.x < 0) 
        megaman->pos.x += megaman->speed;

    if(megaman->pos.x + megaman->sprites[megaman->curr_sprite].actualWidth > g->maps[g->curr_map].background.width) 
        megaman->pos.x -= megaman->speed;
}

void megaman_setup(Game *g){
    g->megaman.pos = (Vector2) { 250, g->maps[g->curr_map].base_floor.y - 39};
    g->megaman.speed = 2;
    g->megaman.curr_sprite = MEGAMAN_SPRITE_WAITING_RIGHT;
    g->megaman.jumping = 0; 
    g->megaman.jump_speed = 15;
    g->megaman.jump_acceleration = -1;
    g->megaman.jump_actual = 0;
    g->megaman.last_key = KEY_D;

    g->megaman.sprites[MEGAMAN_SPRITE_WALKING_RIGHT].tex = LoadTexture("sprites/megaman_walking_right.png");
    g->megaman.sprites[MEGAMAN_SPRITE_WALKING_RIGHT].frames = 11;
    g->megaman.sprites[MEGAMAN_SPRITE_WALKING_RIGHT].currentFrame = 0;
    g->megaman.sprites[MEGAMAN_SPRITE_WALKING_RIGHT].actualWidth = 39;
    g->megaman.sprites[MEGAMAN_SPRITE_WALKING_RIGHT].actualHeight = 39;
    for(int i = 0; i < g->megaman.sprites[MEGAMAN_SPRITE_WALKING_RIGHT].frames; i++) {
        g->megaman.sprites[MEGAMAN_SPRITE_WALKING_RIGHT].srect[i] = (Rectangle) { g->megaman.sprites[MEGAMAN_SPRITE_WALKING_RIGHT].actualWidth*i, 0, 
            g->megaman.sprites[MEGAMAN_SPRITE_WALKING_RIGHT].actualWidth, g->megaman.sprites[MEGAMAN_SPRITE_WALKING_RIGHT].actualHeight };
    }
    g->megaman.sprites[MEGAMAN_SPRITE_WALKING_RIGHT].time = 0;
    g->megaman.sprites[MEGAMAN_SPRITE_WALKING_RIGHT].animationTime = 0.06;

    g->megaman.sprites[MEGAMAN_SPRITE_WALKING_LEFT].tex = LoadTexture("sprites/megaman_walking_left.png");
    g->megaman.sprites[MEGAMAN_SPRITE_WALKING_LEFT].frames = 11;
    g->megaman.sprites[MEGAMAN_SPRITE_WALKING_LEFT].currentFrame = 0;
    g->megaman.sprites[MEGAMAN_SPRITE_WALKING_LEFT].actualWidth = 39;
    g->megaman.sprites[MEGAMAN_SPRITE_WALKING_LEFT].actualHeight = 39;
    for(int i = 0; i < g->megaman.sprites[MEGAMAN_SPRITE_WALKING_LEFT].frames; i++) {
        g->megaman.sprites[MEGAMAN_SPRITE_WALKING_LEFT].srect[i] = (Rectangle) { g->megaman.sprites[MEGAMAN_SPRITE_WALKING_LEFT].actualWidth*i, 0, 
            g->megaman.sprites[MEGAMAN_SPRITE_WALKING_LEFT].actualWidth, g->megaman.sprites[MEGAMAN_SPRITE_WALKING_LEFT].actualHeight };
    }
    g->megaman.sprites[MEGAMAN_SPRITE_WALKING_LEFT].time = 0;
    g->megaman.sprites[MEGAMAN_SPRITE_WALKING_LEFT].animationTime = 0.06;


    g->megaman.sprites[MEGAMAN_SPRITE_JUMPING_RIGHT].tex = LoadTexture("sprites/megaman_jumping_single_right.png");
    g->megaman.sprites[MEGAMAN_SPRITE_JUMPING_RIGHT].frames = 1;
    g->megaman.sprites[MEGAMAN_SPRITE_JUMPING_RIGHT].currentFrame = 0;
    g->megaman.sprites[MEGAMAN_SPRITE_JUMPING_RIGHT].actualWidth = 39;
    g->megaman.sprites[MEGAMAN_SPRITE_JUMPING_RIGHT].actualHeight = 51;
    for(int i = 0; i < g->megaman.sprites[MEGAMAN_SPRITE_JUMPING_RIGHT].frames; i++) {
        g->megaman.sprites[MEGAMAN_SPRITE_JUMPING_RIGHT].srect[i] = (Rectangle) { g->megaman.sprites[MEGAMAN_SPRITE_JUMPING_RIGHT].actualWidth*i, 0, 
            g->megaman.sprites[MEGAMAN_SPRITE_JUMPING_RIGHT].actualWidth, g->megaman.sprites[MEGAMAN_SPRITE_JUMPING_RIGHT].actualHeight };
    }
    g->megaman.sprites[MEGAMAN_SPRITE_JUMPING_RIGHT].time = 0;
    g->megaman.sprites[MEGAMAN_SPRITE_JUMPING_RIGHT].animationTime = 0.06;

    g->megaman.sprites[MEGAMAN_SPRITE_JUMPING_LEFT].tex = LoadTexture("sprites/megaman_jumping_single_left.png");
    g->megaman.sprites[MEGAMAN_SPRITE_JUMPING_LEFT].frames = 1;
    g->megaman.sprites[MEGAMAN_SPRITE_JUMPING_LEFT].currentFrame = 0;
    g->megaman.sprites[MEGAMAN_SPRITE_JUMPING_LEFT].actualWidth = 39;
    g->megaman.sprites[MEGAMAN_SPRITE_JUMPING_LEFT].actualHeight = 51;
    for(int i = 0; i < g->megaman.sprites[MEGAMAN_SPRITE_JUMPING_LEFT].frames; i++) {
        g->megaman.sprites[MEGAMAN_SPRITE_JUMPING_LEFT].srect[i] = (Rectangle) { g->megaman.sprites[MEGAMAN_SPRITE_JUMPING_LEFT].actualWidth*i, 0, 
            g->megaman.sprites[MEGAMAN_SPRITE_JUMPING_LEFT].actualWidth, g->megaman.sprites[MEGAMAN_SPRITE_JUMPING_LEFT].actualHeight };
    }
    g->megaman.sprites[MEGAMAN_SPRITE_JUMPING_LEFT].time = 0;
    g->megaman.sprites[MEGAMAN_SPRITE_JUMPING_LEFT].animationTime = 0.06;

    g->megaman.sprites[MEGAMAN_SPRITE_WAITING_RIGHT].tex = LoadTexture("sprites/megaman_waiting_right.png");
    g->megaman.sprites[MEGAMAN_SPRITE_WAITING_RIGHT].frames = 3;
    g->megaman.sprites[MEGAMAN_SPRITE_WAITING_RIGHT].currentFrame = 0;
    g->megaman.sprites[MEGAMAN_SPRITE_WAITING_RIGHT].actualWidth = 39;
    g->megaman.sprites[MEGAMAN_SPRITE_WAITING_RIGHT].actualHeight = 39;
    for(int i = 0; i < g->megaman.sprites[MEGAMAN_SPRITE_WAITING_RIGHT].frames; i++) {
        g->megaman.sprites[MEGAMAN_SPRITE_WAITING_RIGHT].srect[i] = (Rectangle) { g->megaman.sprites[MEGAMAN_SPRITE_WAITING_RIGHT].actualWidth*i, 0, 
            g->megaman.sprites[MEGAMAN_SPRITE_WAITING_RIGHT].actualWidth, g->megaman.sprites[MEGAMAN_SPRITE_WAITING_RIGHT].actualHeight };
    }
    g->megaman.sprites[MEGAMAN_SPRITE_WAITING_RIGHT].time = 0;
    g->megaman.sprites[MEGAMAN_SPRITE_WAITING_RIGHT].animationTime = 0.06;

    g->megaman.sprites[MEGAMAN_SPRITE_WAITING_LEFT].tex = LoadTexture("sprites/megaman_waiting_left.png");
    g->megaman.sprites[MEGAMAN_SPRITE_WAITING_LEFT].frames = 3;
    g->megaman.sprites[MEGAMAN_SPRITE_WAITING_LEFT].currentFrame = 0;
    g->megaman.sprites[MEGAMAN_SPRITE_WAITING_LEFT].actualWidth = 39;
    g->megaman.sprites[MEGAMAN_SPRITE_WAITING_LEFT].actualHeight = 39;
    for(int i = 0; i < g->megaman.sprites[MEGAMAN_SPRITE_WAITING_LEFT].frames; i++) {
        g->megaman.sprites[MEGAMAN_SPRITE_WAITING_LEFT].srect[i] = (Rectangle) { g->megaman.sprites[MEGAMAN_SPRITE_WAITING_LEFT].actualWidth*i, 0, 
            g->megaman.sprites[MEGAMAN_SPRITE_WAITING_LEFT].actualWidth, g->megaman.sprites[MEGAMAN_SPRITE_WAITING_LEFT].actualHeight };
    }
    g->megaman.sprites[MEGAMAN_SPRITE_WAITING_LEFT].time = 0;
    g->megaman.sprites[MEGAMAN_SPRITE_WAITING_LEFT].animationTime = 0.06;
}

void sprite_animate(Sprite* s) {
    s->time += GetFrameTime();
    if(s->time > s->animationTime) {
        s->currentFrame++;
        s->time = 0;
    }

    if(s->currentFrame >= s->frames) {
        s->currentFrame = 0;
    }
}

void map0_setup(Game *g){
    g->maps[0].background = LoadTexture("backgrounds/background_0.png");
    g->maps[0].num_barriers = 1;
    g->maps[0].base_floor = (Rectangle) {0, 415, g->screenWidth, 2};
}
