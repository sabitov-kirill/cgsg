#version 460

// Input Render Data Buffer
layout(std140, binding = 2) uniform RenderData
{
  vec3 CamDir;
  float Dummy;
  vec3 CamLoc;
  float FrameW;
  vec3 CamRight;
  float FrameH;
  vec3 CamUp;
  float Time;
};

// Input Material Data Buffer
layout(std140, binding = 1) uniform MaterialData
{
  vec3 Ka;
  float IsTexture;
  vec3 Kd;
  float Trans;
  vec3 Ks;
  float Ph;
};

in vec4 DrawColor;
in vec2 DrawTexCoord;
in vec3 DrawNormal;
in vec3 DrawPos;

// Color processed by shader
layout(location = 0) out vec4 OutColor;

// Textures
layout(binding = 0) uniform sampler2D Texture;

// Shading function
vec3 Shade( vec3 P, vec3 N, vec3 L, vec3 LColor )
{
  vec3 V = normalize(P - CamLoc);
  vec3 color = vec3(0);

  // Ambient
  color += Ka;

  // Duffuse
  float nl = dot(N, L);
  nl = max(nl, 0);
  vec3 diff = LColor * Kd * nl * 1.3;
  if (bool(IsTexture))
    diff *= texture(Texture, DrawTexCoord).rgb;
  color += diff;

  // Specular
  vec3 R = reflect(V, N);
  float rl = max(dot(R, L), 0);
  color += rl * LColor * Ks * pow(rl, Ph);

  return color;
}

void main( void )
{
  // Vertex norma;
  vec3 N = normalize(DrawNormal);
  // Light sourse position
  // vec3 L = normalize(vec3(15 * sin(Time), 5 + 10 * sin(Time / 3), 2.3 * cos(Time)));
  vec3 L = normalize(vec3(0, 50, 0));
  // Light color
  vec3 LCol = vec3(1);

  // Setting out color by shading
  vec3 ShadedColor = Shade(DrawPos, N, L, LCol);
  OutColor = vec4(ShadedColor, 1);
}