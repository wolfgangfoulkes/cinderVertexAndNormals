in vec3 FrontColor;
in vec3 BackColor;

void main() {
    
    if( gl_FrontFacing ) {
        gl_FragColor = vec4(FrontColor, 1.0);
    } else {
        gl_FragColor = vec4(BackColor, 1.0);
    }
}