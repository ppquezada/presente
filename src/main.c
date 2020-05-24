
#include <raylib.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "level.h"
#include "draw.h"
#include "state.h"
#include "files.h"



int main(int argc, char const *argv[]){

    // Initialization
    const int screen_width = 800;
    const int screen_height = 600;
    
    InitWindow(screen_width,screen_height,"Presente - the game");
    SetTargetFPS(60);

    // Intializaction player score
    int score = 0;
    // Loading high score from hiscore.txt
    int hiscore = show_hiscore();
    
    // Initialization soundtrack and games sounds
    InitAudioDevice();
    Music soundtrack = LoadMusicStream("resources/audio/soundtrack.ogg");
    Music death = LoadMusicStream("resources/audio/death.ogg");
    Music win = LoadMusicStream("resources/audio/win.ogg");
    PlayMusicStream(soundtrack);

    // Initialize level and fill randomly
    level *lvl = level_new(50,40);
    level_fill_random(lvl,6);

    // Initialize state (and add enemies)
    state *sta = state_new();
    state_populate_random(lvl,sta,40);

    // Main loop
    while(!WindowShouldClose()){

        UpdateMusicStream(soundtrack);
        UpdateMusicStream(death);
        UpdateMusicStream(win);
        // Update input depending if keys are pressed or not
        sta->button_state[0] = IsKeyDown(KEY_D);
        sta->button_state[1] = IsKeyDown(KEY_W);
        sta->button_state[2] = IsKeyDown(KEY_A);
        sta->button_state[3] = IsKeyDown(KEY_S);
        sta->button_state[4] = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
        // Compute the angle the player is looking at from the mouse's position relative to the screen's center
        float mouse_y = GetMouseY()-GetScreenHeight()/2;
        float mouse_x = GetMouseX()-GetScreenWidth()/2;
        sta->aim_angle = atan2(-mouse_y,mouse_x);

        // Update the state
        state_update(lvl,sta,&score); // We put the argument score to update the player score
        
        // Drawing
        BeginDrawing();

            //Showing on screen hiscore and score
            DrawText(FormatText("Hiscore: %08i ", hiscore) ,10,5,30,GREEN);
            
            DrawText(FormatText("Score: %08i ", score) ,10,35,30,RED);   

            ClearBackground(RAYWHITE);

            draw_state(lvl, sta);

            DrawText("Presente profe!",190,200,20,LIGHTGRAY);

        EndDrawing();

        if(sta->pla.ent.hp <= 0){ // Player is death, play death sound and update hiscore
            PlayMusicStream(death);
            PauseMusicStream(soundtrack);
            change_hiscore(&score);//Changing hiscore in case the player beat the actual hiscore
            DrawText("You Lose :(", 255, 250, 40, BLACK);          
        } 
        if(sta->n_enemies == 0){ // Play win sound in case the player kills all the enemies
            PlayMusicStream(win);
            StopMusicStream(soundtrack);
            DrawText("All enemies killed :)", 255, 250, 40, GOLD);  
        }           
    }
    //Unload all audio
    UnloadMusicStream(death); 

    UnloadMusicStream(win);

    UnloadMusicStream(soundtrack);

    CloseAudioDevice();
    
    // Closer window
    CloseWindow();

    // Free memory
    state_free(sta);
    level_free(lvl);

    return 0;
}
