#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include <vector>
#include "doodle.hh"
#include "include/Verlet.h"
#include "include/VerletEdge.h"
#include "include/Mesh.h"
#include "include/VerletBuilder.h"
// #include "LuaExpose.h"
#include "ModelImport.h"
//#include "assimplib/include/assimp/Importer.hpp"

#define BUNNY
#undef BUNNY
// TODO convert for iterators into boost foreach?
//

SDL_Window *screen;
SDL_Renderer *renderer;
Mesh *allPoints;
// LUA EXPOSURE
// lua_State *LuaState;
/*
int initLua()
{
    LuaState = luaL_newstate();
    luaL_openlibs(LuaState);
    lua_pushcfunction(LuaState, latticeWrapper);
    lua_setglobal(LuaState, "mkLattice");

    if (luaL_loadfile(LuaState, "scripts/init.lua")) {
        std::cerr << "Something went wrong loading the chunk (syntax error?)" << std::endl;
        std::cerr << lua_tostring(LuaState, -1) << std::endl;
        lua_pop(LuaState,1);
    }

    printf("lua initialized properly\n");
    return 0;
}*/
// static int latticeWrapper(lua_State *L)
// {
//     return 1;
// }

//

int init()
{

    // initialize SDL video
    if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    screen = SDL_CreateWindow("Ooo Stretchy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1080, 720, SDL_WINDOW_OPENGL);
    if ( !screen ) {
        printf("Unable to create window: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(screen, -1, 0);

    if ( !renderer ) {
        printf("Unable to create renderer: %s\n", SDL_GetError());
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    //printf("goody\n");
    // set up test verlets
    allPoints = new Mesh; //mkLattice(10,10,10,10,4);// mkLattice(10, 20, 10, 10, 4); //(x,y,z,l,e)
    Mesh *temp;
    #ifndef BUNNY
    //temp = mkLattice(2,2,1000,10,2);
    //allPoints->mergeInto(temp);
    //delete temp;
    //printf("%d %d\n", temp->edges.size(), temp->verlets.size());
    temp = mkLattice(2,500,2,5,3);
    allPoints->mergeInto(temp);
    delete temp;
    // temp = mkLattice(60,60,2,10,4);
    // allPoints->mergeInto(temp);
    // delete temp;
    #else
    temp = ImportObj("bunny.obj");
    printf("managed to import\n");
    allPoints->mergeInto(temp);
    delete temp;
    #endif
    //allPoints->verlets.push_back(new Verlet(200, 100));
    //allPoints->verlets.push_back(new Verlet(100, 200));
    //verlets[0]->held = true;
    //allPoints->edges.push_back(new VerletEdge(allPoints->verlets[0], allPoints->verlets[1], 100, 50));

    //printf("hi\n");

    return 0;
}

void runLoop()
{

    // program main loop
    bool done = false;
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    if (event.key.keysym.sym == SDLK_SPACE)
                        for (std::vector<VerletEdge*>::iterator i = allPoints->edges.begin();
                i != allPoints->edges.end(); ++i)
                            (*i)->freeze();
                    else if (event.key.keysym.sym == SDLK_z)
                        for (std::vector<VerletEdge*>::iterator i = allPoints->edges.begin();
                            i != allPoints->edges.end(); ++i)
                                (*i)->stretch(10);
                    else if (event.key.keysym.sym == SDLK_x)
                        for (std::vector<VerletEdge*>::iterator i = allPoints->edges.begin();
                            i != allPoints->edges.end(); ++i)
                                (*i)->stretch(-10);
                    // exit if ESCAPE is pressed
                    else if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;
                }
            case SDL_MOUSEMOTION:
                // when mouse down and moved, grabbed verlets get moved
                {
                    for (std::vector<Verlet*>::iterator i = allPoints->verlets.begin();
                i != allPoints->verlets.end(); ++i)
                        (*i)->drag(event.motion.x, event.motion.y);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                {
                    for (std::vector<Verlet*>::iterator i = allPoints->verlets.begin();
                i != allPoints->verlets.end(); ++i)
                        (*i)->grab(event.button.x, event.button.y);
                }
                break;
            case SDL_MOUSEBUTTONUP:
                {
                    for (std::vector<Verlet*>::iterator i = allPoints->verlets.begin();
                i != allPoints->verlets.end(); ++i)
                        (*i)->release();
                }
                break;
            default:;
            } // end switch
        } // end of message processing

        // physics loops

        allPoints->sim();
        allPoints->sim();
        //printf("physics fine\n");

        // DRAWING STARTS HERE
        // clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        int stress;

        //drawLine(screen, 50, 50, 100, 100, rgb2Px(255, 0, 255));

        for (std::vector<VerletEdge*>::iterator i = allPoints->edges.begin();
                i != allPoints->edges.end(); ++i)
        {
            //printf("doodle");
            stress = (*i)->getStress() * 255;
            if (stress > 255) stress = 510 - stress;
            SDL_SetRenderDrawColor(renderer, 255, 255-stress, 255-stress, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawLine(renderer, (*i)->m_a->m_x, (*i)->m_a->m_y, (*i)->m_b->m_x, (*i)->m_b->m_y);
        }
        /*
        for (std::vector<Verlet*>::iterator i = allPoints->verlets.begin();
                i != allPoints->verlets.end(); ++i)
        {
            //printf("doodle");
            drawLine(screen, (*i)->m_x, (*i)->m_y, (*i)->m_x+2, (*i)->m_y, rgb2Px(240, 156, 0));
        }*/

        SDL_RenderPresent(renderer);
    } // end main loop

}

void cleanUp()
{
    // free stuff
    allPoints->wipe();

}

int main ( int argc, char** argv )
{

    init();
    //initLua();

    printf("about to run\n");
    runLoop();

    cleanUp();
    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
