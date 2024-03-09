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

    static constexpr uint64 timeToHit = 500;
    static uint64 time;

    time++;

    if(time >= timeToHit) {
        map->SetTile(1, {15, 14});
    }

    //TODO Grab the visible map tiles and visible entities and draw them
    for(int x = 0; x < 40; x++) {
        for(int y = 0; y < 23; y++) {
            Renderer2D::DrawQuad({x * Tile::width, y * Tile::height, 0.0f}, {Tile::width, Tile::height},
                {1.0f, 1.0f, 1.0f, 1.0f}, tiles[map->GetTile({x, y})].textureCoordinates, 1);
        }
    }

    Renderer2D::EndScene();
}
