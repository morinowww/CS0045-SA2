#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/glut.h>

// VBO variable
GLuint VBOstoredVertexID;
GLuint VBOstoredColorsID;
bool isRenderSkyDisplayed = true;

// Vertex data for the background (sky and grass) and simple cloud shapes
GLfloat verticesBG[] = {
    // Sky (Quad)
    -1.0f,  0.0f, 0.0f,  // Bottom-left
     1.0f,  0.0f, 0.0f,  // Bottom-right
     1.0f,  1.0f, 0.0f,  // Top-right
    -1.0f,  1.0f, 0.0f,  // Top-left

    // Grass (Quad)
    -1.0f, -1.0f, 0.0f,  // Bottom-left
     1.0f, -1.0f, 0.0f,  // Bottom-right
     1.0f,  0.0f, 0.0f,  // Top-right
    -1.0f,  0.0f, 0.0f,  // Top-left

    // Cloud 1 (Rectangle)
    -0.6f,  0.7f, 0.0f,  // Bottom-left
    -0.4f,  0.7f, 0.0f,  // Bottom-right
    -0.4f,  0.8f, 0.0f,  // Top-right
    -0.6f,  0.8f, 0.0f,  // Top-left

    // Cloud 2 (Rectangle)
     0.0f,  0.75f, 0.0f, // Bottom-left
     0.3f,  0.75f, 0.0f, // Bottom-right
     0.3f,  0.85f, 0.0f, // Top-right
     0.0f,  0.85f, 0.0f, // Top-left
};

GLfloat colorsBG[] = {
    // Sky (Quad)
    0.5f, 0.8f, 1.0f,	// Bottom-left
    0.5f, 0.8f, 1.0f,	// Bottom-right
	0.5f, 0.8f, 1.0f,	// Top-right
    0.5f, 0.8f, 1.0f,	// Top-left

    // Grass (Quad)
    0.3f, 0.9f, 0.3f,	// Bottom-left
    0.3f, 0.9f, 0.3f,	// Bottom-right
    0.3f, 0.9f, 0.3f,	// Top-right
    0.3f, 0.9f, 0.3f,	// Top-left

    // Cloud 1 (Rectangle)
    1.0f, 1.0f, 1.0f,  	// Bottom-left
    1.0f, 1.0f, 1.0f,  	// Bottom-right
    1.0f, 1.0f, 1.0f,  	// Top-right
    1.0f, 1.0f, 1.0f,  	// Top-left

    // Cloud 2 (Rectangle)
    1.0f, 1.0f, 1.0f, 	// Bottom-left
    1.0f, 1.0f, 1.0f, 	// Bottom-right
    1.0f, 1.0f, 1.0f, 	// Top-right
    1.0f, 1.0f, 1.0f, 	// Top-left
};

void renderSky() {
		
	if (isRenderSkyDisplayed){
		glGenBuffers(1,&VBOstoredVertexID);
		glBindBuffer(GL_ARRAY_BUFFER,VBOstoredVertexID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBG), verticesBG, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
		glGenBuffers(1,&VBOstoredColorsID);
		glBindBuffer(GL_ARRAY_BUFFER,VBOstoredColorsID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colorsBG), colorsBG, GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
		glPointSize(20.0f);
	
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
	
		glVertexPointer(3,GL_FLOAT,0,0);
		glColorPointer(3,GL_FLOAT,0,0);
		
		isRenderSkyDisplayed= false;
	}
	
	glDrawArrays(GL_QUADS, 0, 4);
	glDrawArrays(GL_QUADS, 4, 4);
    glDrawArrays(GL_QUADS, 8, 4);
    glDrawArrays(GL_QUADS, 12, 4);

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	renderSky();
	glFlush();

}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Teletubbies Background using VBO");

    // Initialize GLEW
    glewInit();

    // Register display callback
    glutDisplayFunc(display);

    // Enter the main loop
    glutMainLoop();
    return 0;
}

