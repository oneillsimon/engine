#version 330 core

layout (location = 0) in vec3 position;
//layout (location = 1) in vec3 colour;
layout (location = 1) in vec2 t_coords;

out vec4 vertex_colour;
out vec2 texture_coords;

uniform float x_offset;
uniform mat4 transform;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    vertex_colour = vec4(1.0, 1.0, 1.0, 1.0);
    texture_coords = t_coords;
    gl_Position = projection * view * model * vec4(position, 1.0);
//    gl_Position = transform * vec4(position.x + x_offset, position.y, position.z, 1.0);
}
