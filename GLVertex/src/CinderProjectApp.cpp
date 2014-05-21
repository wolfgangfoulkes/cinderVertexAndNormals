#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/TriMesh.h"
#include "cinder/ObjLoader.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CinderProjectApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    TriMesh trimesh;
    gl::TextureRef triTex;
    
    int rot = 0;
};

void CinderProjectApp::setup()
{
    // Create the points of our cube
    Vec3f v0(-100,-100,-100);
    Vec3f v1( 100,-100,-100);
    Vec3f v2( 100, 100,-100);
    Vec3f v3(-100, 100,-100);
    Vec3f v4(-100,-100, 100);
    Vec3f v5( 100,-100, 100);
    Vec3f v6( 100, 100, 100);
    Vec3f v7(-100, 100, 100);
    
    // Create the colors for each vertex
    Color c0( 0, 0, 0 );
    Color c1( 1, 0, 0 );
    Color c2( 1, 1, 0 );
    Color c3( 0, 1, 0 );
    Color c4( 0, 0, 1 );
    Color c5( 1, 0, 1 );
    Color c6( 1, 1, 1 );
    Color c7( 0, 1, 1 );
    
    Vec3f faces[6][4] = { /* Vertices for the 6 faces of a cube. */
        {v0, v1, v2, v3}, {v3, v2, v6, v7}, {v7, v6, v5, v4},
        {v4, v5, v1, v0}, {v5, v6, v2, v1}, {v7, v4, v0, v3} };
    
    Color colors[6][4] = { /* colors for each vertex of the cube. */
        {c0, c1, c2, c3}, {c3, c2, c6, c7}, {c7, c6, c5, c4},
        {c4, c5, c1, c0}, {c5, c6, c2, c1}, {c7, c4, c0, c3} };
    
    for (int i = 0; i < 6; i++)
    {
        
        trimesh.appendVertex(faces[i][0]);
        trimesh.appendColorsRgb(&colors[i][0], 1);
        trimesh.appendTexCoord(Vec2f(0, 0));
        
        trimesh.appendVertex(faces[i][1]);
        trimesh.appendColorsRgb(&colors[i][1], 1);
        trimesh.appendTexCoord(Vec2f(2, 0));
        
        trimesh.appendVertex(faces[i][2]);
        trimesh.appendColorsRgb(&colors[i][2], 1);
        trimesh.appendTexCoord(Vec2f(2, 2));
        
        trimesh.appendVertex(faces[i][3]);
        trimesh.appendColorsRgb(&colors[i][3], 1);
        trimesh.appendTexCoord(Vec2f(0, 2));
        
        int numberVertices = trimesh.getNumVertices();
        
        trimesh.appendTriangle( numberVertices - 4, numberVertices - 3, numberVertices - 2 );
        trimesh.appendTriangle( numberVertices - 4, numberVertices - 2, numberVertices - 1 );
    }
    
    fs::path path= getSaveFilePath( "trimesh.obj" );
    trimesh.write( writeFile( path ) );
    
    triTex = gl::Texture::create(loadImage(loadResource("pixelkid.jpg")));
    triTex->setWrap(GL_REPEAT, GL_REPEAT);
    gl::enableDepthRead(); //try with and without to get what this is //super-slow if you call it in the draw loop tho.
    gl::enableDepthWrite();
}

void CinderProjectApp::mouseDown( MouseEvent event )
{
}

void CinderProjectApp::update()
{
    if( trimesh.getNumVertices() == 0 ) return;
    
    // store all the mesh information
    
    std::vector<Color> col = trimesh.getColorsRGB();
    std::vector<Vec3f> vec = trimesh.getVertices();
    
    int i, j;
    i = trimesh.getNumVertices();
    j = 0;
    
    rot = getElapsedFrames() % 360;

    
    /*
    trimesh.clear();
    
    // something to add a little movement
    float inc = sin( getElapsedSeconds() );
    
    while(j < i)
    {
        // alter the positions array to get a little dynamism
        vec.at(j).x -= inc;
        vec.at(j+1).x = inc;
        vec.at(j+2).x += inc*2.0f;
        vec.at(j+3).x -= inc*2.0f;
        
        // now replace it in the mesh
        // alter the positions array to get a little dynamism
        vec.at(j).x -= inc;
        vec.at(j+1).x += inc;
        vec.at(j+2).x += inc;
        vec.at(j+3).x -= inc;
        
        // now replace it in the mesh
        trimesh.appendVertex( vec.at(j));
        trimesh.appendVertex( vec.at(j+1));
        trimesh.appendVertex( vec.at(j+2));
        trimesh.appendVertex( vec.at(j+3));
        
        
        //getNumVertices() = 4, 8, 12, 16, 20;
        int vIdx0 = trimesh.getNumVertices() - 4; //0, 4, 8
        int vIdx1 = trimesh.getNumVertices() - 3; //1, 5, 9
        int vIdx2 = trimesh.getNumVertices() - 2; //2, 6, 10
        int vIdx3 = trimesh.getNumVertices() - 1; //3, 7, 11
        
        trimesh.appendTriangle( vIdx0, vIdx1, vIdx2 );
        trimesh.appendTriangle( vIdx0, vIdx2, vIdx3 );
 
        // go to the next triangle pair
        j+=4;
    }
    */
}

void CinderProjectApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    gl::pushMatrices();
    gl::translate(Vec3f(getWindowWidth()/2, getWindowHeight()/2, 0));
    gl::rotate(Vec3f(0, rot, 0));
    triTex->enableAndBind();
    gl::draw(trimesh);
    triTex->unbind();
    gl::popMatrices();
}

CINDER_APP_NATIVE( CinderProjectApp, RendererGl )
