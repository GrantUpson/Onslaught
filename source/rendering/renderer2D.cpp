#include <string>
#include <iostream>
#include <array>

#include "rendering/renderer2D.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "types.h"
#include "utility/resourceLoader.h"


static constexpr size_t MAX_QUADS = 10000;
static constexpr size_t MAX_VERTICES = MAX_QUADS * 4;
static constexpr size_t MAX_INDICES = MAX_QUADS * 6;
static constexpr size_t MAX_TEXTURE_SLOTS = 16;


struct QuadVertex {
    Vector3 position;
    Vector4 colour;
    Vector2 textureCoordinates;
    float textureIndex = 0;
};


static struct RendererData {
    uint32 vertexBuffer = 0;
    uint32 vertexAttributes = 0;
    uint32 indexBuffer = 0;
    uint32 indexCount = 0;

    Vector4 quadVertexPositions[4];
    QuadVertex* verticesBase = nullptr;
    QuadVertex* verticesOffset = nullptr;
    std::array<uint32, MAX_TEXTURE_SLOTS> textures {};

    Matrix4 projection;

    Renderer2D::Statistics statistics;
} RendererData;


void Renderer2D::Initialize() {
    RendererData.verticesBase = new QuadVertex[MAX_VERTICES];

    RendererData.quadVertexPositions[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
    RendererData.quadVertexPositions[0] = { 0.5f, -0.5f, 0.0f, 1.0f};
    RendererData.quadVertexPositions[0] = { 0.5f,  0.5f, 0.0f, 1.0f};
    RendererData.quadVertexPositions[0] = {-0.5f,  0.5f, 0.0f, 1.0f};

    glGenVertexArrays(1, &RendererData.vertexAttributes);
    glBindVertexArray(RendererData.vertexAttributes);

    glGenBuffers(1, &RendererData.vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, RendererData.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, MAX_VERTICES * sizeof(QuadVertex), nullptr, GL_DYNAMIC_DRAW);

    // Position attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)0);
    glEnableVertexAttribArray(0);

    // Colour attributes
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, colour));
    glEnableVertexAttribArray(1);

    // Texture coordinates attributes
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, textureCoordinates));
    glEnableVertexAttribArray(2);

    // Texture index attribute
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, textureIndex));
    glEnableVertexAttribArray(3);

    uint32 indices[MAX_INDICES];
    uint32 offset = 0;

    for(uint32 i = 0; i < MAX_INDICES; i += 6) {
        indices[i + 0] = 0 + offset;
        indices[i + 1] = 1 + offset;
        indices[i + 2] = 2 + offset;

        indices[i + 3] = 2 + offset;
        indices[i + 4] = 3 + offset;
        indices[i + 5] = 0 + offset;

        offset += 4;
    }

    glGenBuffers(1, &RendererData.indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererData.indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    ResourceLoader::LoadShader("default", "assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
    ResourceLoader::GetShader("default")->Bind();

    //TODO setup and load all game textures here
    /*const int32 location = glGetUniformLocation(ResourceLoader::GetShader("default")->GetId(), "textures");
    int32 samplers[MAX_TEXTURE_SLOTS];

    for(int32 i = 0; i < MAX_TEXTURE_SLOTS; i++) {
        samplers[i] = i;
    }



    SetClearColour({1.0f, 0.0f, 0.0f, 1.0f}); */
}


void Renderer2D::Shutdown() {
    glDeleteVertexArrays(1, &RendererData.vertexAttributes);
    glDeleteBuffers(1, &RendererData.vertexBuffer);
    glDeleteBuffers(1, &RendererData.indexBuffer);

    delete[] RendererData.verticesBase;
}


void Renderer2D::SetViewport(const uint32 x, const uint32 y, const uint32 width, const uint32 height) {
    glViewport(x, y, width, height);
}


void Renderer2D::SetClearColour(const Vector4 colour) {
    glClearColor(colour.r, colour.g, colour.b, colour.a);
}


void Renderer2D::Clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}


void Renderer2D::BeginScene() {
    Clear();
    ResetStatistics();
    StartBatch();
}


void Renderer2D::EndScene() {
    Flush();
    std::cout << "Draw Calls: " << RendererData.statistics.drawCalls << "\nQuads Drawn: " << RendererData.statistics.quadCount << std::endl;
}


