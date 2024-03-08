#ifndef OVERWORLD_H
#define OVERWORLD_H

#include "state.h"
#include "types.h"
#include "maps/map.h"
#include "maps/tile.h"
#include "rendering/orthographicCamera.h"
#include <vector>


class Overworld : public State {
public:
    Overworld() = default;
    ~Overworld() override;

    void OnEnter() override;
    void OnExit() override;
    void Update() override;
    void Render() override;

private:
    Reference<OrthographicCamera> camera;
    Map map {};
    std::vector<Tile> tiles;
};



#endif