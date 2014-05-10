#include <cstdlib>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <iostream>
#include <vector>
#include "doodle.hh"
#include "include/Verlet.h"
#include "include/VerletEdge.h"
#include "include/Mesh.h"
#include "include/VerletBuilder.h"
#include "LuaExpose.h"
#include "ModelImport.h"
//#include "assimplib/include/assimp/Importer.hpp"

#define BUNNY
#undef BUNNY
// TODO convert for iterators into boost foreach?
//

SDL_Surface *screen;
Mesh *allPoints;
// LUA EXPOSURE
lua_State *LuaState;
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
static int latticeWrapper(lua_State *L)
{
    return 1;
}

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
    screen = SDL_SetVideoMode(1080, 720, 32,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }
    SDL_WM_SetCaption("Ooo Stretchy", NULL);
    //printf("goody\n");
    // set up test verlets
    allPoints = new Mesh; //mkLattice(10,10,10,10,4);// mkLattice(10, 20, 10, 10, 4); //(x,y,z,l,e)
    Mesh *temp;
    #ifndef BUNNY
    //temp = mkLattice(2,2,1000,10,2);
    //allPoints->mergeInto(temp);
    //delete temp;
    //printf("%d %d\n", temp->edges.size(), temp->verlets.size());
    temp = mkLattice(60,60,1,10,3);
    allPoints->mergeInto(temp);
    delete temp;
    //temp = mkLattice(40,30,3,10,4);
    //allPoints->mergeInto(temp);
    //delete temp;
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
                // FALL THROUGH
            case SDL_MOUSEBUTTONDOWN:
                // FALL THROUGH
            case SDL_MOUSEBUTTONUP:
                {
                    for (std::vector<Verlet*>::iterator i = allPoints->verlets.begin();
                i != allPoints->verlets.end(); ++i)
                        (*i)->eatEvent(event);
                }
            } // end switch
        } // end of message processing

        // physics loops

        allPoints->sim();
        allPoints->sim();
        //printf("physics fine\n");

        // DRAWING STARTS HERE
        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
        int stress;

        //drawLine(screen, 50, 50, 100, 100, rgb2Px(255, 0, 255));

        for (std::vector<VerletEdge*>::iterator i = allPoints->edges.begin();
                i != allPoints->edges.end(); ++i)
        {
            //printf("doodle");
            stress = (*i)->getStress() * 255;
            if (stress > 255) stress = 510 - stress;
            drawLine(screen, (*i)->m_a->m_x, (*i)->m_a->m_y, (*i)->m_b->m_x, (*i)->m_b->m_y, rgb2Px(255, 255-stress, 255-stress));
        }
        /*
        for (std::vector<Verlet*>::iterator i = allPoints->verlets.begin();
                i != allPoints->verlets.end(); ++i)
        {
            //printf("doodle");
            drawLine(screen, (*i)->m_x, (*i)->m_y, (*i)->m_x+2, (*i)->m_y, rgb2Px(240, 156, 0));
        }*/

        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);
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
