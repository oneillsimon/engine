#version 430 core

subroutine vec3 shadeModelType(vec4 position, vec3 normal);
subroutine uniform shadeModelType shadeModel;

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 FrontColor;
out vec3 BackColor;

struct LightInfo {
    vec4 Position; // Light position in eye coords.
    vec3 La;       // Ambient light intensity.
    vec3 Ld;       // Diffuse light intensity.
    vec3 Ls;       // Specular light intensity.
};
uniform LightInfo Light;

struct MaterialInfo {
    vec3 Ka;         // Ambient reflectivity.
    vec3 Kd;         // Diffuse reflectivity.
    vec3 Ks;         // Specular reflectivity.
    float Shininess; // Specular shininess factor.
};
uniform MaterialInfo Material;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVP;

void getEyeSpace(out vec3 normal, out vec4 position) {
    normal = normalize(NormalMatrix * VertexNormal);
    position = ModelViewMatrix * vec4(VertexPosition, 1.0f);
}

subroutine(shadeModelType)
vec3 phongModel(vec4 position, vec3 normal) {
    vec3 s = normalize(vec3(Light.Position - position));
    vec3 v = normalize(-position.xyz);
    vec3 r = reflect(-s, normal);
    float sDotN = max(dot(s, normal), 0.0);

    vec3 ambient = Light.La * Material.Ka;
    vec3 diffuse = Light.Ld * Material.Kd * sDotN;
    vec3 specular = vec3(0.0);

    if (sDotN > 0.0) {
        specular = Light.Ls * Material.Ks * pow(max(dot(r, v), 0.0), Material.Shininess);
    }

    return ambient + diffuse + specular;
}

subroutine(shadeModelType)
vec3 diffuseOnly(vec4 position, vec3 normal) {
    vec3 s = normalize(vec3(Light.Position - position));
    return Light.Ld * Material.Kd * max(dot(s, normal), 0.0);
}

void main() {
    vec3 eyeNormal;
    vec4 eyePosition;

    // Get the position and normal in eye space.
    getEyeSpace(eyeNormal, eyePosition);

    // Evalulate the lighting equation.
    FrontColor = shadeModel(eyePosition, eyeNormal);
    BackColor = shadeModel(eyePosition, -eyeNormal);

    gl_Position = MVP * vec4(VertexPosition, 1.0);
}



