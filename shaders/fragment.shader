#version 450 core
in vec2 fragment_texture_coordinates;

out vec4 fragment_color;

uniform sampler2D out_texture;

void main() {
	fragment_color = texture(out_texture, fragment_texture_coordinates);
	//fragment_color = vec4(1.0, .0, .0, 1.0);
}
