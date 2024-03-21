#version 440

in vec2 texture_coords;

out vec4 out_color;
uniform sampler2D color_texture;

uniform float exposure;

void main() {
	vec3 texcolor = texture(color_texture, texture_coords).rgb;
	vec3 mapped = vec3(1.0) - exp(-texcolor * exposure);;
    out_color = vec4(mapped, 1);
}