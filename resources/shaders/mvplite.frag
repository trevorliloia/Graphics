#version 450

out vec4 outColor;
in vec2 vUV;
in vec4 vPos;
in vec4 vNormal;

layout (location = 3) uniform sampler2D diffuse;


void main()
{
	vec3 L = normalize(vec3(1,-1,1));
	vec3 N = vNormal.xyz;

	float lamb = dot(N, -L);
    outColor = lamb*texture(diffuse, vUV);
}
