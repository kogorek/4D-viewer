#include "linearmath.h"

mat5 operator*(const mat5 &l, const mat5 &r)
{
    const float *lMat = &l.a;
    const float *rMat = &r.a;
    mat5 mat;
    float *newMat = &mat.a;
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 5; ++j)
            for(int k = 0; k < 5; ++k)
            {
                newMat[i*5+j] += lMat[i*5+k] * rMat[k*5+j];
            }
    return mat;
}

vec5 operator*(const mat5 &l, const vec5 &r)
{
    const float *lMat = &l.a;
    const float *rVec = &r.x;
    vec5 vec;
    float *newVec = &vec.x;
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 5; ++j)
        {
            newVec[i] += lMat[i*5+j] * rVec[j];
        }
    return vec;
}

std::ostream &operator<<(std::ostream &s, const mat5 &mat)
{
    const float *matP = &mat.a;
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            s << matP[i*5+j] << "; ";
        }
        s << '\n';
    }
    return s;
}

std::ostream &operator<<(std::ostream &s, const vec5 &vec)
{
    s << "(" << vec.x << "; " <<
                vec.y << "; " <<
                vec.z << "; " <<
                vec.w << "; " <<
                vec.v << ")";
    return s;
}

mat5 scale(glm::vec4 axis)
{
    return mat5{axis.x, 0.0f  , 0.0f  , 0.0f  , 0.0f,
                0.0f  , axis.y, 0.0f  , 0.0f  , 0.0f,
                0.0f  , 0.0f  , axis.z, 0.0f  , 0.0f,
                0.0f  , 0.0f  , 0.0f  , axis.w, 0.0f,
                0.0f  , 0.0f  , 0.0f  , 0.0f  , 1.0f};
}

mat5 rotateZW4D(float degrees)
{
    return mat5{1.0f, 0.0f, 0.0f                            , 0.0f                            , 0,
                0.0f, 1.0f, 0.0f                            , 0.0f                            , 0,
                0.0f, 0.0f, (float)cos(degrees*M_PI/180.0f) , (float)-sin(degrees*M_PI/180.0f), 0,
                0.0f, 0.0f, (float)-sin(degrees*M_PI/180.0f), (float)cos(degrees*M_PI/180.0f) , 0,
                0   , 0   , 0                               , 0                               , 1};
}

mat5 rotateYW4D(float degrees)
{
    return mat5{1.0f, 0.0f                            , 0.0f, 0.0f                            , 0.0f,
                0.0f, (float)cos(degrees*M_PI/180.0f) , 0.0f, (float)-sin(degrees*M_PI/180.0f), 0.0f,
                0.0f, 0.0f                            , 1.0f, 0.0f                            , 0.0f,
                0.0f, (float)-sin(degrees*M_PI/180.0f), 0.0f, (float)cos(degrees*M_PI/180.0f) , 0.0f,
                0.0f, 0.0f                            , 0.0f, 0.0f                            , 1.0f};
}

mat5 rotateXW4D(float degrees)
{
    return mat5{(float)cos(degrees*M_PI/180.0f) , 0.0f, 0.0f, (float)sin(degrees*M_PI/180.0f), 0.0f,
                0.0f                            , 1.0f, 0.0f, 0.0f                           , 0.0f,
                0.0f                            , 0.0f, 1.0f, 0.0f                           , 0.0f,
                (float)-sin(degrees*M_PI/180.0f), 0.0f, 0.0f, (float)cos(degrees*M_PI/180.0f), 0.0f,
                0.0f                            , 0.0f, 0.0f, 0.0f                           , 1.0f};
}

mat5 rotateXZ4D(float degrees)
{
    return mat5{(float)cos(degrees*M_PI/180.0f) , 0.0f, (float)-sin(degrees*M_PI/180.0f), 0.0f, 0.0f,
                0.0f                            , 1.0f, 0.0f                           , 0.0f, 0.0f,
                (float)sin(degrees*M_PI/180.0f), 0.0f, (float)cos(degrees*M_PI/180.0f), 0.0f, 0.0f,
                0.0f                            , 0.0f, 0.0f                           , 1.0f, 0.0f,
                0.0f                            , 0.0f, 0.0f                           , 0.0f, 1.0f};
}

mat5 rotateYZ4D(float degrees)
{
    return mat5{1.0f, 0.0f                            , 0.0f                           , 0.0f, 0.0f,
                0.0f, (float)cos(degrees*M_PI/180.0f) , (float)sin(degrees*M_PI/180.0f), 0.0f, 0.0f,
                0.0f, (float)-sin(degrees*M_PI/180.0f), (float)cos(degrees*M_PI/180.0f), 0.0f, 0.0f,
                0.0f, 0.0f                            , 0.0f                           , 1.0f, 0.0f,
                0.0f, 0.0f                            , 0.0f                           , 0.0f, 1.0f};
}

mat5 rotateXY4D(float degrees)
{
    return mat5{(float)cos(degrees*M_PI/180.0f) , (float)sin(degrees*M_PI/180.0f), 0.0f, 0.0f, 0.0f,
                (float)-sin(degrees*M_PI/180.0f), (float)cos(degrees*M_PI/180.0f), 0.0f, 0.0f, 0.0f,
                0.0f                            , 0.0f                           , 1.0f, 0.0f, 0.0f,
                0.0f                            , 0.0f                           , 0.0f, 1.0f, 0.0f,
                0.0f                            , 0.0f                           , 0.0f, 0.0f, 1.0f};
}

mat5 translate(const glm::vec4 &axis)
{
    return mat5{1, 0, 0, 0, axis.x,
                0, 1, 0, 0, axis.y,
                0, 0, 1, 0, axis.z,
                0, 0, 0, 1, axis.w,
                0, 0, 0, 0, 1};
}


std::ostream &operator<<(std::ostream &s, const glm::vec4 &vec)
{
    s << "(" << vec.x << "; " << vec.y << "; " << vec.z << "; " << vec.w << ")";
    return s;
}

std::ostream &operator<<(std::ostream &s, const glm::vec3 &vec)
{
    s << "(" << vec.x << "; " << vec.y << "; " << vec.z << ")";
    return s;
}

std::ostream &operator <<(std::ostream &s, const glm::mat4 &mat)
{
    for(int y = 0; y < 4; y++)
    {
        for(int x = 0; x < 4; x++)
        {

            s << mat[x][y] << "; ";
        }
        s << "\n";
    }
    return s;
}

glm::vec4 stereographicProjection(const vec5 &vec, const float ligthWPos)
{
    glm::mat3x4 stereographicProjection = {1/(ligthWPos-vec.w), 0.0f, 0.0f, 0.0f,
                                           0.0f, 1/(ligthWPos-vec.w), 0.0f, 0.0f,
                                           0.0f, 0.0f, 1/(ligthWPos-vec.w), 0.0f};
    glm::vec3 result = glm::vec4(vec.x, vec.y, vec.z, vec.w)*stereographicProjection;
    return glm::vec4(result.x, result.y, result.z, vec.v);
}

glm::vec4 orthogonalProjection(const vec5 &vec)
{
    return glm::vec4(vec.x, vec.y, vec.z, vec.v);
}
