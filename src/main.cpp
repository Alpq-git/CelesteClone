#include "CelesteClone_lib.h"

#include "input.h"

#include "game.h"

#define APIENTRY
#define GL_GLEXT_PROTOTYPES  
#include "gl_renderer.h" 

static KeyCodeID KeyCodeLookupTable[KEY_COUNT];

#include "platform.h"
#ifdef _WIN32
#include "win32_platform.cpp"
#endif

#include "gl_renderer.cpp"

//########################################################################
//                      Game DLL Stuff(Hot Code Reloading)
//########################################################################


//########################################################################
//                      Game DLL Stuff(Hot Code Reloading)
//########################################################################

//this is the function pointer to update_game in game.cpp
typedef decltype(update_game) update_game_type;
static update_game_type* update_game_ptr;


//########################################################################
//                      Cross Platform functions
//########################################################################
void reload_game_dll(BumpAllocator* transientStorage);

int main()
{

    BumpAllocator transientStorage = make_bump_allocator(MB(50));
    BumpAllocator persistentStorage = make_bump_allocator(MB(50));

    input = (Input*)bump_alloc(&persistentStorage, sizeof(Input));
    if(!input)
    {
        SM_ERROR("Failed to allocate Input");
        return -1;
    }

    renderData = (RenderData*)bump_alloc(&persistentStorage, sizeof(RenderData));
    if(!renderData)
    {
        SM_ERROR("Failed to allocate RenderData");
        return -1;
    }

    platform_fill_keycode_lookup_table();
    platform_create_window(1280, 640, "Celeste Clone Motor");


    gl_init(&transientStorage);

    while(running)
    {
        //Update
        platform_update_window();
        update_game(gameState, renderData, input);
        gl_render();

        platform_swap_buffers(); 

        transientStorage.used = 0;
    } 

    return 0;
}

void update_game(GameState* gameStateIn, RenderData* renderDataIn, Input* inputIn)
{
    update_game_ptr(gameStateIn, renderDataIn,inputIn);
}

void reload_game_dll(BumpAllocator* transientStorage)
{
    static void* gameDll;
    static long long lastEditTimestampGameDll;

    long long currentTimestampGameDll = get_timestamp("game.dll");
    if(currentTimestampGameDll > lastEditTimestampGameDll)
    {
        if(gameDll)
        {
            bool freeResult = platform_free_dynamic_library(gameDll);
            SM_ASSERT(freeResult, "Failed to free game.dll");
            gameDll = nullptr;
            SM_TRACE("Free game.dll");
        }

        while(!copy_file("game.dll", "game_load.dll", transientStorage))
        {
            Sleep(10);
        }
        SM_TRACE("Copied game.dll into game_load.dll");

        gameDll = platform_load_dynamic_library("game_load.dll");
        SM_ASSERT(gameDll, "Failed to load game.dll");

        update_game_ptr = (update_game_type*)platform_load_dynamic_function(gameDll, "update_game");
        SM_ASSERT(update_game_ptr, "Failed to load update_game function");
        lastEditTimestampGameDll = currentTimestampGameDll;
    }
}
