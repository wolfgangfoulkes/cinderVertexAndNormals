#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/TriMesh.h"
#include "cinder/ObjLoader.h"

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
};

void CinderProjectApp::setup()
{
    cout << "setup called!";
    cube = new Cube();
    gl::enableDepthRead(); //try with and without to get what this is //super-slow if you call it in the draw loop tho.
    gl::enableDepthWrite();
}

void CinderProjectApp::mouseDown( MouseEvent event )
{
}

void CinderProjectApp::update()
{
    cube->pos = Vec3f(getWindowWidth()/2, getWindowHeight()/2, 0);
    cube->rot.y = getElapsedFrames() % 360;
    

}

void CinderProjectApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    cube->draw();
}

CINDER_APP_NATIVE( CinderProjectApp, RendererGl )
