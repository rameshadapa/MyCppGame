#define MULTIPLIER 1.22

varying vec4 v_fragmentColor;	
varying vec2 v_texCoord;

uniform vec2 resolution;

void main()
{
 	vec3 lightColor = vec3(1.0, 1.0, 0.0);
	vec3 lightAttenuation = vec3(0.25, 0.1, 0.1);		
	vec2 center = vec2(resolution.x/2.0, resolution.y/2.0);
	vec2 uv = gl_FragCoord.xy/resolution - .5;
	float aspect=resolution.x/resolution.y;
	uv=uv*aspect;

	int i;
	vec4 color;
	vec4 c;
	float alpha = 1.0;
	for(i=0; i<1; ++i)
	{
		float distance=distance(gl_FragCoord.xy, center*MULTIPLIER);
		float attenuation=1.0/(lightAttenuation.x+lightAttenuation.y*distance+lightAttenuation.z*distance*distance);	
		color=vec4(attenuation,attenuation,attenuation,1.0)*vec4(lightColor,0.5)*resolution.x*2.0;	
		c = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
		alpha = alpha*(1.0-color.r*color.g);
	}
 	gl_FragColor.rgb = c.rgb;
	gl_FragColor.a = alpha;
}
