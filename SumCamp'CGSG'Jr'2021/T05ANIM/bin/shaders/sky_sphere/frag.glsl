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

layout(location = 0) out vec4 OutColor;

in vec2 DrawTexCoord;

layout(binding = 0) uniform sampler2D Texture;

void  main( void )
{
  float w = FrameW, h = FrameH;
  vec2 s = (DrawTexCoord - 0.5) * 1;

  if (w > h) s.x *= w / h;
  else s.y *= h / w;

  vec3 dir = normalize(CamDir + CamRight * s.x + CamUp * s.y);
  float theta = -acos(dir.y);
  float phi = atan(dir.x, dir.z);
  float pi = acos(-1);
  vec2 c = vec2(phi / 2 / pi, 1 - theta / pi);

  vec4 tc = texture(Texture, c);
  OutColor = vec4(tc.rgb, 1);
}