//
//  cube.cpp
//  GLVertex
//
//  Created by Wolfgag on 5/21/14.
//
//

#include "cube.h"

Cube::Cube()
{
    cout << "new Cube!\n";
    // Create the points of our cube
    Vec3f v0(-1,-1,-1);
    Vec3f v1( 1,-1,-1);
    Vec3f v2( 1, 1,-1);
    Vec3f v3(-1, 1,-1);
    Vec3f v4(-1,-1, 1);
    Vec3f v5( 1,-1, 1);
    Vec3f v6( 1, 1, 1);
    Vec3f v7(-1, 1, 1); //center of the object is (0, 0, 0)
    
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
    
    for (int i = 0; i < 6; i++) //each face
    {
        
        cube.appendVertex(faces[i][0]);
        cube.appendColorsRgb(&colors[i][0], 1);
        cube.appendTexCoord(Vec2f(0, 0));
        
        cube.appendVertex(faces[i][1]);
        cube.appendColorsRgb(&colors[i][1], 1);
        cube.appendTexCoord(Vec2f(2, 0));
        
        cube.appendVertex(faces[i][2]);
        cube.appendColorsRgb(&colors[i][2], 1);
        cube.appendTexCoord(Vec2f(2, 2));
        
        cube.appendVertex(faces[i][3]);
        cube.appendColorsRgb(&colors[i][3], 1);
        cube.appendTexCoord(Vec2f(0, 2));
        
        vertices = cube.getNumVertices();
        
        cube.appendTriangle( vertices - 4, vertices - 3, vertices - 2 );
        cube.appendTriangle( vertices - 4, vertices - 2, vertices - 1 );
    }
    
    vertices = cube.getNumVertices();
    indices = cube.getNumIndices();

    cubeTex = gl::Texture::create(loadImage(loadResource("pixelkid.jpg")));
    cubeTex->setWrap(GL_REPEAT, GL_REPEAT);
    
    pos = Vec3f(0, 0, 0);
    rot = Vec3f(0, 0, 0);
    size = Vec3f(50, 50, 50);
}

void Cube::update()
{
    if( cube.getNumVertices() == 0 ) return;
}

void Cube::draw()
{
    gl::pushMatrices();
    gl::translate(pos);
    gl::scale(size);
    gl::rotate(rot); //rotate, scale is fine too because origin of the object is at center
    cubeTex->enableAndBind();
    gl::draw(cube);
    cubeTex->unbind();
    gl::popMatrices();
}

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