#include <raylib.h>
#include <stdio.h>
#include <rcamera.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#define LOG(X) printf("%s: %d", __FILE__, __LINE__, X)
RenderTexture rt;
void hauptloop(){
    BeginDrawing();
    BeginTextureMode(rt);
    ClearBackground(CLITERAL(Color){0, 0, 0, 255});
    DrawCircle(GetMouseX(), GetMouseY(), 50, CLITERAL(Color){255,255,0,255});
    EndTextureMode();
    DrawTexture(rt.texture, 0, 0, CLITERAL(Color){255,255,255,255});
    EndDrawing();
}
int main(){
    int screenWidth = 1920;
    int screenHeight = 1080;
    
    InitWindow(screenWidth, screenHeight, "rtextures");
    SetTargetFPS(144);
    
    //LOG("OpenGL version: " << glGetString(GL_VERSION));
    rt = LoadRenderTexture(screenWidth, screenHeight);
    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(hauptloop, 0, 0);
    //emscripten_sleep(10000);
    #else
    while(!WindowShouldClose()){
        hauptloop();
    }
    #endif
    return 0;
}
