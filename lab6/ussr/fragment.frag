#version 330 core
	
in vec2 TexCoord;
in vec3 CameraPos;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D texture1;

void main()
{
	vec3 viewPos = CameraPos;
    vec3 lightPos = vec3(5.0, -10.0, 1.0);
	vec3 lightColor = vec3(1.0, 1.0, 1.0);
	vec3 objectColor = texture(texture1,TexCoord).xyz;

	// ambient
    float ambientStrength = 0.6;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize((lightPos -( FragPos)));
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1);
    vec3 specular = specularStrength * spec * lightColor;  
        
    vec3 result = (ambient + diffuse + specular) * objectColor;
 
    FragColor = vec4(result, 1.0);
}