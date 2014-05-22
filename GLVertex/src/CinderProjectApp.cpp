/*
 this project crashes sometimes. I couldn't tell you why. avoid using the VBOMesh in the future
 */

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/Vbo.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/TriMesh.h"
#include "cinder/ObjLoader.h"
#include <vector>

#include "cube.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CinderProjectApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    Cube * cube; //use pointer or it's initialized here, which causes bad access;
    
    gl::VboMeshRef	mVboMesh, mVboMesh2;
    gl::TextureRef mTexture;
    
    int numIndices;
    int numVertices;
    
    vector<uint32_t> indices;
    vector<Vec3f>  vertices;
    vector<Vec2f> texCoords;
    
    gl::GlslProg basicShader;
};

void CinderProjectApp::setup()
{
    cout << "setup called!\n";
    cube = new Cube();
    
    numIndices = cube->cube.getNumIndices();
    cout << "numIndices" << cube->cube.getNumIndices() << "\n";
    numVertices = cube->cube.getNumVertices();
    cout << "numVertices" << cube->cube.getNumVertices() << "\n";
    indices = cube->cube.getIndices();
    vertices = cube->cube.getVertices();
    texCoords = cube->cube.getTexCoords();
    

	gl::VboMesh::Layout layout;
	layout.setStaticIndices();
	layout.setDynamicPositions(); //if you attempt to use bufferPositions etc. after setting this dynamic, EXCEPTION!
	layout.setStaticTexCoords2d();
	mVboMesh = gl::VboMesh::create( numVertices, cube->cube.getNumTriangles() * 4, layout, GL_TRIANGLES );
    //can also create a VboMesh of any kind (QUADS) using create(triMesh, layout)
    
    //cout << "layout:" << layout.;
    cout << "made a VboMesh!\n";
    
    mVboMesh->bufferIndices( indices );
    //mVboMesh->bufferPositions( vertices );
    mVboMesh->bufferTexCoords2d( 0, texCoords );
	
	mTexture = gl::Texture::create( loadImage( loadResource( "pixelkid.jpg" ) ) );
    mTexture->setWrap(GL_REPEAT, GL_REPEAT);
    
    gl::enableDepthRead(); //try with and without to get what this is //super-slow if you call it in the draw loop tho.
    gl::enableDepthWrite();
    
    basicShader = gl::GlslProg( loadResource("light_vert110.glsl"), loadResource("light_frag110.glsl"));
}

void CinderProjectApp::mouseDown( MouseEvent event )
{
}

void CinderProjectApp::update()
{
    cube->pos = Vec3f(getWindowWidth()/4, getWindowHeight()/4, 0);
    cube->rot.y = getElapsedFrames() % 360;
    
    gl::VboMesh::VertexIter iter = mVboMesh->mapVertexBuffer();
    for( int x = 0; x < numVertices; ++x )
    {
        iter.setPosition( vertices.at(x) );
        ++iter;
    }
}

void CinderProjectApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    basicShader.bind();
    cube->draw();
    basicShader.unbind();
    
    gl::pushMatrices();
    gl::translate(getWindowWidth()/2, getWindowHeight()/2);
    gl::scale(50, 50, 50);
    gl::rotate(cube->rot);
	mTexture->enableAndBind();
	gl::draw( mVboMesh );
    gl::popMatrices();
    mTexture->unbind();
}

CINDER_APP_NATIVE( CinderProjectApp, RendererGl )
