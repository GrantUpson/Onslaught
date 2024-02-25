#include "game.h"
#include "window.h"
#include "state/gameState.h"
#include "state/overworld.h"
#include "utility/systemTimer.h"


bool Game::Initialize() {
    //TODO Load from settings

    //TODO Create window with settings loaded
    window = std::make_unique<Window>("Onslaught", true, true, 640, 360);
    GameState::SetCurrentGameState(std::make_unique<Overworld>());

    return true;
}


void Game::Run() {
    constexpr uint32 UPDATES_PER_SECOND = 60;
    constexpr uint32 SKIP_TICKS = 1000 / UPDATES_PER_SECOND;
    constexpr uint32 MAX_FRAME_SKIP = 10;

    uint64 nextUpdate = SystemTimer::GetTickCountSinceInitialization();

    while (isRunning) {
        uint32 numLoops = 0;

        while(SystemTimer::GetTickCountSinceInitialization() > nextUpdate && numLoops < MAX_FRAME_SKIP) {
            if (glfwGetKey(window->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                isRunning = false;
                break;
            }
            //TODO Process input properly

            GameState::GetCurrentGameState()->Update();

            nextUpdate += SKIP_TICKS;
            numLoops++;
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        GameState::GetCurrentGameState()->Render();

        glfwSwapBuffers(window->GetWindow());
        glfwPollEvents();
    }
}


void Game::Shutdown() {
    window->Close();
}




