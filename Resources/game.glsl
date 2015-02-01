
varying vec4 v_fragmentColor;	
varying vec2 v_texCoord;

uniform vec2 center;
uniform vec2 resolution;
//CC_Time[1] is time

void main()			
{
//	vec2 p = 2.0 * (gl_FragCoord.xy + center.xy) / resolution.xy;
	vec4 c = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
//	c = (c + vec4(0.07, 0.07, 0.07, 0.7)) * vec4(1.6,abs(cos(CC_Time[1])), abs(sin(CC_Time[1])), 1.0);
	float d = resolution.x/8.0;	//smoothstep(1.0, 0.1, 1.0-length(v_texCoord));
	float dist = distance(gl_FragCoord.xy, center);
//	if(dist < resolution.x/8.0)
//		d = 0.0;
	gl_FragColor.rgb = c.rgb;
	gl_FragColor.a = dist/d;
}				
