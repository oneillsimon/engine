#version 330 core

in vec3 Normal;
in vec3 FragPosition;
in vec2 TexCoords;

out vec4 frag_colour;

uniform vec3 object_colour;
uniform vec3 light_colour;
//uniform vec3 light_position;
uniform vec3 view_position;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct SpotLight {
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float cut_off;
    float outer_cut_off;
};

uniform Material material;
uniform SpotLight spot_light;

struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform DirectionalLight directional_light;

#define NR_POINT_LIGHTS 4
uniform PointLight point_lights[NR_POINT_LIGHTS];

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 view_direction);
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 frag_pos, vec3 view_direction);
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 frag_pos, vec3 view_direction);

void main() {
    vec3 norm = normalize(Normal);
    vec3 view_direction = normalize(view_position - FragPosition);

    // Phase 1: Directional lighting.
    vec3 result = CalculateDirectionalLight(directional_light, norm, view_direction);

    // Phase 2: Point lights.
    for (int i = 0; i < NR_POINT_LIGHTS; i++) {
        result += CalculatePointLight(point_lights[i], norm, FragPosition, view_direction);
    }

    // Phase 3: Spot light
    result += CalculateSpotLight(spot_light, norm, FragPosition, view_direction);

    frag_colour = vec4(result, 1.0);
}

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 view_direction) {
    vec3 light_direction = normalize(-light.direction);

    // Diffuse shading.
    float diff = max(dot(normal, light_direction), 0.0);

    // Specular shading.
    vec3 reflect_direction = reflect(-light_direction, normal);
    float spec = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);

    // Combine results.
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;
    return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 frag_pos, vec3 view_direction) {
    vec3 light_direction = normalize(light.position - frag_pos);

    // Diffuse shading.
    float diff = max(dot(normal, light_direction), 0.0);

    // Specular shading.
    vec3 reflect_direction = reflect(-light_direction, normal);
    float spec = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);

    // Attenuation.
    float distance = length(light.position - frag_pos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // Combine results.
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 frag_pos, vec3 view_direction) {
    vec3 light_direction = normalize(light.position - FragPosition);

    // Diffuse shading.
    float diff = max(dot(normal, light_direction), 0.0);

    // Specular shading.
    vec3 reflect_direction = reflect(-light_direction, normal);
    float spec = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);

    // Combine results.
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

    // Check to see if fragment is inside the spotlight cone.
    float theta = dot(light_direction,-(light.direction));
    float epsilon = light.cut_off - light.outer_cut_off;
    float intensity = clamp((theta - light.outer_cut_off) / epsilon, 0.0, 1.0);
    diffuse *= intensity;
    specular *= intensity;

    // Attenuation/
    float distance = length(light.position - FragPosition);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}