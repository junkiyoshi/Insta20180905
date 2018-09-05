#version 150

uniform float time;
uniform vec2 resolution;
uniform sampler2DRect tex;
uniform vec3 x_noise;
uniform vec3 y_noise;

out vec4 outputColor;

// 2D Random
float random (in vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))
                 * 43758.5453123);
}

// 2D Noise based on Morgan McGuire @morgan3d
// https://www.shadertoy.com/view/4dS3Wd
float noise (in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    // Four corners in 2D of a tile
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    // Smooth Interpolation

    // Cubic Hermine Curve.  Same as SmoothStep()
    vec2 u = f*f*(3.0-2.0*f);
    // u = smoothstep(0.,1.,f);

    // Mix 4 coorners percentages
    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}

void main() {

  vec2 p = (gl_FragCoord.xy * 2.0 - resolution) / min(resolution.x, resolution.y);

  float drift = 60.0;
  float r = texture(tex, vec2(gl_FragCoord.x + drift * noise(vec2(p.x + x_noise.r, p.y + time)), (resolution.y - gl_FragCoord.y) + drift * noise(vec2(p.x + time, p.y + y_noise.r)))).r;
  float g = texture(tex, vec2(gl_FragCoord.x + drift * noise(vec2(p.x + x_noise.g, p.y + time)), (resolution.y - gl_FragCoord.y) + drift * noise(vec2(p.x + time, p.y + y_noise.g)))).g;
  float b = texture(tex, vec2(gl_FragCoord.x + drift * noise(vec2(p.x + x_noise.b, p.y + time)), (resolution.y - gl_FragCoord.y) + drift * noise(vec2(p.x + time, p.y + y_noise.b)))).b;
  outputColor = vec4(r, g, b, 1.0);
}
