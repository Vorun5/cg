// #version 330 core
// in vec3 FragPos;
// in vec3 Normal;

void main()
{   
	// vec3 viewPos = vec3(2.5, 2.5, -1);
    // vec3 lightPos = vec3(5.0, -10.0, 1.0);
	// vec3 lightColor = vec3(1.0, 1.0, 1.0);
	// vec3 objectColor = vec3(0.4, 0.2, 0.7);

	// ambient
    // float ambientStrength = 0.6;
    // vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    // vec3 norm = normalize(Normal);
    // vec3 lightDir = normalize((lightPos -(FragPos)));
    // float diff = max(dot(norm, lightDir), 0.0);
    // vec3 diffuse = diff * lightColor;
    
    // specular
    // float specularStrength = 0.5;
    // vec3 viewDir = normalize(viewPos - FragPos);
    // vec3 reflectDir = reflect(-lightDir, norm);  
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1);
    // vec3 specular = specularStrength * spec * lightColor;  
    // vec3 result = (ambient + diffuse + specular) * objectColor;
    
    gl_FragColor = vec4(0.4, 0.2, 0.7, 0); //vec4(result, 1);
}