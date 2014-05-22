//
//  cube.h
//  GLVertex
//
//  Created by Wolfgag on 5/21/14.
//
//

#ifndef __GLVertex__cube__
#define __GLVertex__cube__

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/TriMesh.h"
#include "cinder/ObjLoader.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Cube
{
    public:
    Cube();
    void update();
    void draw();
    
    TriMesh cube;
    gl::TextureRef cubeTex;
    
    int vertices;
    int indices;
    
    Vec3f pos;
    Vec3f rot;
    Vec3f size;
};

#endif /* defined(__GLVertex__cube__) */
