#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;

void main() {

    vec4 texColor = texture(texture1, TexCoord);
    FragColor = texColor * vec4(ourColor, 1.0);
};