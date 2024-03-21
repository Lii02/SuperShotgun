#version 440

out vec4 out_color;
in vec2 textures;

uniform vec3 tint;
uniform sampler2D texture_sampler;

void main() {
	vec4 texcolor = texture(texture_sampler, textures);
	out_color = texcolor;
}