#version 440

in vec2 texture_coords;

out vec4 out_color;
uniform sampler2D color_texture;

void main() {
	vec4 texcolor = texture(color_texture, texture_coords);
    out_color = texcolor;
}