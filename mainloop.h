#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <glm/glm.hpp>

#include "linearmath.h"
#include "camera.h"

class Application
{
private:
    SDL_Window *window = NULL;
    SDL_Renderer* renderer = NULL;
    bool limitingFps;
    bool running;
    // Tesseract angles: x, y, z, w1, w2
    glm::vec3 angles;
    glm::vec3 angles4D;
    glm::vec4 cubePos;
    float cubeSize;
    float deltaTime;
    Camera cam;

    mat5 modelMat4D;
    glm::mat4 mvp3D;

    const unsigned int maxFps = 60;
    const int winX = 800;
    const int winY = 600;

    TTF_Font *font;

    // If true all projections will be stereographic instead of orthogonal.
    bool stereogProj;
    // Figure type to draw.
    int fig;

    // Store two points of a line for cube edges.
    std::vector<std::pair<vec5, vec5>> cubeEdges;
    std::vector<std::pair<vec5, vec5>> sphereEdges;
    std::vector<std::pair<vec5, vec5>> torEdges;
    std::vector<vec5> sphereVertices;

    void initialize();
    void update();
    void draw();
    void events();
    void input();

    void limitFPS();
    float calcDeltaTime();

    void drawHyperSphere();
    void drawTesseract();
    void drawTor();

    void drawAxis();

public:
    Application();
    void execute();
};

#endif // APPLICATION_H
