
varying vec4 v_fragmentColor;	
varying vec2 v_texCoord;

uniform vec2 center;
uniform vec2 resolution;
//uniform float lightcount;
uniform vec2 lightposition;	//[5];
//CC_Time[1] is time

void main()			
{
	vec4 c = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
	float d = resolution.x/8.0;
	float opacity = 1.0;
	int i;
	for(i=0; i<1; ++i)
	{
		float dist = distance(gl_FragCoord.xy, lightposition);
		dist = (dist/d);
		if(i)
		    dist = dist*2.0;
		opacity = opacity*dist;
	}
	gl_FragColor.rgb = c.rgb;
	gl_FragColor.a = opacity;
}				
