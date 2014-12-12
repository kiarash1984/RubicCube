//! [0]
uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform mat3 normalMatrix;
uniform vec3 lightPosition;
uniform vec3 leftlightPosition;

attribute vec4 vertex;
attribute vec3 normal;
attribute vec3 color;


varying vec3 varyingNormal;
varying vec3 varyingLightDirection;
varying vec3 varyingViewerDirection;
varying vec3 varyingColor;


void main(void)
{
    vec4 eyeVertex = mvMatrix * vertex;
    eyeVertex /= eyeVertex.w;
    varyingNormal = normalMatrix * normal;
    varyingLightDirection = lightPosition - eyeVertex.xyz;
    //varyingLightDirection += leftlightPosition - eyeVertex.xyz;
    varyingViewerDirection = -eyeVertex.xyz;
	varyingColor = color;
    gl_Position = mvpMatrix * vertex;
}
//! [0]
