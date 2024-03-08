#ifndef RENDERER2D_H
#define RENDERER2D_H

#include "types.h"


class Renderer2D {
public:
    static void Initialize();
    static void Shutdown();

    static void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height);
    static void SetClearColour(const Vector4& colour);
    static void Clear();

    static void BeginScene();
    static void DrawQuad(const Vector3& position, const Vector2& size, const Vector4& colour, const Vector2& textureCoordinates, float textureIndex);
    static void EndScene();

    struct Statistics {
        uint32 drawCalls = 0;
        uint32 quadCount = 0;

        [[nodiscard]] uint32 GetTotalVertexCount() const { return quadCount * 4; }
        [[nodiscard]] uint32 GetTotalIndexCount() const { return quadCount * 6; }
    };

    static void ResetStatistics();
    static Statistics GetStatistics();

private:
    Renderer2D() = default;

    static void StartBatch();
    static void NextBatch();
    static void Flush();
};


#endif
