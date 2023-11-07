// #version 330 core
// out vec3 FragPos;
// out vec3 Normal;

uniform float u_time;

void main()
{
    vec4 position = gl_Vertex;
    float x = position.x;
    float y = position.y;
    // (x * x) / K - Codaet krivizny na osi X
    // (y * y) / K - Codaet krivizny na osi Y
    float z1 = x * x / 3 + y * y / 2;
    float z2 = x * x / 3 - y * y / 2;
    // Vbls4eslaetcya linenaya interpolasiya mejdy Z1 è Z2
    position.z = mix(z1, z2, u_time);

    // gl_ModelViewProjectionMatrix - eto Model Matrix, View Matrix and Projection Matrix
    gl_Position = gl_ModelViewProjectionMatrix * position;
    
    // FragPos = vec3(gl_Position);
    // vec3 dX = vec3(1.0, 0.0, (z1 - z2) / (2.0 * 3.0));
    // vec3 dY = vec3(0.0, 1.0, (z1 - z2) / (2.0 * 2.0)); 
    // Normal = normalize(cross(dX, dY));
}