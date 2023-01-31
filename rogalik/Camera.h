#pragma once
#include "GameObject.h"
#include "common.h"
class Camera :
    public GameObject
{
public:
    float zoom = 1.0;
    Camera(int ScreenWidth, int ScreenHeight) {
        ScreenW = ScreenWidth;
        ScreenH = ScreenHeight;
    }

    void cameraToScreenSpace(const Vector2 &relativeToCamera, Vector2 &screenCoords) {
        int halfW = ScreenW / 2, halfH = ScreenH / 2;
        screenCoords.x = relativeToCamera.x*zoom;
        screenCoords.y = -relativeToCamera.y*zoom;
        screenCoords.x += halfW;
        screenCoords.y += halfH;
    }
    
    void screenToCameraSpace(const Vector2 &screenCoords, Vector2 &relativeToCamera) {
        int halfW = ScreenW / 2, halfH = ScreenH / 2;
        relativeToCamera.x = screenCoords.x - halfW;
        relativeToCamera.y = screenCoords.y - halfH;
        relativeToCamera.x /= zoom;
        relativeToCamera.y /= -zoom;
    }


    void cameraToWorldSpace(const Vector2& relativeToCamera, Vector2& worldCoords) {
        worldCoords.x = relativeToCamera.x + pos.x;
        worldCoords.y = relativeToCamera.y + pos.y;
    }

    void worldToCameraSpace(const Vector2& worldCoords, Vector2& relativeToCamera) {
        relativeToCamera.x = worldCoords.x - pos.x;
        relativeToCamera.y = worldCoords.y - pos.y;
    }

    void worldToScreenSpace(const Vector2 &worldCoords, Vector2 &screenCoords) {
        Vector2 relativeToCamera;
        worldToCameraSpace(worldCoords, relativeToCamera);
        cameraToScreenSpace(relativeToCamera, screenCoords);
    }

    void screenToWorldSpace(const Vector2& screenCoords, Vector2& worldCoords) {
        Vector2 relativeToCamera;
        screenToCameraSpace(screenCoords, relativeToCamera);
        cameraToWorldSpace(relativeToCamera, worldCoords);
    }

    void update() {

    }
private:
    int ScreenW, ScreenH;
};

