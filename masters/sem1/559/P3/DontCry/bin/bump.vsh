uniform vec4 bulb;
varying vec3 light_direction;

void main(void)
{
 gl_TexCoord[0] = gl_MultiTexCoord0;
 gl_TexCoord[1] = gl_MultiTexCoord1;
 gl_FrontColor = gl_Color;
 light_direction = bulb - gl_Vertex;
 gl_Position = ftransform(); //fixed function pipeline
}