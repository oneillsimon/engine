#version 330 core
out vec4 frag_colour;

uniform vec3 light_colour;

void main() {
    frag_colour = vec4(light_colour, 1.0);
}