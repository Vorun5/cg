#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 aTexCoord;
//layout (location = 2) in vec3 aNormal;
uniform float aTime;
uniform float aC;
uniform float aA;

out vec2 TexCoord;
out vec3 CameraPos;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 u_proj;
uniform mat4 u_view;
uniform mat4 u_model;
uniform vec3 u_cameraPos;
	
void main()
{	
	CameraPos = u_cameraPos;
	float x = position.x;
	float y = position.y;

	gl_Position = u_proj * u_view * u_model * vec4(x, y, aA * sin( (y/60) - (aC * aTime) ), 1.0);
	TexCoord = aTexCoord;
	FragPos = vec3(u_model * vec4(position, 1.0));

	float k = 1/60;
	float dx = 1;
    float dy = 1;
    float dzdy = aA * k * cos((k * y) - cos(aC * aTime));
    float dzdx = 0;

	vec3 norm = vec3(dy * dzdx - dzdy * dx, dzdy * dx - dzdx * dy, dzdx * dy - dy * dzdx);
	Normal =  normalize(norm);
}