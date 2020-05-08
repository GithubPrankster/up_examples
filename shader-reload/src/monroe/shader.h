#pragma once

unsigned int me_shader_create(const char* vsrc, const char* fsrc);
void me_shader_float(const unsigned int shr, const char* name, const float var);
void me_shader_vec2(const unsigned int shr, const char* name, const float *var);