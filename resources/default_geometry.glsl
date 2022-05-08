in vec3 fragPos[];
in vec3 fragColor[];

layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

out vec3 gs_normal;
out vec3 gs_fragPos;
out vec3 gs_fragColor;

void main( void )
{
    vec3 U = fragPos[1].xyz - fragPos[0].xyz;
    vec3 V = fragPos[2].xyz - fragPos[0].xyz;
    vec3 N = normalize( cross( U, V ) );

    for( int i=0; i<gl_in.length(); ++i )
    {
        gl_Position = gl_in[i].gl_Position;
        gs_fragPos = fragPos[i];
        gs_fragColor = fragColor[i];
        gs_normal = N;
        EmitVertex();
    }

    EndPrimitive();
}