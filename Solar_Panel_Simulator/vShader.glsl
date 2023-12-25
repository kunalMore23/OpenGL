attribute highp vec4 posAttr;
attribute lowp vec4 colAttr;
varying lowp vec4 col;
uniform highp mat4 matrix;
uniform highp float zoom;
void main() {
   col = colAttr;
       highp mat4 zoomMatrix = mat4(
        zoom, 0.0, 0.0, 0.0,
        0.0, zoom, 0.0, 0.0,
        0.0, 0.0, zoom, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
 
   gl_Position = matrix * posAttr * zoomMatrix;
}