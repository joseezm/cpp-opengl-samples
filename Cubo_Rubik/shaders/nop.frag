# version 330 core
// Do not modify the version directive to anything older than 330.

// Fragment shader inputs are outputs of the same name from vertex shader
in vec3 Color;
in vec2 TexCoord;

// Uniform variables
uniform sampler2D ourTexture;

// Output
out vec4 fragColor;

void main (void) 
{        
	fragColor = texture(ourTexture, TexCoord)*vec4(Color, 1.0f);
}
