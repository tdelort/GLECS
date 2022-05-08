in vec3 gs_normal;
in vec3 gs_fragPos;
in vec3 gs_fragColor;

vec3 lightPos = vec3(2.0, 0.0, -1.0);
vec3 lightColor = vec3(1.0, 1.0, 1.0);

out vec4 outColor;

void main()
{
    float intensity = max(dot(normalize(gs_normal), normalize(lightPos - gs_fragPos)), 0.0);
    vec3 diffuse = lightColor * intensity; 
    vec3 ambient = lightColor * 0.1;
    outColor = vec4((diffuse + ambient) * gs_fragColor, 1);
    //outColor = vec4(gs_normal * 0.5 + 0.5 , 1.0);
}