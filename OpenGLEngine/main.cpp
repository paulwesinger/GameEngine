#include "engine/engine.h"
#include "logs/logs.h"


int main(int argc,char ** argv)
{


    CEngine * engine = new CEngine("Engine started");

    if ( ! engine ) {
        logwarn( "Failed to Create Object !!! \n Aborting ......");
        return 1;
    }

    if ( engine->InitSDL2()) {

        engine->Run();

    }
    else {
        logwarn(" Init SDL2 failed !! \n aborting ....");
        return 2;
    }
    engine->Done();

    delete engine;
}
