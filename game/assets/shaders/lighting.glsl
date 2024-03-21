#define POINT_LIGHT 0
#define SPOTLIGHT 1
#define DIRECTIONAL_LIGHT 2

struct light {
	vec3 color;
	vec3 position;
	float intensity;
	int type;
	vec3 direction;
	float linear;
	float quadratic;
	float cutoff;
	float radius;
};

#define LIGHT_CONSTANT 1.0

#define MAX_LIGHTS 50

uniform light lights[MAX_LIGHTS];

float CalculateLightAttenuation(light l, float distance) {
	return LIGHT_CONSTANT / (LIGHT_CONSTANT + l.linear * distance + l.quadratic * (distance * distance));
}