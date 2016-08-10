/*
 * GL02Primitive.cpp: Vertex, Primitive and Color
 * Draw Simple 2D colored Shapes: quad, triangle and polygon.
 */
#include <GLUT/glut.h>  // GLUT, include glu.h and gl.h
#include "bitmap.h"
/* Initialize OpenGL Graphics */
DWORD* data;
int width;
int height;

void initGL() {
    
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
    

    
//    ifstream infile("42DC698F0000.tga",ios::binary|ios::in);
//    if(!infile){
//        cout<<"打开文件失败"<<endl;
//    }
//    TGA_FILE_HEADER TgaHeader;
//    infile.read((char*)&TgaHeader,sizeof(TGA_FILE_HEADER));
//    
//    
//    ofstream outfile("42DC698F0000.bmp",ios::out|ios::binary);
//    if(!outfile){
//        
//        return 0;
//    }
//    BITMAPFILEHEADER bithead;
//    BITMAPINFOHEADER bitinfo;
//    int headsize,linesize,i,j,s;
//    DWORD color;
//    int width = TgaHeader.ImageWidth;
//    int height = TgaHeader.ImageHeight;
//    linesize=(width*3+3)&0xfffffffc;
//    s=linesize-width*3;
//    memset(&bithead,0,sizeof(bithead));
//    headsize=sizeof(bithead)+sizeof(bitinfo);
//    bithead.bfType='MB';
//    printf("%s\n",&bithead.bfType );
//    bithead.bfSize=headsize+linesize*height;
//    printf("%x\n",bithead.bfSize );
//    bithead.bfOffBits=headsize;
//    printf("%x\n", headsize);
//    outfile.write((char*)&bithead,sizeof(bithead));
//    bitinfo.biSize=sizeof(bitinfo);
//    bitinfo.biWidth=width;
//    bitinfo.biHeight=height;
//    cout<<"height:" <<height<<endl;
//    bitinfo.biPlanes=1;
//    bitinfo.biBitCount=32;
//    bitinfo.biCompression=0;
//    bitinfo.biSizeImage=0;
//    bitinfo.biXPelsPerMeter=72;
//    bitinfo.biYPelsPerMeter=72;
//    bitinfo.biClrUsed=0;
//    bitinfo.biClrImportant=0;
//    outfile.write((char*)&bitinfo,sizeof(bitinfo));
//    
//    DWORD* data=new DWORD[width*height];
//    infile.read((char*)data,width*height*4);
//    
//    outfile.write((char*)data,width*height*4);
//    outfile.close();

}


/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color
    
//    // Define shapes enclosed within a pair of glBegin and glEnd
//    glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
//    glColor3f(1.0f, 0.0f, 0.0f); // Red
//    glVertex2f(-0.8f, 0.1f);     // Define vertices in counter-clockwise (CCW) order
//    glVertex2f(-0.2f, 0.1f);     //  so that the normal (front-face) is facing you
//    glVertex2f(-0.2f, 0.7f);
//    glVertex2f(-0.8f, 0.7f);
//    
//    glColor3f(0.0f, 1.0f, 0.0f); // Green
//    glVertex2f(-0.7f, -0.6f);
//    glVertex2f(-0.1f, -0.6f);
//    glVertex2f(-0.1f,  0.0f);
//    glVertex2f(-0.7f,  0.0f);
//
//    
//    glColor3f(0.2f, 0.2f, 0.2f); // Dark Gray
//    glVertex2f(-0.9f, -0.7f);
//    glColor3f(1.0f, 1.0f, 1.0f); // White
//    glVertex2f(-0.5f, -0.7f);
//    glColor3f(0.2f, 0.2f, 0.2f); // Dark Gray
//    glVertex2f(-0.5f, -0.3f);
//    glColor3f(1.0f, 1.0f, 1.0f); // White
//    glVertex2f(-0.9f, -0.3f);
//    glEnd();
//    
//    glBegin(GL_TRIANGLES);          // Each set of 3 vertices form a triangle
//    glColor3f(0.0f, 0.0f, 1.0f); // Blue
//    glVertex2f(0.1f, -0.6f);
//    glVertex2f(0.7f, -0.6f);
//    glVertex2f(0.4f, -0.1f);
//    
//    glColor3f(1.0f, 0.0f, 0.0f); // Red
//    glVertex2f(0.3f, -0.4f);
//    glColor3f(0.0f, 1.0f, 0.0f); // Green
//    glVertex2f(0.9f, -0.4f);
//    glColor3f(0.0f, 0.0f, 1.0f); // Blue
//    glVertex2f(0.6f, -0.9f);
//    glEnd();
//    
//    glBegin(GL_POLYGON);            // These vertices form a closed polygon
//    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
//    glVertex2f(0.4f, 0.2f);
//    glVertex2f(0.6f, 0.2f);
//    glVertex2f(0.7f, 0.4f);
//    glVertex2f(0.6f, 0.6f);
//    glVertex2f(0.4f, 0.6f);
//    glVertex2f(0.3f, 0.4f);
//    glEnd();
    
    glBegin(GL_POINTS);
    for(int i=0;i<height;i++){
        for (int j = 0; j<width;j++) {
            printf("%x ",data[i*width+j]) ;
            if(data[i*width+j]!=0){
                glColor4f(data[i*width+j] &0x00ff0000, data[i*width+j] &0x0000ff00,  data[i*width+j] &0x000000ff, data[i*width+j] &0xff000000);
                glVertex2f(1.0f*j/640,1.0f*i/480);
            }
        }
        printf("\n") ;
    }
    glEnd();
    
    
    
    glFlush();  // Render now
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    
    
    ifstream infile("/Users/oceancx/Desktop/BaseOpenGL/BaseOpenGL/42DC698F0000.bmp",ios::binary|ios::in);
    if(!infile){
        cout<<"打开文件失败"<<endl;
    }
    BITMAPFILEHEADER bithead;
    BITMAPINFOHEADER bitinfo;

    infile.read((char*)&bithead,sizeof(bithead));
    infile.read((char*)&bitinfo,sizeof(bitinfo));
    width = bitinfo.biWidth;
    height = bitinfo.biHeight;
    data=new DWORD[width*height];
    infile.read((char*)data,width*height*4);
    infile.close();
    
    glutInitWindowSize(640, 480);   // Set the window's initial width & height
    glutInit(&argc, argv);          // Initialize GLUT
    glutCreateWindow("Vertex, Primitive & Color");  // Create window with the given title
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutDisplayFunc(display);       // Register callback handler for window re-paint event
    initGL();                       // Our own OpenGL initialization
    glutMainLoop();                 // Enter the event-processing loop
    return 0;
}