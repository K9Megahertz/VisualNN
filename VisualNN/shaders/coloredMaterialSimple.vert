#version 330
// vertex attribs (input)
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec3 vertexColor;
layout (location = 3) in vec2 vertexTexCoords;
layout (location = 4) in float textureId;

// uniforms
//uniform mat4 u_matrixModel;
uniform mat4 u_matrixView;
uniform mat4 u_matrixProjection;

out vec3 v_Color;

void main()
{
    // offset each vertex position per instance    
    v_Color = vertexColor;    
    //gl_Position = u_matrixProjection * u_matrixView * u_matrixModel * vec4(vertexPosition, 1.0);    
    gl_Position = u_matrixProjection * u_matrixView * vec4(vertexPosition, 1.0);    
}