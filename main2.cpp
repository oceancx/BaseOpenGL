////
////  main.cpp
////  BaseOpenGL
////
////  Created by oceancx on 16/8/6.
////  Copyright (c) 2016年 oceancx. All rights reserved.
////
//
//#include <iostream>
//
//
//#include <GL/glew.h>
//#include <OpenGL/gl3.h>
//#include <GLUT/glut.h>
////#include <OpenGL/gl.h>
//
////GLFW
////#include <GLFW/glfw3.h>
//#include "vgl.h"
//#include "LoadShaders.h"
//
//
////
////
////void render(void){
////
////    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
////    glClear(GL_COLOR_BUFFER_BIT);
////
////    glBegin(GL_TRIANGLES);
////    {
////        glColor3f(1.0, 0.0, 0.0);
////        glVertex2f(0, .5);
////        glColor3f(0.0, 1.0, 0.0);
////        glVertex2f(-.5, -.5);
////        glColor3f(0.0, 0.0, 1.0);
////        glVertex2f(.5, -.5);
////
////    }
////    glEnd();
////}
////
////int main(int argc, const char * argv[]) {
////    GLFWwindow *win;
////    if(!glfwInit()){
////        return -1;
////    }
////    win = glfwCreateWindow(640, 480, "OpenGL Base Project", NULL, NULL);
////    if(!win){
////        glfwTerminate();
////        exit(EXIT_FAILURE);
////    }
////    if (!glewInit()) {
////        return -1;
////    }
////
////    glfwMakeContextCurrent(win);
////
////    while(!glfwWindowShouldClose(win)){
////        render()   ;
////        glfwSwapBuffers(win);
////        glfwPollEvents();
////    }
////    glfwTerminate();
////    exit(EXIT_SUCCESS);
////
////
////    return 0;
////}
//
//
//enum VAO_IDs { Triangles, NumVAOs };
//enum Buffer_IDs { ArrayBuffer, NumBuffers };
//enum Attrib_IDs { vPosition = 0 };
//
//GLuint  VAOs[NumVAOs];
//GLuint  Buffers[NumBuffers];
//
//const GLuint NumVertices = 6;
//
//
//
///**
// *  初始化操作
// */
//void init() {
//    printf("init");
//    glGenVertexArrays(NumVAOs, VAOs);
//    glBindVertexArray(VAOs[Triangles]);
//    GLfloat  vertices[NumVertices][2] = {
//        { -0.90, -0.90 },  // Triangle 1
//        {  0.85, -0.90 },
//        { -0.90,  0.85 },
//        {  0.90, -0.85 },  // Triangle 2
//        {  0.90,  0.90 },
//        { -0.85,  0.90 }
//    };
//    glGenBuffers(NumBuffers, Buffers);
//    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices, GL_STATIC_DRAW);
//    
//    ShaderInfo  shaders[] = {
//        { GL_VERTEX_SHADER, "/Users/oceancx/Desktop/BaseOpenGL/BaseOpenGL/triangles.vert" },
//        { GL_FRAGMENT_SHADER, "/Users/oceancx/Desktop/BaseOpenGL/BaseOpenGL/triangles.frag" },
//        { GL_NONE, NULL}
//    };
//    GLuint program = LoadShaders(shaders);
//    
//    glUseProgram(program);
//    glVertexAttribPointer(vPosition, 2, GL_FLOAT,
//                          GL_FALSE, 0, BUFFER_OFFSET(0));
//    glEnableVertexAttribArray(vPosition);
//}
//
////---------------------------------------------------------------------
////
//// display
////
//void display(void) {
//    glClear(GL_COLOR_BUFFER_BIT);
//    glBindVertexArray(VAOs[Triangles]);
//    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
//    glFlush();
//}
//
//void display2() {
//    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color
//    
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
//    
//    glFlush();  // Render now}
//}
//
////---------------------------------------------------------------------
////
//// main
////
////int
////main(int argc, char** argv)
////{
////
////    init();
////    glutDisplayFunc(display);
////    glutMainLoop();
////}
//
//
//int main(int argc, char * argv[]) {      // to this.
//    printf("heelow oeidls");
//    glutInit(&argc, argv);
//    //glutInitDisplayMode(GLUT_RGBA|GLUT_3_2_CORE_PROFILE);
//    glutInitWindowSize(512, 512);
//    //    glutInitContextVersion(4, 3);
//    //    glutInitContextProfile(GLUT_CORE_PROFILE);
//    glutCreateWindow(argv[0]);
//    if (glewInit()) {
//        printf("not wordk");
//        exit(EXIT_FAILURE);
//    }
//    // init();
//    glutDisplayFunc(display2);
//    glutMainLoop();
//    
//    return 0;
//}
//
