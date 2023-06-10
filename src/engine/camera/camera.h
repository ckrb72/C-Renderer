#pragma once
#include <linmath.h>

//Need to look into what one would need for a camera. Don't really know at this point
typedef struct ortho_camera
{
    mat4x4 projection;
    mat4x4 view;
}Ortho_Camera;