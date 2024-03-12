#ifndef OVERWORLD_H
#define OVERWORLD_H

#include "state.h"
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
    OrthographicCamera camera {0.0f, 640.0f, 360.0f, 0.0f};
    Owner<Map> map;
    std::vector<Tile> tiles;
};



#endif