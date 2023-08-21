#version 330 core

uniform vec4 u_lightPosition;       // should be in the eye space
uniform vec4 u_lightAmbientColor;        // light ambient color
uniform vec4 u_lightDiffuseColor;        // light diffuse color
uniform vec4 u_lightSpecularColor;       // light specular color
uniform vec4 u_materialAmbientColor;     // material ambient color
uniform vec4 u_materialDiffuseColor;     // material diffuse color
uniform vec4 u_materialSpecularColor;    // material specular color
uniform float u_materialShininess;  // material specular shininess

in vec3 v_normal;

out vec4 frag_color;

void main() {    
    vec3 lightDir = normalize(vec3(u_lightPosition - vec4(gl_FragCoord.xyzw)));
    vec3 normal = normalize(v_normal);
    vec3 reflectDir = reflect(-lightDir, normal);

    vec4 ambient = u_lightAmbientColor * u_materialAmbientColor;
    vec4 diffuse = u_lightDiffuseColor * u_materialDiffuseColor * max(dot(lightDir, normal), 0.0);
    vec4 specular = u_lightSpecularColor * u_materialSpecularColor * pow(max(dot(reflectDir, normalize(-vec3(gl_FragCoord.xy, 0))), 0.0), u_materialShininess);

    
    frag_color = ambient + diffuse + specular;
    //frag_color = vec4(1.0, 0.0, 0.0, 1.0);
    
}