void Renderer2D::DrawQuad(const Vector3& position, const Vector2& size, const Vector4& colour, const Vector2& textureCoordinates, const float textureIndex) {
    if(RendererData.indexCount >= MAX_INDICES) {
        NextBatch();
    }

    // Vertex 1
    RendererData.verticesOffset->position = position;
    RendererData.verticesOffset->colour = colour;
    RendererData.verticesOffset->textureCoordinates = textureCoordinates;
    RendererData.verticesOffset->textureIndex = textureIndex;
    RendererData.verticesOffset++;

    // Vertex 2
    RendererData.verticesOffset->position = {position.x + size.x, position.y, position.z};
    RendererData.verticesOffset->colour = colour;
    RendererData.verticesOffset->textureCoordinates = textureCoordinates;
    RendererData.verticesOffset->textureIndex = textureIndex;
    RendererData.verticesOffset++;

    // Vertex 3
    RendererData.verticesOffset->position = {position.x + size.x, position.y + size.y, position.z};
    RendererData.verticesOffset->colour = colour;
    RendererData.verticesOffset->textureCoordinates = textureCoordinates;
    RendererData.verticesOffset->textureIndex = textureIndex;
    RendererData.verticesOffset++;

    // Vertex 4
    RendererData.verticesOffset->position = {position.x, position.y + size.y, position.z};
    RendererData.verticesOffset->colour = colour;
    RendererData.verticesOffset->textureCoordinates = textureCoordinates;
    RendererData.verticesOffset->textureIndex = textureIndex;
    RendererData.verticesOffset++;

    RendererData.indexCount += 6;
    RendererData.statistics.quadCount++;
}


void Renderer2D::DrawTile(const Vector3& position, const Vector2& size, const Vector4& colour, const Tile& textureCoordinates, const float textureIndex) {
    if(RendererData.indexCount >= MAX_INDICES) {
        NextBatch();
    }

    // Vertex 1

    RendererData.verticesOffset->colour = colour;
    RendererData.verticesOffset->textureCoordinates = textureCoordinates.textureCoordinates[0];
    RendererData.verticesOffset->textureIndex = textureIndex;
    RendererData.verticesOffset++;

    // Vertex 2
    RendererData.verticesOffset->position = {position.x + size.x, position.y, position.z};
    RendererData.verticesOffset->colour = colour;
    RendererData.verticesOffset->textureCoordinates = textureCoordinates.textureCoordinates[1];
    RendererData.verticesOffset->textureIndex = textureIndex;
    RendererData.verticesOffset++;

    // Vertex 3
    RendererData.verticesOffset->position = {position.x + size.x, position.y + size.y, position.z};
    RendererData.verticesOffset->colour = colour;
    RendererData.verticesOffset->textureCoordinates = textureCoordinates.textureCoordinates[2];
    RendererData.verticesOffset->textureIndex = textureIndex;
    RendererData.verticesOffset++;

    // Vertex 4
    RendererData.verticesOffset->position = {position.x, position.y + size.y, position.z};
    RendererData.verticesOffset->colour = colour;
    RendererData.verticesOffset->textureCoordinates = textureCoordinates.textureCoordinates[3];
    RendererData.verticesOffset->textureIndex = textureIndex;
    RendererData.verticesOffset++;

    RendererData.indexCount += 6;
    RendererData.statistics.quadCount++;
}


void Renderer2D::StartBatch() {
    RendererData.verticesOffset = RendererData.verticesBase;
    RendererData.indexCount = 0;
}


void Renderer2D::NextBatch() {
    Flush();
    StartBatch();
}


void Renderer2D::Flush() {
    if(RendererData.indexCount > 0) {
        GLsizeiptr dataSize = (uint8_t*)RendererData.verticesOffset - (uint8_t*)RendererData.verticesBase;
        glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, (const void*)RendererData.verticesBase);

        glDrawElements(GL_TRIANGLES, RendererData.indexCount, GL_UNSIGNED_INT, nullptr);
        RendererData.statistics.drawCalls++;
    }
}


void Renderer2D::ResetStatistics() {
    RendererData.statistics.drawCalls = 0;
    RendererData.statistics.quadCount = 0;
}


Renderer2D::Statistics Renderer2D::GetStatistics() {
    return RendererData.statistics;
}
