#version 300 esope
precision mediump float;

layout(location = 0) in vec3 aVertexPosition;

out vec3 vColor;

uniform mat3 uModelMatrix;
uniform vec3 uColor;

mat3 rotate(float a) {
  float radAngle = radians(a);
  return mat3(vec3(cos(radAngle), sin(radAngle), 0), vec3(-sin(radAngle), cos(radAngle), 0), vec3(0, 0, 1));
}

void main() {
    vColor = uColor;
    vec3 rotatedVertex = vec3(aVertexPosition, 1) * uModelMatrix;
    gl_Position = vec4(rotatedVertex, 1);
}
