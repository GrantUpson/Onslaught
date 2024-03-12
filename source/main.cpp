#include <memory>
#include "game.h"
#include "types.h"

int main() {
    Owner<Game> game = std::make_unique<Game>();

    if(game->Initialize()) {
        game->Run();
        game->Shutdown();
    }

    return 0;
}
