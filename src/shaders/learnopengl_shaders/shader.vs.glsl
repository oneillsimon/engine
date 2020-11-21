//    const char* vertex_shader_source = "#version 330 core\n"
//                                     "layout (location = 0) in vec3 aPos;\n"
//                                     "layout (location = 1) in vec3 aColor;\n"
//                                     "\n"
//                                     "out vec3 vertexColor;\n"
//                                     "void main()\n"
//                                     "{\n"
//                                     "    vertexColor = aColor;\n"
//                                     "    gl_Position = vec4(aPos, 1.0);\n"
//                                     "}\0";

#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 colour;

out vec4 vertex_colour;

uniform float x_offset;

void main() {
    vertex_colour = vec4(colour, 1.0);
    gl_Position = vec4(position.x + x_offset, position.y, position.z, 1.0);
}

// I've updated this file