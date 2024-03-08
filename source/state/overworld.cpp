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

    float centerX = 0.0f;
    float centerY = 0.0f;
    float quadWidth = 0.025f * 6; // Width of the quad
    float quadHeight = 0.0444f * 6; // Height of the quad
    float bottomLeftX = centerX - quadWidth / 2.0f;
    float bottomLeftY = centerY - quadHeight / 2.0f;

    Renderer2D::DrawQuad({bottomLeftX, bottomLeftY, 0.0f}, {quadWidth, quadHeight}, {1.0f, 1.0f, 0.0f, 1.0f}, {1.0f, 16.0f}, 1);

    Renderer2D::EndScene();
}
