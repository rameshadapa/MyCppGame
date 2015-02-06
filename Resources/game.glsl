
varying vec4 v_fragmentColor;	
varying vec2 v_texCoord;

uniform vec2 resolution;
uniform vec2 lightposition;
//CC_Time[1] is time

void main()			
{
	vec4 c = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
	float d = resolution.x/8.0;
	float dist = distance(gl_FragCoord.xy, lightposition);
	gl_FragColor.rgb = c.rgb;
	gl_FragColor.a = dist/d;
}				
