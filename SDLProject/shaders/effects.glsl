uniform sampler2D diffuse;
varying vec2 texCoordVar;

void main()
{
    vec4 colour = texture2D(diffuse, texCoordVar);
    gl_FragColor = vec4(colour.r, 0, 0, colour.a);
}
