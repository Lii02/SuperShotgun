#version 440

in vec3 position;
in vec2 tex;
in vec3 nor;
in vec3 tangent;
out mat3 TBN;

out vec3 fragpos;
out vec2 textures;
out vec3 normals;

uniform mat4 projection;
uniform mat4 transform;
uniform mat4 view;

void main() {
	vec4 world_position = transform * vec4(position, 1.0);
	fragpos = world_position.xyz;
	gl_Position = projection * view * world_position;
	textures = tex;
	normals = mat3(transpose(inverse(transform))) * nor;
	vec3 T = normalize(tangent);
	vec3 N = normalize(normals);
	T = normalize(T - dot(T, N) * N);
	vec3 B = cross(N, T);
	TBN = mat3(T, B, N);
}