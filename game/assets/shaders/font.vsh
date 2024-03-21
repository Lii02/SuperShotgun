#version 440

in vec4 vertex;
out vec2 texture_coords;

uniform mat4 projection;
uniform mat4 transform;

void main() {
	gl_Position = projection * transform * vec4(vertex.x, -vertex.y, 0.0, 1.0);
	texture_coords = vertex.zw;
}