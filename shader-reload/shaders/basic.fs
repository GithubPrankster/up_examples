#version 460 core
out vec4 frag;

uniform float time;
uniform vec2 res;

void main()
{
    frag = vec4(abs(cos(time * 0.002f)), abs(sin(time * 0.003f) + cos(time * 0.0015f)), abs(sin(time * 0.004f)), 1.0);
}