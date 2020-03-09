#version 330

out vec4 pixelColor;
in vec4 gl_FragCoord;
uniform float widthScreen;
uniform float heightScreen;


void main() {
	
	float delta = 2.4 / widthScreen;
	vec2 vecx = vec2(-1.2 + gl_FragCoord.x*delta, -1.2 + gl_FragCoord.y*delta);
	vec2 vecz = vec2(-0.74543, -0.11301);
	int count = 0;
	
	while (length(vecx) <= 2.0 && count < 128) {
		vec2 aux = vec2( vecx.x*vecx.x - vecx.y*vecx.y, 2 * vecx.x * vecx.y);
		vecx = aux + vecz;
		count++;
	}
	
	float gray;
	if (length(vecx) <= 2.0) {
		gray = 0.0;
	} else {
		gray = count/128.0;
	}
	
	pixelColor = vec4(gray, gray, gray, 1.0);
	
}