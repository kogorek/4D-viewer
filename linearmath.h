#ifndef LINEARMATH_H
#define LINEARMATH_H

#include <ostream>
#include <glm/glm.hpp>


struct vec5
{
    float x, y, z, w, v;

    vec5():
        x(0.0f)
      , y(0.0f)
      , z(0.0f)
      , w(0.0f)
      , v(0.0f)
    {}

    vec5(float num):
        x(num)
      , y(num)
      , z(num)
      , w(num)
      , v(num)
    {}

    vec5(float x, float y, float z, float w, float v):
        x(x)
      , y(y)
      , z(z)
      , w(w)
      , v(v)
    {}

//    operator glm::vec4() const
//    {
//        return glm::vec4(x, y, z, v);
//    }
};

struct mat5
{
    float a, b, c, d, e;
    float f, g, h, i, j;
    float k, l, m, n, o;
    float p, q, r, s, t;
    float u, v, w, x, y;

    mat5():
        a(0.0f), b(0.0f), c(0.0f), d(0.0f), e(0.0f)
      , f(0.0f), g(0.0f), h(0.0f), i(0.0f), j(0.0f)
      , k(0.0f), l(0.0f), m(0.0f), n(0.0f), o(0.0f)
      , p(0.0f), q(0.0f), r(0.0f), s(0.0f), t(0.0f)
      , u(0.0f), v(0.0f), w(0.0f), x(0.0f), y(0.0f)
    {}

    mat5(float num):
        a(num), b(num), c(num), d(num), e(num)
      , f(num), g(num), h(num), i(num), j(num)
      , k(num), l(num), m(num), n(num), o(num)
      , p(num), q(num), r(num), s(num), t(num)
      , u(num), v(num), w(num), x(num), y(num)
    {}

    mat5(float a, float b, float c, float d, float e,
         float f, float g, float h, float i, float j,
         float k, float l, float m, float n, float o,
         float p, float q, float r, float s, float t,
         float u, float v, float w, float x, float y):
        a(a), b(b), c(c), d(d), e(e)
      , f(f), g(g), h(h), i(i), j(j)
      , k(k), l(l), m(m), n(n), o(o)
      , p(p), q(q), r(r), s(s), t(t)
      , u(u), v(v), w(w), x(x), y(y)
    {}
};

glm::vec4 stereographicProjection(const vec5 &vec, const float ligthWPos = 2.0f);
glm::vec4 orthogonalProjection(const vec5 &vec);

mat5 operator*(const mat5 &l, const mat5 &r);
vec5 operator*(const mat5 &l, const vec5 &r);
std::ostream &operator<< (std::ostream &s, const mat5 &mat);
std::ostream &operator<< (std::ostream &s, const vec5 &vec);

std::ostream &operator<< (std::ostream &s, const glm::vec4 &vec);
std::ostream &operator<< (std::ostream &s, const glm::vec3 &vec);
std::ostream &operator <<(std::ostream &s, const glm::mat4 &mat);

//glm::vec4 &operator=(glm::vec4 &v4, const vec5 &v5);


//glm::vec4 &operator=(glm::vec4 &v4, const vec5 &v5)
//{
//    return {v5.x, v5.y, v5.z, v5.w};
//}


mat5 scale(glm::vec4 axis);
mat5 translate(const glm::vec4 &axis);

mat5 rotateZW4D(float degrees);
mat5 rotateYW4D(float degrees);
mat5 rotateXW4D(float degrees);

mat5 rotateXZ4D(float degrees);
mat5 rotateYZ4D(float degrees);
mat5 rotateXY4D(float degrees);

#endif // LINEARMATH_H
