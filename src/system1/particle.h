#ifndef _PARTICLE_HPP_
#define _PARTICLE_HPP_
// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

#include "src/glm/vec3.hpp"
#include "src/glm/vec4.hpp"
#include "src/glm/mat4x4.hpp"
#include "src/glm/gtc/matrix_transform.hpp"
#include "src/glm/gtc/type_ptr.hpp"
#include"src/gl_framework.hpp"
#include"src/shader_util.hpp"
#include<time.h>
class Particle{
    public:
    glm::vec2 position,velocity;
    int timeOrigin;
    int timeTotal = 3;
    int n = 200;
    Particle(float angle,int t);
};

#endif