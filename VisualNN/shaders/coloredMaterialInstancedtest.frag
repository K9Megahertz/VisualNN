#version 330 core

uniform vec4 u_lightPosition;       // should be in the eye space

uniform vec4 u_lightAmbientColor;        // light ambient color
uniform vec4 u_lightDiffuseColor;        // light diffuse color
uniform vec4 u_lightSpecularColor;       // light specular color

in vec3 v_normal;
in vec4 v_materialAmbientColor;
in vec4 v_materialDiffuseColor;

out vec4 frag_color;

void main() {
    vec3 lightDir = normalize(vec3(u_lightPosition));
    vec3 normal = normalize(v_normal);
    vec3 reflectDir = reflect(-lightDir, normal);


    vec4 ambient = u_lightAmbientColor * v_materialAmbientColor;

    // Calculate the diffuse component by multiplying the light color, material color, and the dot product of the light direction and the normal
    vec4 diffuse = u_lightDiffuseColor * v_materialDiffuseColor * max(dot(lightDir, normal), 0.0);

    vec4 specular = u_lightSpecularColor * v_materialDiffuseColor * pow(max(dot(reflectDir, normalize(-vec3(gl_FragCoord.xy, 0))), 0.0), 32.0);

    // Combine the ambient and diffuse components to get the final fragment color
    frag_color = ambient + diffuse + specular;
}