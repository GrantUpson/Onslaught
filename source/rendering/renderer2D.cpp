#include <string>
#include <iostream>
#include <array>

#include "rendering/renderer2D.h"

#include <glm/gtc/matrix_transform.hpp>

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

    QuadVertex* verticesBase = nullptr;
    QuadVertex* verticesOffset = nullptr;
    Vector4 quadVertexPositions[4];
    std::array<uint32, MAX_TEXTURE_SLOTS> textures {};

    Renderer2D::Statistics statistics;
} Data;


void Renderer2D::Initialize() {
    Data.verticesBase = new QuadVertex[MAX_VERTICES];

    Data.quadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
    Data.quadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
    Data.quadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
    Data.quadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

    glGenVertexArrays(1, &Data.vertexAttributes);
    glBindVertexArray(Data.vertexAttributes);

    glGenBuffers(1, &Data.vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, Data.vertexBuffer);
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

    glGenBuffers(1, &Data.indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Data.indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    ResourceLoader::LoadShader("default", "assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
    ResourceLoader::GetShader("default")->Bind();

    //TODO Load all textures
    ResourceLoader::LoadTexture("overworld", "assets/textures/overworld.png");
    glBindTexture(GL_TEXTURE_2D, ResourceLoader::GetTexture("overworld")->GetId());

    SetClearColour({0.0f, 0.0f, 0.0f, 1.0});

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void Renderer2D::Shutdown() {
    glDeleteVertexArrays(1, &Data.vertexAttributes);
    glDeleteBuffers(1, &Data.vertexBuffer);
    glDeleteBuffers(1, &Data.indexBuffer);

    delete[] Data.verticesBase;
}


void Renderer2D::SetViewport(const uint32 x, const uint32 y, const uint32 width, const uint32 height) {
    glViewport(x, y, width, height);
}


void Renderer2D::SetClearColour(const Vector4& colour) {
    glClearColor(colour.r, colour.g, colour.b, colour.a);
}


void Renderer2D::Clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}


void Renderer2D::BeginScene(const OrthographicCamera& camera) {
    ResourceLoader::GetShader("default")->SetUniformMatrix4("viewProjection", camera.GetViewProjectionMatrix());
    Clear();
    ResetStatistics();
    StartBatch();
}


void Renderer2D::EndScene() {
    Flush();
    std::cout << "Draw Calls: " << Data.statistics.drawCalls << "\nQuads Drawn: " << Data.statistics.quadCount << std::endl;
}


void Renderer2D::DrawQuad(const Vector3& position, const Vector2& size, const Vector4& colour, const Vector2 textureCoordinates[4], const float textureIndex) {
    const Matrix4 transform = translate(Matrix4(1.0f), position) * scale(Matrix4(1.0f), { size.x, size.y, 1.0f });
    DrawQuad(transform, colour, textureCoordinates, textureIndex);
}


void Renderer2D::DrawQuad(const Matrix4& transform, const Vector4& tintColour, const Vector2 textureCoordinates[4], const float textureIndex) {
    constexpr size_t QUAD_VERTEX_COUNT = 4;

    if(Data.indexCount >= MAX_INDICES) {
        NextBatch();
    }

    // BL -> BR -> TR -> TL
    for(size_t i = 0; i < QUAD_VERTEX_COUNT; ++i) {
        Data.verticesOffset->position = transform * Data.quadVertexPositions[i];
        Data.verticesOffset->colour = tintColour;
        Data.verticesOffset->textureCoordinates = textureCoordinates[i];
        Data.verticesOffset->textureIndex = textureIndex;
        Data.verticesOffset++;
    }

    Data.indexCount += 6;
    Data.statistics.quadCount++;
}


void Renderer2D::StartBatch() {
    Data.verticesOffset = Data.verticesBase;
    Data.indexCount = 0;
}


void Renderer2D::NextBatch() {
    Flush();
    StartBatch();
}


void Renderer2D::Flush() {
    if(Data.indexCount > 0) {
        const GLsizeiptr dataSize = (uint8_t*)Data.verticesOffset - (uint8_t*)Data.verticesBase;
        glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, (const void*)Data.verticesBase);

        glDrawElements(GL_TRIANGLES, Data.indexCount, GL_UNSIGNED_INT, nullptr);
        Data.statistics.drawCalls++;
    }
}


void Renderer2D::ResetStatistics() {
    Data.statistics.drawCalls = 0;
    Data.statistics.quadCount = 0;
}


Renderer2D::Statistics Renderer2D::GetStatistics() {
    return Data.statistics;
}
