#version 440

out vec4 gPosition;
out vec4 gNormal;
out vec4 gAlbedo;
out vec4 gSpecular;
out vec4 gDepth;

in vec3 fragpos;
in vec2 textures;
in vec3 normals;
in mat3 TBN;

@include material.glsl

void main() {
	gPosition = vec4(fragpos, 1);
	if(mat.nmap.uses_map) {
		gNormal = vec4(GetNormalMap(mat.nmap, textures, TBN), 1);
	} else {
		gNormal = vec4(normalize(normals), 1);
	}
	gAlbedo = vec4(GetMaterialColor(mat.values[DIFFUSE_UNIT], textures), 1);
	gSpecular = vec4(vec3(GetMaterialValue(mat.values[SPECULAR_UNIT], textures)), 1);
	gDepth = vec4(vec3(gl_FragCoord.z), 1);
}