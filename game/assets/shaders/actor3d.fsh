#version 440

out vec4 out_color;
in vec2 texture_coords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;
uniform sampler2D gSpecular;
uniform sampler2D gDepth;

uniform vec3 view_position;
@include lighting.glsl
@include forward.glsl

void main() {
	vec3 fragpos = texture(gPosition, texture_coords).rgb;
    vec3 N = texture(gNormal, texture_coords).rgb;
	vec3 diffuse = texture(gAlbedo, texture_coords).rgb;
	float specular = texture(gSpecular, texture_coords).r;
	vec3 depth = texture(gDepth, texture_coords).rgb;
	vec3 view_dir = normalize(view_position - fragpos);
	vec3 ambient = diffuse * 0.25f;
	vec3 lighting = GetForwardLightingCalculation(ambient, fragpos, N, specular, 32, view_dir);
	out_color = vec4(lighting * diffuse, 1);
}