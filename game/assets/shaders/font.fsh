#version 440

out vec4 out_color;
in vec2 texture_coords;

uniform sampler2D text;
uniform vec4 text_color;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texture_coords).r);
    out_color = text_color * sampled;
}