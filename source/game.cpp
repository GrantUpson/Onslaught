#include "game.h"
#include "window.h"
#include "utility/systemTimer.h"


bool Game::Initialize() {
    //TODO Load from settings

    //TODO Create window with settings loaded
    window = std::make_unique<Window>("Onslaught", true, true, 640, 360);

    return true;
}


void Game::Run() {
    constexpr uint32 UPDATES_PER_SECOND = 60;
    constexpr uint32 SKIP_TICKS = 1000 / UPDATES_PER_SECOND;
    constexpr uint32 MAX_FRAME_SKIP = 10;

    uint64 nextUpdate = SystemTimer::GetTickCountSinceInitialization();
    uint32 numLoops;

    while (isRunning) {
        numLoops = 0;

        while(SystemTimer::GetTickCountSinceInitialization() > nextUpdate && numLoops < MAX_FRAME_SKIP) {
            if (glfwGetKey(window->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                isRunning = false;
                break;
            }
            //TODO Process input properly
            //TODO Game updates

            nextUpdate += SKIP_TICKS;
            numLoops++;
        }


        //TODO Render properly




        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window->GetWindow());
        glfwPollEvents();
    }
}


void Game::Shutdown() {
    window->Close();
}




