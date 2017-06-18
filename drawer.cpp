#include "drawer.h"

glm::ivec2 Drawer::viewPortSize;
glm::ivec2 Drawer::viewPortPos;
SDL_Renderer *Drawer::renderer;

void Drawer::setRenderer(SDL_Renderer *rendr)
{
    renderer = rendr;
}

void Drawer::viewPort(int x, int y, int w, int h)
{
    viewPortSize.x = w;
    viewPortSize.y = h;

    viewPortPos.x = x;
    viewPortPos.y = y;
}

void Drawer::point(const glm::vec4 &point)
{
    glm::vec2 ndcPoint = {point.x/point.w, point.y/point.w};
    glm::vec2 ssPoint = {ndcPoint.x*viewPortSize.x/2+(viewPortPos.x+viewPortSize.x/2),
                         ndcPoint.y*viewPortSize.y/2+(viewPortPos.y+viewPortSize.y/2)};
    SDL_RenderDrawPoint(renderer, ssPoint.x, ssPoint.y);
}

void Drawer::line(const glm::vec4 &one, const glm::vec4 &two)
{
    //ndc stands for Normalized Device Coordinats.
    //ss stands for Screen Space.
    glm::vec3 ndcOne = {one.x/one.w, one.y/one.w, one.z/one.w};
    glm::vec3 ssOne = {ndcOne.x*viewPortSize.x/2+(viewPortPos.x+viewPortSize.x/2),
                       ndcOne.y*viewPortSize.y/2+(viewPortPos.y+viewPortSize.y/2),
                       ndcOne.z};

    glm::vec3 ndcTwo = {two.x/two.w, two.y/two.w, two.z/two.w};
    glm::vec3 ssTwo = {ndcTwo.x*viewPortSize.x/2+(viewPortPos.x+viewPortSize.x/2),
                       ndcTwo.y*viewPortSize.y/2+(viewPortPos.y+viewPortSize.y/2),
                       ndcTwo.z};

    SDL_RenderDrawLine(renderer, ssOne.x, ssOne.y, ssTwo.x, ssTwo.y);
}

void Drawer::text(TTF_Font *font, const std::string &message, const glm::ivec2 &pos, const glm::ivec4 &color)
{
    SDL_Color textColor;
    textColor.r = color.r;
    textColor.g = color.g;
    textColor.b = color.b;
    textColor.a = color.a;

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, message.c_str(), textColor);
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, textSurface);
    int text_width = textSurface->w;
    int text_height = textSurface->h;
    SDL_FreeSurface(textSurface);
    SDL_Rect renderQuad = {pos.x, pos.y, text_width, text_height};
    SDL_RenderCopy(renderer, text, NULL, &renderQuad);
    SDL_DestroyTexture(text);
}

void Drawer::color(const glm::ivec4 &color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void Drawer::color(const glm::ivec3 &color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
}

void Drawer::clear(const glm::ivec4 &color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
}

void Drawer::draw()
{
    SDL_RenderPresent(renderer);
}
