
#version 330 core

out vec4 FragColor;
in vec2 uv;

uniform sampler2D texture0;

void main()
{
    // texture(texture0, uv);
    FragColor = vec4(.2, .2, .2, 1); 
}