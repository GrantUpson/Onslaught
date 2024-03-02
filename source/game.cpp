#include "game.h"

#include <iostream>
#include <ostream>

#include "window.h"
#include "rendering/renderer2D.h"
#include "state/gameState.h"
#include "state/overworld.h"


bool Game::Initialize() {
    //TODO Load from settings

    //TODO Create window with settings loaded
    window = std::make_unique<Window>("Onslaught", true, true, 640, 360);
    //window = std::make_unique<Window>("Onslaught", true, true, 1920, 1080);
    Renderer2D::Initialize();
    GameState::SetCurrentGameState(std::make_unique<Overworld>());

    return true;
}


void Game::Run() {
    constexpr double UPDATES_PER_SECOND = 60.0;
    constexpr double TIME_STEP = 1.0 / UPDATES_PER_SECOND;

    double lastTime = glfwGetTime();
    double accumulator = 0.0;

    // For calculating FPS and updates
    uint32_t frames = 0;
    uint32_t updates = 0;
    double timer = lastTime;


    while (isRunning) {
        double now = glfwGetTime();
        double frameTime = now - lastTime;
        lastTime = now;
        accumulator += frameTime;

        while (accumulator >= TIME_STEP) {
            if (glfwGetKey(window->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                isRunning = false;
                break;
            }

            GameState::GetCurrentGameState()->Update();

            updates++; // Updates tracking
            accumulator -= TIME_STEP;
        }

        GameState::GetCurrentGameState()->Render();
        frames++;  // FPS tracking

        glfwSwapBuffers(window->GetWindow());
        glfwPollEvents();

        // Log FPS and updates every second.
        if (now - timer >= 1.0) {
            std::cout << "FPS: " << frames << " Updates:" << updates << std::endl;
            timer += 1.0;
            frames = 0;
            updates = 0;
        }
    }
}


void Game::Shutdown() {
    Renderer2D::Shutdown();
    window->Close();
}




