#version 450


layout(location = 0) out vec4 outColor;
layout(location = 0) in vec3 normal;
layout(location = 1) in vec2 fragTexCoord;


layout(binding = 1) uniform sampler2D texSampler;

void main() 
{
    const vec3 L = vec3(0, sin(5.4), cos(5.4));
    float ndl = max(dot(normal, L), 0.2);

    outColor = vec4(texture(texSampler, fragTexCoord).xyz * ndl, 1);
}