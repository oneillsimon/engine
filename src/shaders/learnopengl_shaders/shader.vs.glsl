#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 colour;
layout (location = 2) in vec2 t_coords;

out vec4 vertex_colour;
out vec2 texture_coords;

uniform float x_offset;
uniform mat4 transform;

void main() {
    vertex_colour = vec4(colour, 1.0);
    texture_coords = t_coords;
    gl_Position = transform * vec4(position.x + x_offset, position.y, position.z, 1.0);
}
