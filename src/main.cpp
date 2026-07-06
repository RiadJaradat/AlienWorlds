#include <fstream>
#include <cstdlib>
#include "Engine.hpp"

int main(int argc, char* argv[])
{
    try
    {
        Engine engine;
        engine.run();
    }
    catch (const std::exception &e){
        std::ofstream log("error.log", std::ios::app);
        log << "Engine Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}