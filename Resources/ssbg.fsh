#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 center;
uniform vec2 mouse;
uniform vec2 resolution;

float length2(vec2 p) { return dot(p, p); }

float noise(vec2 p){
	return fract(sin(fract(sin(p.x) * (43.13311)) + p.y) * 31.0011);
}

float worley(vec2 p) {
	float d = 1e30;
	for (int xo = -1; xo <= 1; ++xo) {
		for (int yo = -1; yo <= 1; ++yo) {
			vec2 tp = floor(p) + vec2(xo, yo);
			d = min(d, length2(p - tp - vec2(noise(tp))));
		}
	}
	return 3.0*exp(-4.0*abs(2.0*d - 1.0));
}

float fworley(vec2 p) {
	return sqrt(sqrt(sqrt(
		1.1 * // light
		worley(p*50. + .3 + CC_Time[1]*.0525) *
		sqrt(worley(p * 50. + 0.3 + CC_Time[1] * -0.15)) *
		sqrt(sqrt(worley(p * -10. + 9.3))))));
}

void main() {
	vec2 uv = 2.0 * (gl_FragCoord.xy - center.xy) / resolution.xy;
	float t = fworley(uv * resolution.xy / 1500.0);
	t *= exp(-length2(abs(0.7*uv - 1.0)));
	gl_FragColor = vec4(vec3(t*1.2-.05*noise(vec2(sin(CC_Time[1])/1400.,t/50.))-.2), 1.0);
}
