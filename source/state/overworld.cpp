#include "state/overworld.h"
#include "rendering/renderer2D.h"


Overworld::~Overworld() {

}


void Overworld::OnEnter() {
    camera = OrthographicCamera(0.0f, 640.0f, 360.0f, 0.0f); //TODO get window size to provide correct viewport

    tiles.emplace_back(Tile(Forest, 0, {7.0f, 0.0f})); //Grass
    tiles.emplace_back(Tile(Forest, 0, {1.0f, 3.0f})); //Rock
    tiles.emplace_back(Tile(Forest, 0, {9.0f, 6.0f})); //Grass Tuft
    tiles.emplace_back(Tile(Forest, 0, {17.0f, 4.0f})); //Mushroom
    tiles.emplace_back(Tile(Forest, 0, {15.0f, 23.0f})); //Flower

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
        for(int x = 0; x < map->GetWidth(); x++) { // 0.5 is used to offset the fact that the center of the quad is the origin for positioning.
            Renderer2D::DrawQuad({(x + 0.5)  * Tile::width, (y + 0.5) * Tile::height, 0.0f}, {Tile::width, Tile::height},
                {1.0f, 1.0f, 1.0f, 1.0f}, tiles[map->GetTile({x, y})].textureCoordinates, 1);
        }
    }

    Renderer2D::EndScene();
}
