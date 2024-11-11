#version 330 core

in vec3 normals;
in vec2 TexCord;

out vec4 fColor;

uniform vec3 color;

uniform sampler2D tex;

void main()
{

	// fColor=vec4(color, 1.0);  
	// Color without texture

	vec4 textureColor = texture(tex, TexCord);
	fColor = textureColor * vec4(color, 1.0);
	// Color with texture
}