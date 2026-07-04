uniform vec2 u_lightPos;       // Light position in screen coordinates
uniform vec3 u_lightColor;     // Light color (RGB normalized 0.0 to 1.0)
uniform float u_lightRadius;   // Radius of the light
uniform vec2 u_resolution;     // Window resolution (to flip Y axis)

void main() {
    // SFML's Y-axis is top-down, but OpenGL is bottom-up. Flip the Y-axis.
    vec2 pixelPos = gl_FragCoord.xy;
    vec2 correctedLightPos = vec2(u_lightPos.x, u_resolution.y - u_lightPos.y);

    // Calculate distance between this pixel and the light source
    float distance = length(correctedLightPos - pixelPos);

    // Calculate light intensity based on distance (linear falloff)
    float attenuation = 1.0 - smoothstep(0.0, u_lightRadius, distance);
    attenuation = clamp(attenuation, 0.0, 1.0);

    // Output final color mixed with attenuation, alpha set to 1.0 for additive mixing
    gl_FragColor = vec4(u_lightColor * attenuation, 1.0);
}