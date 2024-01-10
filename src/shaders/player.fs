#version 330 core

in vec2 texCoord;
out vec4 color;
uniform vec3 m_color;
uniform sampler2D m_texture;

void main()
{    
    color = vec4(m_color, 1.0) * texture(m_texture, texCoord);

}