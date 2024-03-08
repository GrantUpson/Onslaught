#include "state/overworld.h"
#include "rendering/renderer2D.h"
#include "utility/resourceLoader.h"


Overworld::~Overworld() {

}


void Overworld::OnEnter() {
    camera = std::make_shared<OrthographicCamera>(0.0f, 640.0f, 360.0f, 0.0f);

    //Temp
    tiles.emplace_back(Tile(Forest, 0, {7.0f, 0.0f})); //Grass
    tiles.emplace_back(Tile(Forest, 0, {1.0f, 3.0f})); //Rock
    tiles.emplace_back(Tile(Forest, 0, {9.0f, 6.0f})); //Grass Tuft
    tiles.emplace_back(Tile(Forest, 0, {17.0f, 4.0f})); //Mushroom

    map.tiles[10][13] = 1;
    map.tiles[23][18] = 3;
    map.tiles[19][5] = 2;
}


void Overworld::OnExit() {

}


void Overworld::Update() {

}


void Overworld::Render() {
    Renderer2D::BeginScene();
    ResourceLoader::GetShader("default")->SetUniformMatrix4("viewProjection", camera->GetViewProjectionMatrix());

    //TODO Grab the visible map tiles and visible entities and draw them
    for(int x = 0; x < 40; x++) {
        for(int y = 0; y < 23; y++) {
            Renderer2D::DrawQuad({Tile::width * x, Tile::height * y, 0.0f}, {Tile::width, Tile::height}, {1.0f, 1.0f, 1.0f, 1.0f}, tiles[map.tiles[x][y]].textureCoordinates, 1);
        }
    }

    Renderer2D::EndScene();
}
