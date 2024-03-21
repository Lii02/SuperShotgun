#define TYPE_COLOR 0
#define TYPE_TEXTURE 1
#define TYPE_FLOAT 2

#define DIFFUSE_UNIT 0
#define SPECULAR_UNIT 1
#define NORMAL_UNIT 4

struct material_value {
	int type;
	vec3 color;
	sampler2D texture_sampler;
};

struct normal_map {
	bool uses_map;
	sampler2D texture_sampler;
};

struct material {
	material_value values[4];
	normal_map nmap;
};

float GetMaterialValue(material_value val, vec2 textures) {
	if (val.type == TYPE_COLOR) {
		return val.color.r;
	} else if (val.type == TYPE_TEXTURE) {
		return texture(val.texture_sampler, textures).r;
	} if (val.type == TYPE_FLOAT) {
		return val.color.r;
	}
}

vec3 GetMaterialColor(material_value val, vec2 textures) {
	if (val.type == TYPE_COLOR) {
		return val.color;
	} else if (val.type == TYPE_TEXTURE) {
		return texture(val.texture_sampler, textures).rgb;
	}  if (val.type == TYPE_FLOAT) {
		return vec3(val.color.r);
	}
}

vec3 GetNormalMap(normal_map nmap, vec2 textures, mat3 TBN) {
	vec3 normal = texture(nmap.texture_sampler, textures).xyz;
	normal = 2.0 * normal - vec3(1.0, 1.0, 1.0);
	return TBN * normal;
}

uniform material mat;