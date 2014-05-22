#version 400

//basic ADS lighting using functions

out vec3 FrontColor;
out vec3 BackColor;

vec3 light_position; // Light position in eye coords.
vec3 light_ambient; // Ambient light intensity
vec3 light_diffuse; // Diffuse light intensity
vec3 light_specular; // Specular light intensity

vec3 surface_ambient; // Ambient reflectivity
vec3 surface_diffuse; // Diffuse reflectivity
vec3 surface_specular; // Specular reflectivity
float shininess; // Specular shininess factor

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;

vec3 phongModel( vec4 position, vec3 norm )
{
    vec3 s = normalize(vec3(light_position - position));
    vec3 v = normalize(-position.xyz);
    vec3 r = reflect( -s, norm ); //angle reflected about the norm (e.g. the "opposite side")
    vec3 ambient = light_ambient * material_ambient;
    float sDotD = max( dot(s,norm), 0.0 );
    //lambert's law
    //get angle between normal and and light position
    vec3 diffuse = light_diffuse * material_diffuse * sDotN;
    //intensity of light varies based on angle between light and surface
    vec3 spec = vec3(0.0);
    if( sDotD > 0.0 ) //might be redundant
    {
        float sDotS = max( dot(r,v), 0.0);
        //r is -s reflected about the normal.
        spec = light_specular * material_specular * pow(sDotS, shininess);
        
    }
    return ambient + diffuse + spec;
}

void main()
{
    vec3 eyeNorm = normalize( NormalMatrix * VertexNormal);
    vec4 eyePosition = ModelViewMatrix * vec4(VertexPosition,1.0);
    // Get the position and normal in eye space
    getEyeSpace(eyeNorm, eyePosition);
    // Evaluate the lighting equation.
    
    FrontColor = phongModel( eyeCoords, tnorm );
    
    BackColor = phongModel( eyeCoords, -tnorm );
    
    gl_Position = ModelViewMatrix * ProjectionMatrix * vec4(VertexPosition,1.0);
}