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

// Input Primitive Data Buffer
layout(std140, binding = 3) uniform PrimitiveData
{
    mat4 MatrW;
    mat4 MatrWVP;
};
