#version 330 core

// vertex attribs (input)
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec3 vertexColor;
layout (location = 3) in vec2 vertexTexCoords;
layout (location = 4) in float textureId;
layout (location = 5) in mat4 matrixModel;
layout (location = 9) in vec4 materialAmbientColor;
layout (location = 10) in vec4 materialDiffuseColor;

// uniforms
uniform mat4 u_matrixView;
uniform mat4 u_matrixProjection;


// varyings (output)
out vec3 v_normal;
out vec4 v_materialAmbientColor;
out vec4 v_materialDiffuseColor;


void main()
{
    // Transform the normal vector using the modelview matrix
    v_normal = mat3(matrixModel) * vertexNormal;
    
    // Offset each vertex position per instance
    gl_Position = u_matrixProjection * u_matrixView * matrixModel * vec4(vertexPosition, 1.0);

    v_materialAmbientColor = materialAmbientColor;
    v_materialDiffuseColor = materialDiffuseColor;
}

