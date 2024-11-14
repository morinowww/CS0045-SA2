#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>

//Prototypes
void generateCircleVertices();

// VBO variables
GLuint VBOstoredVerticesID;
GLuint VBOstoredColorsID;
bool isRenderDisplayed = true;

GLfloat verticesVBO[] = {
	// BG: Sky (Quad)
    -1.0f,  0.0f, 0.0f,  	// Bottom-left
    1.0f,  0.0f, 0.0f,  	// Bottom-right
	1.0f,  1.0f, 0.0f,  	// Top-right
    -1.0f,  1.0f, 0.0f,  	// Top-left

    // BG: Grass (Quad)
    -1.0f, -1.0f, 0.0f,  	// Bottom-left
    1.0f, -1.0f, 0.0f,  	// Bottom-right
    1.0f,  0.0f, 0.0f,  	// Top-right
    -1.0f,  0.0f, 0.0f,  	// Top-left

    // BG: Cloud 1 (Rectangle)
    -0.6f,  0.7f, 0.0f,  	// Bottom-left
    -0.4f,  0.7f, 0.0f,  	// Bottom-right
    -0.4f,  0.8f, 0.0f,  	// Top-right
    -0.6f,  0.8f, 0.0f,  	// Top-left

    // BG: Cloud 2 (Rectangle)
    0.0f,  0.75f, 0.0f, 	// Bottom-left
    0.3f,  0.75f, 0.0f, 	// Bottom-right
    0.3f,  0.85f, 0.0f, 	// Top-right
    0.0f,  0.85f, 0.0f, 	// Top-left
	
	//Po: Head
    -0.40f, 0.30f, 0.0f,    	// 0°
    -0.412f, 0.353f, 0.0f,  	// 22.5°
    -0.4293f, 0.3707f, 0.0f, 	// 45°
    -0.447f, 0.387f, 0.0f,   	// 67.5°
    -0.50f, 0.40f, 0.0f,     	// 90°
    -0.552f, 0.387f, 0.0f,   	// 112.5°
    -0.5707f, 0.3707f, 0.0f, 	// 135°
    -0.587f, 0.353f, 0.0f,   	// 157.5°
    -0.60f, 0.30f, 0.0f,     	// 180°
    -0.587f, 0.247f, 0.0f,   	// 202.5°
    -0.5707f, 0.2293f, 0.0f, 	// 225°
    -0.552f, 0.213f, 0.0f,   	// 247.5°
    -0.50f, 0.20f, 0.0f,     	// 270°
    -0.447f, 0.213f, 0.0f,   	// 292.5°
    -0.4293f, 0.2293f, 0.0f, 	// 315°
    -0.412f, 0.247f, 0.0f,   	// 337.5°
    
    //Po: Head (Internal)
	-0.410f, 0.300f, 0.0f,      // 0°
	-0.421f, 0.348f, 0.0f,      // 22.5°
	-0.436f, 0.364f, 0.0f,      // 45°
	-0.452f, 0.378f, 0.0f,      // 67.5°
	-0.500f, 0.390f, 0.0f,      // 90°
	-0.547f, 0.378f, 0.0f,      // 112.5°
	-0.564f, 0.364f, 0.0f,      // 135°
	-0.578f, 0.348f, 0.0f,      // 157.5°
	-0.590f, 0.300f, 0.0f,      // 180°
	-0.578f, 0.252f, 0.0f,      // 202.5°
	-0.564f, 0.236f, 0.0f,      // 225°
	-0.547f, 0.222f, 0.0f,      // 247.5°
	-0.500f, 0.210f, 0.0f,      // 270°
	-0.452f, 0.222f, 0.0f,      // 292.5°
	-0.436f, 0.236f, 0.0f,      // 315°
	-0.421f, 0.252f, 0.0f,      // 337.5°

};

GLfloat colorsVBO[] = {
    // BG: Sky (Quad)
    0.5f, 0.8f, 1.0f,	// Bottom-left
    0.5f, 0.8f, 1.0f,	// Bottom-right
	0.5f, 0.8f, 1.0f,	// Top-right
    0.5f, 0.8f, 1.0f,	// Top-left

    // BG: Grass (Quad)
    0.3f, 0.9f, 0.3f,	// Bottom-left
    0.3f, 0.9f, 0.3f,	// Bottom-right
    0.3f, 0.9f, 0.3f,	// Top-right
    0.3f, 0.9f, 0.3f,	// Top-left

    // BG: Cloud 1 (Rectangle)
    1.0f, 1.0f, 1.0f,  	// Bottom-left
    1.0f, 1.0f, 1.0f,  	// Bottom-right
    1.0f, 1.0f, 1.0f,  	// Top-right
    1.0f, 1.0f, 1.0f,  	// Top-left

    // BG: Cloud 2 (Rectangle)
    1.0f, 1.0f, 1.0f, 	// Bottom-left
    1.0f, 1.0f, 1.0f, 	// Bottom-right
    1.0f, 1.0f, 1.0f, 	// Top-right
    1.0f, 1.0f, 1.0f, 	// Top-left
    
    //Po: Head
    1.0f, 0.0f, 0.0f,	// 0°
    1.0f, 0.0f, 0.0f,  	// 22.5°
    1.0f, 0.0f, 0.0f, 	// 45°
    1.0f, 0.0f, 0.0f,  	// 67.5°
    1.0f, 0.0f, 0.0f, 	// 90°
    1.0f, 0.0f, 0.0f,  	// 112.5°
    1.0f, 0.0f, 0.0f, 	// 135°
    1.0f, 0.0f, 0.0f,  	// 157.5°
    1.0f, 0.0f, 0.0f, 	// 180°
    1.0f, 0.0f, 0.0f,  	// 202.5°
    1.0f, 0.0f, 0.0f, 	// 225°
    1.0f, 0.0f, 0.0f,  	// 247.5°
    1.0f, 0.0f, 0.0f,   // 270°
    1.0f, 0.0f, 0.0f,  	// 292.5°
    1.0f, 0.0f, 0.0f, 	// 315°
    1.0f, 0.0f, 0.0f,  	// 337.5°
};

void renderVerticesVBO() {
	
	if (isRenderDisplayed){	
		glGenBuffers(1,&VBOstoredVerticesID);
		glBindBuffer(GL_ARRAY_BUFFER,VBOstoredVerticesID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesVBO), verticesVBO, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
		glGenBuffers(1,&VBOstoredColorsID);
		glBindBuffer(GL_ARRAY_BUFFER,VBOstoredColorsID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colorsVBO), colorsVBO, GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
		glPointSize(20.0f);
	
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
	
		glVertexPointer(3,GL_FLOAT,0,0);
		glColorPointer(3,GL_FLOAT,0,0);
		
		isRenderDisplayed = false;
	}
	glDrawArrays(GL_QUADS, 0, 4);	//Draw gky
	glDrawArrays(GL_QUADS, 4, 4);	//Draw grass
    glDrawArrays(GL_QUADS, 8, 4);	//Draw clouds 1
    glDrawArrays(GL_QUADS, 12, 4);	//Draw clouds 2
    glDrawArrays(GL_POLYGON, 16, 16);
    glDrawArrays(GL_POLYGON, 32, 16);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	renderVerticesVBO();
	glFlush();
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(960, 540);
    glutCreateWindow("Teletubbies Background using VBO | Moreno, Santos, Cando");

    // Initialize GLEW
    glewInit();
    // Register display callback
    glutDisplayFunc(display);

    // Enter the main loop
    glutMainLoop();
    return 0;
}
