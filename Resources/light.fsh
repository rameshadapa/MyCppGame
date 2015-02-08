
varying vec4 v_fragmentColor;	
varying vec2 v_texCoord;

//uniform vec2 lightpos;
//uniform vec3 lightColor;
uniform vec2 resolution;
//uniform vec3 lightAttenuation;
//uniform float radius;

uniform sampler2D texture;

void main()
{
 	vec3 lightColor = vec3(1.0, 1.0, 0.0);
	vec3 lightAttenuation = vec3(0.25, 0.1, 0.1);		
	vec2 pixel=gl_FragCoord.xy;		
	pixel.y=resolution.y-pixel.y;	
	int i;
	vec4 color;
	vec4 c;
	float alpha = 1.0;
	for(i=0; i<2; ++i)
	{
	vec2 aux=resolution*(0.5+(float(i)*0.25))-pixel;
	float distance=length(aux);
	float attenuation=1.0/(lightAttenuation.x+lightAttenuation.y*distance+lightAttenuation.z*distance*distance);	
	color=vec4(attenuation,attenuation,attenuation,1.0)*vec4(lightColor,0.5)*resolution.x/2.0;	
	c = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
	alpha = alpha*(1.0-color.r*color.g);
	}
 	gl_FragColor.rgb = c.rgb;
	gl_FragColor.a = alpha;//*texture2D(texture,gl_TexCoord[0].st);
}