#include "mainloop.h"

#include <iostream>
#include <vector>

#include "linearmath.h"

#include <glm/gtx/transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "drawer.h"

void Application::initialize()
{
    if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 )
    {
        std::cerr << "Unable to init SDL, error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    TTF_Init();

    window = SDL_CreateWindow("Tesseract", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winX, winY, SDL_WINDOW_SHOWN);

    if(window == 0)
    {
        std::cerr << "Cannot create window: " << SDL_GetError() << std::endl;
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == 0)
    {
        std::cerr << "Cannot create renderer: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Generate cube edges.
    {
        for(int w = 0; w < 2; w++)
            for(int z = 0; z < 2; z++)
                for(int x = 0; x < 2; x++)
                    cubeEdges.push_back(std::make_pair(vec5(x-0.5, 0.0-0.5, z-0.5f, w-0.5f, 1.0f), vec5(x-0.5, 1.0f-0.5, z-0.5f, w-0.5f, 1.0f)));

        for(int w = 0; w < 2; w++)
            for(int y = 0; y < 2; y++)
                for(int x = 0; x < 2; x++)
                    cubeEdges.push_back(std::make_pair(vec5(x-0.5, y-0.5, 0.0f-0.5f, w-0.5f, 1.0f), vec5(x-0.5, y-0.5, 1.0f-0.5f, w-0.5f, 1.0f)));


        for(int w = 0; w < 2; w++)
            for(int y = 0; y < 2; y++)
                for(int z = 0; z < 2; z++)
                    cubeEdges.push_back(std::make_pair(vec5(0.0f-0.5, y-0.5, z-0.5f, w-0.5f, 1.0f), vec5(1.0f-0.5, y-0.5, z-0.5f, w-0.5f, 1.0f)));


        for(int x = 0; x < 2; x++)
            for(int y = 0; y < 2; y++)
                for(int z = 0; z < 2; z++)
                    cubeEdges.push_back(std::make_pair(vec5(x-0.5, y-0.5, z-0.5f, 0.0f-0.5f, 1.0f), vec5(x-0.5, y-0.5, z-0.5f, 1.0f-0.5f, 1.0f)));
    }

    // Here's how I generate tesseract's vertices if you curious.
    //    std::vector<vec5> vertices;
    //    for(int w = 0; w < 2; w++)
    //        for(int z = 0; z < 2; z++)
    //            for(int y = 0; y < 2; y++)
    //                for(int x = 0; x < 2; x++)
    //                    vertices.push_back(vec5(x-0.5, y-0.5, z-0.5, w-0.5, 1.0f));

    // Generate Hypersphere vertices
    for(float alpha = 0; alpha < 2*M_PI; alpha+=M_PI/12)
    {
        for(float phi = 0; phi < M_PI; phi+=M_PI/12)
        {
            for(float theta = 0; theta < M_PI; theta+=M_PI/12)
            {
                float x = cos(phi);
                float y = sin(phi)*cos(theta);
                float z = sin(phi)*sin(theta)*cos(alpha);
                float w = sin(phi)*sin(theta)*sin(alpha);
                sphereVertices.push_back({x, y, z, w, 1.0f});
            }
        }
    }


//    for(float phi = M_PI/12; phi < M_PI; phi+=M_PI/12)
//    {
//        sphereEdges.push_back(std::make_pair(vec5(cos(phi), sin(phi)*cos(0), sin(phi)*sin(0), 0.0f, 1.0f)
//                                             , vec5(cos(phi), sin(phi)*cos(M_PI/12), sin(phi)*sin(M_PI/12), 0.0f, 1.0f)));
//        for(float theta = 0; theta < 2*M_PI; theta+=M_PI/12)
//        {
//            float x = cos(phi);
//            float y = sin(phi)*cos(theta);
//            float z = sin(phi)*sin(theta);
//            vec5 prevPoint = sphereEdges.back().second;
//            sphereEdges.push_back(std::make_pair(prevPoint, vec5{x, y, z, 0.0f, 1.0f}));
//        }
//    }

    //        sphereEdges.push_back(std::make_pair(vec5{cos(0), sin(0)*cos(0), sin(0)*sin(0), 0.0f, 1.0f}
    //                                           , vec5{cos(0), sin(0)*cos(M_PI/12), sin(0)*sin(M_PI/12), 0.0f, 1.0f}));
//    for(float phi = M_PI/12; phi < 2*M_PI; phi+=M_PI/12)
//    {
//        for(float theta = 0; theta < M_PI; theta+=M_PI/12)
//        {
//            float x = cos(theta);
//            float y = sin(theta)*cos(phi);
//            float z = sin(theta)*sin(phi);
//            vec5 prevPoint = sphereEdges.back().second;
//            sphereEdges.push_back(std::make_pair(prevPoint, vec5{x, y, z, 0.0f, 1.0f}));
//        }
//    }

    // Generating tor lines
    {
        for(float theta = 0; theta < 2*M_PI; theta+=M_PI/12)
        {
            torEdges.push_back(std::make_pair(vec5(cos(0), sin(0), cos(theta), sin(theta), 1.0f)
                                              , vec5(cos(M_PI/12), sin(M_PI/12), cos(theta), sin(theta), 1.0f)));
            for(float phi = M_PI/12; phi < M_PI*2; phi+=M_PI/12)
            {
                float x = cos(phi);
                float y = sin(phi);
                float z = cos(theta);
                float w = sin(theta);
                torEdges.push_back(std::make_pair(torEdges.back().second
                                                  , vec5(x, y, z, w, 1.0f)));
            }
        }

        for(float phi = M_PI/12; phi < M_PI*2; phi+=M_PI/12)
        {
            for(float theta = 0; theta < 2*M_PI; theta+=M_PI/12)
            {
                float x = cos(phi);
                float y = sin(phi);
                float z = cos(theta);
                float w = sin(theta);
                torEdges.push_back(std::make_pair(torEdges.back().second
                                                  , vec5(x, y, z, w, 1.0f)));
            }
        }
    }

    font = TTF_OpenFont("LiberationSerif.ttf", 16);
    if(font == nullptr)
    {
        std::cout << SDL_GetError() << std::endl;
        exit(1);
    }

    cam.Position = {-12, 0,0};
    cam.Yaw = 90;
    cam.Pitch = 180;
    cam.setPerspectiveMode(75.0f, winX/(float)winY, 0.001f, 100.0f);

    Drawer::viewPort(0, 0, winX, winY);
    Drawer::setRenderer(renderer);
}

void Application::update()
{
    mat5 scaleMatrix4D = scale(glm::vec4(cubeSize));
    mat5 posMatrix4D = translate(cubePos);
    mat5 rotateMatrix4D = rotateYZ4D(angles.x)*rotateXZ4D(angles.y)*rotateXY4D(angles.z)*
            rotateXW4D(angles4D.x)*rotateYW4D(angles4D.y)*rotateZW4D(angles4D.z);
    modelMat4D = posMatrix4D*scaleMatrix4D*rotateMatrix4D;

    glm::vec3 pos(0.0f);
    glm::vec3 scale(1.0f);
    glm::vec3 rot(0.0f);

    glm::mat4 posMat = glm::translate(pos);
    glm::mat4 scaleMat = glm::scale(scale);
    glm::mat4 rotX = glm::rotate(glm::radians(rot.x), glm::vec3(1.0, 0.0, 0.0));
    glm::mat4 rotY = glm::rotate(glm::radians(rot.y), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 rotZ = glm::rotate(glm::radians(rot.z), glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 rotMat = rotX * rotY * rotZ;
    glm::mat4 modelMatrix = posMat * rotMat * scaleMat;

    glm::mat4 projectionMat = cam.getProjectionMatrix();
    glm::mat4 viewMat = cam.getViewMatrix();

    mvp3D = projectionMat * viewMat * modelMatrix;
}

void Application::draw()
{
    Drawer::clear();
    Drawer::color({0xFF, 0xFF, 0xFF, 0xFF});

    switch(fig)
    {
    case 0:
        drawTesseract();
        break;
    case 1:
        drawTor();
        break;
    case 2:
        drawHyperSphere();
        break;
    }

    drawAxis();
    Drawer::text(font, std::string("YZ(X): ") + std::to_string((int)angles.x), {0 ,16*0});
    Drawer::text(font, std::string("XZ(Y): ") + std::to_string((int)angles.y), {0 ,16*1});
    Drawer::text(font, std::string("XY(Z): ") + std::to_string((int)angles.z), {0 ,16*2});

    Drawer::text(font, std::string("XW: ") + std::to_string((int)angles4D.x), {90 ,16*0});
    Drawer::text(font, std::string("YW: ") + std::to_string((int)angles4D.y), {90 ,16*1});
    Drawer::text(font, std::string("ZW: ") + std::to_string((int)angles4D.z), {90 ,16*2});

    if(stereogProj)
        Drawer::text(font, "Projection: stereographic", {0 ,16*3});
    else
        Drawer::text(font, "Projection: orthographic", {0 ,16*3});

    switch(fig)
    {
    case 0:
        Drawer::text(font, "Figure: tesseract", {0 ,16*4});
        break;
    case 1:
        Drawer::text(font, "Figure: tor", {0 ,16*4});
        break;
    case 2:
        Drawer::text(font, "Figure: hypersphere", {0 ,16*4});
        break;
    }
    Drawer::draw();

}

void Application::events()
{
    SDL_Event event;
    while ( SDL_PollEvent(&event) )
    {
        switch(event.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_F1:
                stereogProj = !stereogProj;
                break;
            case SDLK_F2:
                angles4D = glm::vec3(0.0f);
                break;
            case SDLK_F3:
                angles = glm::vec3(0.0f);
                break;
            case SDLK_1:
                fig = 0;
                break;
            case SDLK_2:
                fig = 1;
                break;
            case SDLK_3:
                fig = 2;
                break;
            }
            break;
        }
    }
}

void Application::input()
{
    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
    // Zoom in
    if (keyboardState[SDL_SCANCODE_Q])
        cubeSize += 1*deltaTime;
    // Zoom out
    if (keyboardState[SDL_SCANCODE_E])
        cubeSize -= 1*deltaTime;


    float speed = 1.0f;
    if (keyboardState[SDL_SCANCODE_W])
        cubePos.y += speed*deltaTime;
    if (keyboardState[SDL_SCANCODE_S])
        cubePos.y -= speed*deltaTime;
    if (keyboardState[SDL_SCANCODE_A])
        cubePos.x += speed*deltaTime;
    if (keyboardState[SDL_SCANCODE_D])
        cubePos.x -= speed*deltaTime;
    if (keyboardState[SDL_SCANCODE_SPACE])
        cubePos.z += speed*deltaTime;
    if (keyboardState[SDL_SCANCODE_C])
        cubePos.z -= speed*deltaTime;

    if (keyboardState[SDL_SCANCODE_R])
        cubePos.w += speed*deltaTime;
    if (keyboardState[SDL_SCANCODE_F])
        cubePos.w -= speed*deltaTime;



    glm::ivec2 mousePos;
    static glm::ivec2 prevMousePos = {0.0f, 0.0f};
    glm::ivec2 mouseDelta;

    SDL_GetMouseState(&mousePos.x, &mousePos.y);

    mouseDelta = prevMousePos - mousePos;
    prevMousePos = mousePos;
    if((SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) and !keyboardState[SDL_SCANCODE_LALT])
    {
        angles.y += mouseDelta.y*50*deltaTime;
        angles.z -= mouseDelta.x*50*deltaTime;
    }

    if((SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) and !keyboardState[SDL_SCANCODE_LALT])
    {
        angles.x += mouseDelta.x*50*deltaTime;
    }

    if((SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) and keyboardState[SDL_SCANCODE_LALT])
    {
        angles4D.x += mouseDelta.x*50*deltaTime;
        angles4D.y += mouseDelta.y*50*deltaTime;
    }

    if((SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) and keyboardState[SDL_SCANCODE_LALT])
    {
        angles4D.z += mouseDelta.x*50*deltaTime;
    }

}

void Application::limitFPS()
{
    static unsigned int start = SDL_GetTicks();
    if (limitingFps && ((1000 / maxFps) > (SDL_GetTicks() - start)))
    {
        SDL_Delay(1000 / maxFps - (SDL_GetTicks() - start));
    }
    start = SDL_GetTicks();
}

float Application::calcDeltaTime()
{
    static float lastTime = 0;
    static float currentTime = 0;

    if (currentTime > lastTime)
        lastTime = currentTime;
    currentTime = SDL_GetTicks();
    return ((currentTime - lastTime) / 1000.0f);
}

void Application::drawHyperSphere()
{
    if(stereogProj)
    {
        for(unsigned int i = 0; i < sphereVertices.size(); i++)
        {
            glm::vec4 point = mvp3D*stereographicProjection(modelMat4D*sphereVertices[i]);
            Drawer::point(point);
        }
    }
    else
    {
        for(unsigned int i = 0; i < sphereVertices.size(); i++)
        {
            glm::vec4 point = mvp3D*orthogonalProjection(modelMat4D*sphereVertices[i]);
            Drawer::point(point);
        }
    }


//            for(unsigned int i = 0; i < sphereEdges.size(); i++)
//            {
//                glm::vec4 one = mvp3D*(modelMat4D*sphereEdges[i].first);
//                glm::vec4 two = mvp3D*(modelMat4D*sphereEdges[i].second);
//                renderLine(renderer, one, two);
//            }
}

void Application::drawTesseract()
{
    if(stereogProj)
    {
        for(unsigned int i = 0; i < cubeEdges.size(); i++)
        {
            glm::vec4 one = mvp3D*stereographicProjection(modelMat4D*cubeEdges[i].first);
            glm::vec4 two = mvp3D*stereographicProjection(modelMat4D*cubeEdges[i].second);
            Drawer::line(one, two);
        }
    }
    else
    {
        for(unsigned int i = 0; i < cubeEdges.size(); i++)
        {
            glm::vec4 one = mvp3D*orthogonalProjection(modelMat4D*cubeEdges[i].first);
            glm::vec4 two = mvp3D*orthogonalProjection(modelMat4D*cubeEdges[i].second);
            Drawer::line(one, two);
        }
    }
}

void Application::drawTor()
{
    if(stereogProj)
    {
        for(unsigned int i = 0; i < torEdges.size(); i++)
        {
            glm::vec4 one = mvp3D*stereographicProjection(modelMat4D*torEdges[i].first);
            glm::vec4 two = mvp3D*stereographicProjection(modelMat4D*torEdges[i].second);
            Drawer::line(one, two);
        }
    }
    else
    {
        for(unsigned int i = 0; i < torEdges.size(); i++)
        {
            glm::vec4 one = mvp3D*orthogonalProjection(modelMat4D*torEdges[i].first);
            glm::vec4 two = mvp3D*orthogonalProjection(modelMat4D*torEdges[i].second);
            Drawer::line(one, two);
        }
    }
}

void Application::drawAxis()
{

    if(stereogProj)
    {
        Drawer::color({0xFF, 0, 0, 0xFF});
        Drawer::line(mvp3D*stereographicProjection(modelMat4D*vec5(0.0f, 0.0f, 0.0f, 0.0f, 1.0f))
                     , mvp3D*stereographicProjection(modelMat4D*vec5(1.0f, 0.0f, 0.0f, 0.0f, 1.0f)));
        Drawer::color({0, 0xFF, 0, 0xFF});
        Drawer::line(mvp3D*stereographicProjection(modelMat4D*vec5(0.0f, 0.0f, 0.0f, 0.0f, 1.0f))
                           , mvp3D*stereographicProjection(modelMat4D*vec5(0.0f, 1.0f, 0.0f, 0.0f, 1.0f)));
        Drawer::color({0, 0, 0xFF, 0xFF});
        Drawer::line(mvp3D*stereographicProjection(modelMat4D*vec5(0.0f, 0.0f, 0.0f, 0.0f, 1.0f))
                           , mvp3D*stereographicProjection(modelMat4D*vec5(0.0f, 0.0f, 1.0f, 0.0f, 1.0f)));
        Drawer::color({0xFF, 0, 0xFF, 0xFF});
        Drawer::line(mvp3D*stereographicProjection(modelMat4D*vec5(0.0f, 0.0f, 0.0f, 0.0f, 1.0f))
                           , mvp3D*stereographicProjection(modelMat4D*vec5(0.0f, 0.0f, 0.0f, 1.0f, 1.0f)));
    }
    else
    {
        Drawer::color({0xFF, 0, 0, 0xFF});
        Drawer::line(mvp3D*orthogonalProjection(modelMat4D*vec5(0.0f, 0.0f, 0.0f, 0.0f, 1.0f))
                     , mvp3D*orthogonalProjection(modelMat4D*vec5(1.0f, 0.0f, 0.0f, 0.0f, 1.0f)));
        Drawer::color({0, 0xFF, 0, 0xFF});
        Drawer::line(mvp3D*orthogonalProjection(modelMat4D*vec5(0.0f, 0.0f, 0.0f, 0.0f, 1.0f))
                           , mvp3D*orthogonalProjection(modelMat4D*vec5(0.0f, 1.0f, 0.0f, 0.0f, 1.0f)));
        Drawer::color({0, 0, 0xFF, 0xFF});
        Drawer::line(mvp3D*orthogonalProjection(modelMat4D*vec5(0.0f, 0.0f, 0.0f, 0.0f, 1.0f))
                           , mvp3D*orthogonalProjection(modelMat4D*vec5(0.0f, 0.0f, 1.0f, 0.0f, 1.0f)));
        Drawer::color({0xFF, 0, 0xFF, 0xFF});
        Drawer::line(mvp3D*orthogonalProjection(modelMat4D*vec5(0.0f, 0.0f, 0.0f, 0.0f, 1.0f))
                           , mvp3D*orthogonalProjection(modelMat4D*vec5(0.0f, 0.0f, 0.0f, 1.0f, 1.0f)));
    }
}

Application::Application():
    limitingFps(true)
  , running(true)
  , angles(0.0f)
  , angles4D(0.0f)
  , cubeSize(1.0f)
  , deltaTime(0.0f)
  , stereogProj(false)
  , fig(0)
{
}

void Application::execute()
{
    initialize();
    while(running)
    {
        deltaTime = calcDeltaTime();
        input();
        events();
        update();
        draw();
        limitFPS();
    }
}
