#include "state/overworld.h"
#include "rendering/renderer2D.h"


Overworld::~Overworld() {

}


void Overworld::OnEnter() {
    camera = OrthographicCamera(0.0f, 640.0f, 360.0f, 0.0f); //TODO get window size to provide correct viewport

    tiles.emplace_back(0, Forest, Sprite(0, {7.0f, 0.0f}, 16, 16)); //Grass
    tiles.emplace_back(0, Forest, Sprite(0, {1.0f, 3.0f}, 16, 16)); //Rock
    tiles.emplace_back(0, Forest, Sprite(0, {9.0f, 6.0f}, 16, 16)); //Grass Tuft
    tiles.emplace_back(0, Forest, Sprite(0, {17.0f, 4.0f}, 16, 16)); //Mushroom
    tiles.emplace_back(0, Forest, Sprite(0, {15.0f, 10.0f}, 16, 16)); //Flower
    tiles.emplace_back(0, Forest, Sprite(0, {16.0f, 9.0f}, 64, 112)); //Tree

    map = Map::LoadMap("Temp filepath");
}


void Overworld::OnExit() {

}


void Overworld::Update() {

}


void Overworld::Render() {
    Renderer2D::BeginScene(camera);

    //TODO Grab the visible map tiles and visible entities and draw them
    for(int y = 0; y < map->GetHeight(); y++) {
        for(int x = 0; x < map->GetWidth(); x++) {
            const Sprite& sprite = tiles[map->GetTile({x, y})].GetSprite();
            Renderer2D::DrawQuad({x  * 16, y * 16, 0.0f}, {sprite.width, sprite.height},
                {1.0f, 1.0f, 1.0f, 1.0f}, sprite.textureCoordinates, sprite.textureIndex);
        }
    }

    Renderer2D::DrawQuad({12  * 16, 12 * 16, 0.0f}, {64, 112},
                {1.0f, 1.0f, 1.0f, 1.0f}, tiles[5].GetSprite().textureCoordinates, tiles[5].GetSprite().textureIndex);

    Renderer2D::EndScene();
}
