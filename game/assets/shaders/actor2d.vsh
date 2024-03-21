#version 440

in vec2 position;
in vec2 tex;
out vec2 textures;

uniform mat4 projection;
uniform mat4 transform;
uniform mat4 view;

void main() {
	gl_Position = projection * view * transform * vec4(position, 0, 1);
	textures = tex;
}