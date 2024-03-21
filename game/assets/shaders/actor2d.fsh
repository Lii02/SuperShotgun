#version 440

out vec4 out_color;
in vec2 textures;

uniform sampler2D texture_sampler;

void main() {
	vec4 texture_color = texture(texture_sampler, textures);
	out_color = texture_color;
}