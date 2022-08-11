#version 450 core
layout (location = 0) in vec2 in_coordinates;
layout (location = 1) in vec2 in_texture_coordinates;

out vec2 fragment_texture_coordinates;

uniform vec4 object_offset;

void main() {
   gl_Position = vec4(in_coordinates.x + object_offset.x, in_coordinates.y + object_offset.y, 0.0, 1.0);
   fragment_texture_coordinates = in_texture_coordinates;
}
