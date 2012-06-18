layout(location=3) in vec3 in_color

void main()
{
	gl_FragColor = vec4(in_color, 1.0);
}
