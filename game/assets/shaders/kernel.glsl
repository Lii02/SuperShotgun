vec3 DoKernelCalculation(sampler2D texsampler, vec2 texture_coords, float offset, in float kernel[9]) {
    vec2 offsets[9] = {
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right    
    };

    vec3 samples[9];
    for(int i = 0; i < 9; i++) {
        samples[i] = vec3(texture(texsampler, texture_coords.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++) {
        col += samples[i] * kernel[i];
    }
    return col;
}