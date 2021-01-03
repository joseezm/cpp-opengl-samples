# version 330 core
// Do not modify the above version directive to anything older than 330, as
// modern OpenGL will not work properly due to it not being core at the time.

// Shader inputs
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

// Shader outputs, if any
out vec3 Color;
out vec2 TexCoord;

// Uniform variables
uniform mat4 modelview;
uniform mat4 projection;

void main() {
    gl_Position = projection * modelview * vec4(position, 1.0f);
	Color = color; // Just forward this color to the fragment shader
	TexCoord = vec2(texCoord.x, texCoord.y);
}

