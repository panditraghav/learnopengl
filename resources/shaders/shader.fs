#version 330 core
out vec4 fragColor;

in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixA;

void main()
{
  fragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), mixA);
  // Flip the smily face along x axis
  // fragColor = mix(texture(texture1, texCoord), texture(texture2, vec2(1.0f - texCoord.x, texCoord.y)), 0.2f);
};
