#include <raylib.h>
#include <stdio.h>
#include <rcamera.h>
#include <time.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#define LOG(X) printf("%s: %d", __FILE__, __LINE__, X)
RenderTexture rt;

#ifdef __EMSCRIPTEN__
EM_JS(void, idbfs_put, (const char* filename, const char* str), {
    FS.writeFile(UTF8ToString(filename), UTF8ToString(str));
    FS.syncfs(false,function (err) {
        assert(!err);
    });
});
EM_JS(char*, idbfs_get, (const char* filename), {
    var arr = FS.readFile(UTF8ToString(filename));
    var jsString = new TextDecoder().decode(arr);
    var lengthBytes = lengthBytesUTF8(jsString)+1;
    //console.log(jsString);
    var stringOnWasmHeap = _malloc(lengthBytes);
    stringToUTF8(jsString, stringOnWasmHeap, lengthBytes);
    return stringOnWasmHeap;
});
#endif
const char* someResource = 0;


void gameLoop(){
    BeginDrawing();
    BeginTextureMode(rt);
    ClearBackground(CLITERAL(Color){0, 0, 0, 255});
    DrawCircle(GetMouseX(), GetMouseY(), 50, CLITERAL(Color){255,255,0,255});
    EndTextureMode();
    DrawTexture(rt.texture, 0, 0, CLITERAL(Color){255,255,255,255});
    DrawFPS(0, 0);
    #ifdef __EMSCRIPTEN__
    char* text = idbfs_get("file.txt");
    DrawText(TextFormat("Dynamic file content: %s", text), 0, 30, 20, WHITE);
    #endif
    DrawText(TextFormat("Static file content: %s", someResource), 0, 60, 20, WHITE);
    EndDrawing();
}
int main(){
    int screenWidth = 1920;
    int screenHeight = 1080;
    
    InitWindow(screenWidth, screenHeight, "rtextures");
    SetTargetFPS(144);
    rt = LoadRenderTexture(screenWidth, screenHeight);
    someResource = LoadFileText("../resources/dummy.txt");

    #ifdef __EMSCRIPTEN__
    EM_ASM(
        FS.mkdir('/work');
        FS.mount(IDBFS, {}, '/work');
        FS.syncfs(true, function (err){
            assert(!err);
        });
    );
    struct timespec ts = {.tv_sec = 0,  .tv_nsec = 100000000};
    struct timespec ts2 = {.tv_sec = 0, .tv_nsec = 100000000};
    nanosleep(&ts, &ts2);
    idbfs_put("file.txt", "Some dynamic file contents...\n");
    emscripten_set_main_loop(gameLoop, 0, 0);
    #else
    while(!WindowShouldClose()){
        gameLoop();
    }
    #endif
    return 0;
}
