#version 330
// vertex attribs (input)
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec3 vertexColor;
layout (location = 3) in vec2 vertexTexCoord;
layout (location = 4) in float textureId;

// uniforms
uniform mat4 u_matrixModel;
uniform mat4 u_matrixView;
uniform mat4 u_matrixProjection;


out vec3 v_normal;
out vec2 v_texCoord;
out vec4 v_materialAmbientColor;
out vec4 v_materialDiffuseColor;

void main()
{
    // offset each vertex position per instance    
    v_normal = mat3(u_matrixModel) * vertexNormal;      
    v_texCoord = vertexTexCoord;

    gl_Position = u_matrixProjection * u_matrixView * u_matrixModel * vec4(vertexPosition, 1.0);    
    //gl_Position = u_matrixProjection * u_matrixView * vec4(vertexPosition, 1.0);    
}