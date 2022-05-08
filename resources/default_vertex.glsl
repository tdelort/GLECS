// default vertex data
in vec3 v_position;
in vec3 v_color;

// default uniforms
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec3 fragPos;
out vec3 fragColor;

void main()
{
    gl_Position = u_projection * u_view * u_model * vec4(v_position, 1.0);
    fragPos = vec3(u_model * vec4(v_position, 1.0));
    fragColor = v_color;
}