uniform sampler2D tex1, tex2;
uniform int mode;

void main (void) 
{
	vec4 c1 = texture2D(tex1, gl_TexCoord[0].st);
	vec4 c2 = texture2D(tex2, gl_TexCoord[0].st);

	if (mode == 2) { // DUBOIS
		float red = 0.456100 * c1.r + 0.500484 * c1.g + 0.176381 * c1.b - 0.0434706 * c2.r - 0.0879388 * c2.g - 0.00155529 * c2.b;
		float green = -0.0400822 * c1.r - 0.0378246 * c1.g - 0.0157589 * c1.b + 0.378476 * c2.r + 0.73364 * c2.g - 0.0184503 * c2.b;
		float blue = -0.0152161 * c1.r - 0.0205971 * c1.g - 0.00546856 * c1.b - 0.0721527 * c2.r - 0.112961 * c2.g + 1.2264 * c2.b;

		gl_FragColor = vec4(red, green, blue, 1.0);
	} else { // SIMPLE
		gl_FragColor = vec4(c1.r, c2.g, c2.b, 1.0);
	}
}
