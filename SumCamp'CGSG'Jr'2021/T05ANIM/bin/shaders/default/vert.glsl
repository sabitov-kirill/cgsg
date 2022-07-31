#version 460

// Input Primitive Data Buffer
layout(std140, binding = 3) uniform PrimitiveData
{
  mat4 MatrW;
  mat4 MatrWVP;
};

// Vertices input data (from VBO)
layout(location = 0) in vec3 InPosition;
layout(location = 1) in vec2 InTexCoord;
layout(location = 2) in vec3 InNormal;
layout(location = 3) in vec4 InColor;

// Out parametrs
out vec4 DrawColor;
out vec2 DrawTexCoord;
out vec3 DrawNormal;
out vec3 DrawPos;

void main( void )
{
  gl_Position = MatrWVP * vec4(InPosition, 1);

  DrawColor = InColor;
  DrawPos = (MatrW * vec4(InPosition, 1)).xyz;
  DrawNormal = inverse(transpose(mat3(MatrW))) * InNormal;
  DrawTexCoord = InTexCoord;
}
