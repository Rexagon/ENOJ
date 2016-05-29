#version 330

uniform sampler2D diffuse_tex;
uniform sampler2D normal_tex;
uniform sampler2D specular_tex;

in vec2 v_tex_coords;
in vec3 v_normal;
in vec3 v_tangent;
in vec3 v_position;

in vec3 v_bone_weights; // for debug

vec3 get_normal()
{
    vec3 normal = normalize(v_normal);
    vec3 tangent = normalize(v_tangent);
    tangent = normalize(tangent - dot(tangent, normal) * normal);
    vec3 bitangent = cross(tangent, normal);
    mat3 tbn = mat3(tangent, bitangent, normal);
    
    vec3 t_normal = texture(normal_tex, v_tex_coords).xyz;
    return normalize(tbn * t_normal);
}

void main()
{
    vec3 diffuse = texture(diffuse_tex, v_tex_coords).rgb;
    vec3 normal = get_normal();
    vec3 specular = texture(specular_tex, v_tex_coords).rgb;
    
    gl_FragColor = vec4(diffuse, 1.0);
}