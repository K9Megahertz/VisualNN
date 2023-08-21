#version 330
// vertex attribs (input)
in vec3 vertexPosition;
in vec3 vertexNormal;
in vec3 vertexColor;
in vec2 vertexTexCoords;
in float textureId;

// uniforms
uniform mat4 u_matrixModel;
uniform mat4 u_matrixView;
uniform mat4 u_matrixProjection;

// varyings (output)
out vec3 v_normal;

void main()
{
    // offset each vertex position per instance    
    v_normal = vertexNormal;    
    gl_Position = u_matrixProjection * u_matrixView * u_matrixModel * vec4(vertexPosition, 1.0);    
}