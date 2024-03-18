#include "state/overworld.h"
#include "rendering/renderer2D.h"
#include <iostream>


Overworld::~Overworld() {

}


void Overworld::OnEnter() {
    camera = OrthographicCamera(0.0f, 640.0f, 360.0f, 0.0f); //TODO get window size to provide correct viewport

    for(size_t y = 0; y < 150; y++) { //TODO MAY NEED TO SWITCH THESE
        for(size_t x = 0; x < 140; x++) {
            tiles.emplace_back(0, Forest, Sprite(0, {x, y}, 16, 16));
        }
    }

    map = std::make_unique<Map>("assets/maps/Test_map.txt");
}


void Overworld::OnExit() {

}


void Overworld::Update() {

}


void Overworld::Render() {
    Renderer2D::BeginScene(camera);

    // TODO Grab the visible map tiles and visible entities and draw them

    // Draw Base Layer
    for(int y = 0; y < map->GetHeight(); y++) {
        for(int x = 0; x < map->GetWidth(); x++) {
            const Sprite& sprite = tiles[map->GetTileIndex({x, y}, MapLayer::Base)].GetSprite();
            Renderer2D::DrawQuad({x  * 16, y * 16, 0.0f}, {sprite.width, sprite.height},
                {1.0f, 1.0f, 1.0f, 1.0f}, sprite.textureCoordinates, sprite.textureIndex);
        }
    }

    // Draw Object Layer
    for(int y = 0; y < map->GetHeight(); y++) {
        for(int x = 0; x < map->GetWidth(); x++) {
            const Sprite& sprite = tiles[map->GetTileIndex({x, y}, MapLayer::Object)].GetSprite();
            Renderer2D::DrawQuad({x  * 16, y * 16, 0.0f}, {sprite.width, sprite.height},
                {1.0f, 1.0f, 1.0f, 1.0f}, sprite.textureCoordinates, sprite.textureIndex);
        }
    }

    // Draw Top Layer
    for(int y = 0; y < map->GetHeight(); y++) {
        for(int x = 0; x < map->GetWidth(); x++) {
            const Sprite& sprite = tiles[map->GetTileIndex({x, y}, MapLayer::Top)].GetSprite();
            Renderer2D::DrawQuad({x  * 16, y * 16, 0.0f}, {sprite.width, sprite.height},
                {1.0f, 1.0f, 1.0f, 1.0f}, sprite.textureCoordinates, sprite.textureIndex);
        }
    }

    Renderer2D::EndScene();
}
