#version 330
// vertex attribs (input)
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec3 vertexColor;
layout (location = 3) in vec2 vertexTexCoords;
layout (location = 4) in float textureId;
layout (location = 5) in mat4 matrixModel;

// uniforms

uniform mat4 u_matrixView;
uniform mat4 u_matrixProjection;

// varyings (output)
out vec3 v_normal;

void main()
{
    // offset each vertex position per instance    
    v_normal = vertexNormal;    
    gl_Position = u_matrixProjection * u_matrixView * matrixModel * vec4(vertexPosition, 1.0);    
}