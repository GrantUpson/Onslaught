#ifndef OVERWORLD_H
#define OVERWORLD_H

#include "state.h"
#include "gameplay/player.h"
#include "rendering/orthographicCamera.h"


class Overworld : public State {
public:
    Overworld() = default;
    ~Overworld() override;

    void OnEnter() override;
    void OnExit() override;
    void Update() override;
    void Render() override;
private:
    Player player {{1.0f, 1.0f}};
    OrthographicCamera camera {1.0f, 1.0f, 1.0f, 1.0f};
};



#endif