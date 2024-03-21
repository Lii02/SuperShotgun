vec3 GetForwardLightingCalculation(vec3 ambient, vec3 fragpos, vec3 N, float specular, float shininess, vec3 view_dir) {
	vec3 calc = ambient;
	for(int i = 0; i < MAX_LIGHTS; i++) {
		light l = lights[i];
		if(l.type == POINT_LIGHT) {
			float distance = length(l.position - fragpos);
			if(distance < l.radius) {
				vec3 L = normalize(l.position - fragpos);
				float attenuation = CalculateLightAttenuation(l, distance);
				float diff = max(dot(N, L), 0.0);
				vec3 diffuse = diff * l.color * l.intensity;
				vec3 reflect_direction = reflect(-L, N);
				float spec = pow(max(dot(view_dir, reflect_direction), 0.0), shininess);
				vec3 specular = specular * l.color * spec;
				diffuse *= attenuation;
				specular *= attenuation;
				calc += diffuse + specular;
			}
		} else if(l.type == DIRECTIONAL_LIGHT) {
			vec3 L = normalize(-l.direction);
			float diff = max(dot(N, L), 0.0);
			vec3 diffuse = diff * l.color * l.intensity;
			vec3 halfway = normalize(L + view_dir);
			vec3 reflect_direction = reflect(-L, N);
			float spec = pow(max(dot(N, halfway), 0.0), shininess);
			vec3 specular = specular * l.color * spec;
			calc += diffuse + specular;
		}
	}
	return calc;
}