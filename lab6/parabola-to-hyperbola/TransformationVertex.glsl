uniform float u_time;

void main()
{
    vec4 position = gl_Vertex;
    float x = position.x;
    float y = position.y;
    // (x * x) / K - Cozdaet krivizny na osi X
    // (y * y) / K - Cozdaet krivizny na osi Y
    float z1 = x * x / 3 + y * y / 2;
    float z2 = x * x / 3 - y * y / 2;

    float frequency = 1 / 8.0;
    float amplitude = 4.0;
    float timeFactor = sin(u_time * frequency);

    position.z = mix(z1, z2, timeFactor * amplitude);
    gl_Position = gl_ModelViewProjectionMatrix * position;
}