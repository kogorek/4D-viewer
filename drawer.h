#ifndef DRAWER_H
#define DRAWER_H

#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Drawer
{
    static glm::ivec2 viewPortSize;
    static glm::ivec2 viewPortPos;
    static SDL_Renderer *renderer;

    Drawer();
public:


    static void setRenderer(SDL_Renderer *rendr);
    static void viewPort(int x, int y, int w, int h);
    static void point(const glm::vec4 &point);
    static void line(const glm::vec4 &one, const glm::vec4 &two);
    static void text(TTF_Font *font, const std::string &message, const glm::ivec2 &pos, const glm::ivec4 &color = {255, 255, 255, 0});
    static void color(const glm::ivec4 &color);
    static void color(const glm::ivec3 &color);
    static void clear(const glm::ivec4 &color = {0, 0, 0, 0});
    static void draw();
};

#endif // DRAWER_H
