#version 330 core

in vec4 vCol;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D theTexture;

void main(){
   vec4 texColor = texture(theTexture, TexCoord);
   color = texColor ;
};