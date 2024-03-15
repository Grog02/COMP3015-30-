#version 460

// Variables from Vertex Shader
in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;

// Texture mapping and fragment colour
layout (binding = 0) uniform sampler2D Tex1;    
layout (location = 0) out vec4 FragColor;


// Light structure info 
uniform struct Lightinfo{
    vec4 Position; 
    vec3 La;
    vec3 L;
}Light;

// Material structure with material properties
uniform struct MaterialInfo{
    vec3 Kd;
    vec3 Ka;
    vec3 Ks;
    float Shininess;
}Material;

// Fog structure with fog parameters
uniform struct FogInfo{
    float MaxDist;
    float MinDist;
    vec3 Color;
}Fog;

// Blinn-Phong model
vec3 blinnPhong(vec3 position, vec3 n)
{
    vec3 diffuse = vec3(0), spec = vec3(0);
    vec3 texColor = texture(Tex1, TexCoord).rgb;
    vec3 ambient = Light.La * texColor;

    vec3 s = normalize(Light.Position.xyz - position); 
    float sDotN = max(dot(s, n), 0.0);
    diffuse = texColor * sDotN;
    if (sDotN > 0.0)
    {
        vec3 v = normalize (-position.xyz);
        vec3 h = normalize(v + s); // Correct normalization
        spec = Material.Ks * pow(max(dot(h, n), 0.0), Material.Shininess);
    }    
    return ambient + (diffuse + spec) * Light.L;

}

// Main function for calculating fragment colour
void main() 
{
    float dist=abs(Position.z);
    float fogFactor = (Fog.MaxDist - dist)/(Fog.MaxDist - Fog.MinDist);
    //fogFactor = clamp(fogFactor, 0.0, 1.0);
    fogFactor = pow(fogFactor, 2.0);
    vec3 shadeColor = blinnPhong(Position,normalize(Normal));
    vec3 color = mix(Fog.Color, shadeColor, fogFactor);
    FragColor = vec4(color, 1.0);
}