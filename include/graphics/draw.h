#pragma once

struct Geometry;
struct Shader;
struct Framebuffer;
struct Texture;

void s0_draw(const Framebuffer &f, const Shader &s, const Geometry &g);

void clearFramebuffer(const Framebuffer &f);

void setUniform(const Shader &s, int location, float value);

void setUniform(const Shader &s, int location, int value);

void setUniform(const Shader &s, int location, const Texture &value, unsigned slot);

namespace _internal
{
void t_setUniform(const Shader &s, int &loc_io, int & tex_io, float val);
void t_setUniform(const Shader &s, int &loc_io, int & tex_io, int val);
void t_setUniform(const Shader &s, int &loc_io, int & tex_io,const Texture &val);
}

template<typename T, typename ...U>

void setUniforms(const Shader &s, int &loc_io, int & tex_io, const T &val, U &&... uniforms)
{
	_internal::t_setUniform(s, loc_io, tex_io, val);

	setUniforms(s, loc_io, tex_io, uniforms...);
}

template<typename T>

void setUniforms(const Shader &s, int &loc_io, int & tex_io, const T &val)
{
	_internal::t_setUniform(s, loc_io, tex_io, val);

}