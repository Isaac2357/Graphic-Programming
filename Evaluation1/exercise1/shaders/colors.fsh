#version 330

out vec4 pixelColor;
in vec4 gl_FragCoord;
uniform float widthScreen;
uniform float heightScreen;


void main() {
	
	float inc = 2.4 / widthScreen;
	vec2 vecx = vec2(-1.2 + gl_FragCoord.x*inc, -1.2 + gl_FragCoord.y*inc);
	vec2 vecz = vec2(-0.74543, 0.11301);
	int count = 0;
	
	while (sqrt(vecx.x * vecx.x + vecx.y * vecx.y) <= 2.0 && count < 128) {
		vec2 aux = vec2( vecx.x*vecx.x - vecx.y*vecx.y, 2 * vecx.x * vecx.y);
		vecx = aux + vecz;
		count++;
	}
	
	float factor = count/128.0;
	
	vec4 color1 = vec4(0.04, 0.16, 0.08, 1.0);
	vec4 color2 = vec4(0.90, 0.98, 0.67, 1.0);
	vec4 color3 = vec4(0.67, 0.17, 0.17, 1.0);
	/*vec4 color1 = vec4(1,0,0, 1.0);
	vec4 color2 = vec4(0,1,0 ,1.0);
	vec4 color3 = vec4(0,0,1, 1.0);*/
		
	if (sqrt(vecx.x * vecx.x + vecx.y * vecx.y) <= 2.0) {
		pixelColor = color1;
	} else if(count == 128) {
		pixelColor = color2;
	} else if(count == 0) {
		pixelColor = color3;
	} else {
		pixelColor = (1-factor)*color3 + factor*color2;
		//pixelColor = vec4(1,1,1,1);
		
	}
	
}