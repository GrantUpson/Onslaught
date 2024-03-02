#include "state/overworld.h"
#include "rendering/renderer2D.h"


Overworld::~Overworld() {

}


void Overworld::OnEnter() {

}


void Overworld::OnExit() {

}


void Overworld::Update() {

}


void Overworld::Render() {
    Renderer2D::BeginScene();
    //TODO Grab the visible map tiles and visible entities and draw them.

    //TODO Remove after testing drawing quads dynamically
    for(float y = -10.0f; y < 10.0f; y += 0.25f) {
        for(float x = -10.0f; x < 10.0f; x += 0.25f) {
            Vector4 colour = {(x + 10) / 20.0f, 0.2f, (y + 10) / 20.0f, 1.0f };
            Renderer2D::DrawQuad({x, y, 0.0f}, {0.2f, 0.2f}, colour, {1, 1}, 1);
        }
    }

    Renderer2D::EndScene();
}
