#version 330 core

in vec4 vertex_colour;
in vec2 texture_coords;

out vec4 frag_colour;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    frag_colour = mix(texture(texture1, texture_coords), texture(texture2, vec2(-texture_coords.x, texture_coords.y)), 0.2);
//    frag_colour = mix(texture(texture1, texture_coords), texture(texture2, texture_coords), 0.2) * vertex_colour;
}