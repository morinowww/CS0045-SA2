#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/glut.h>
#include <cmath>

//Prototypes
void generateCircleVertices(GLfloat * vector_array, GLfloat position_x, GLfloat posiyion_y, GLfloat radius);

// VBO variables
GLuint VBOstoredVertexBGID;
GLuint VBOstoredColorsBGID;
GLuint VBOstoredVertexTB_PoID;
GLuint VBOstoredColorsTB_PoID;
bool isRenderSkyDisplayed = true;
bool isRenderTeletubbiesDisplayed = true;

//Other variables
const int NUM_SEGMENTS = 100; // Number of segments to approximate the circle

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
     
	-0.60f, 0.20f, 0.0f,	//Head bottom-left
	-0.40f, 0.20f, 0.0f,	//Head bottom-right
	-0.40f, 0.40f, 0.0f,	//Head top-right
	-0.60f, 0.40f, 0.0f,	//Head top-left
	
	-0.58f, 0.22f, 0.0f,	//Head interior bottom-left
	-0.42f, 0.22f, 0.0f,	//Head interior bottom-right
	-0.42f, 0.38f, 0.0f,	//Head interior top-right
	-0.58f, 0.38f, 0.0f,	//Head interior top-left
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

	1.0f, 0.0f, 0.0f,		//Head interior bottom-left
	1.0f, 0.0f, 0.0f,		//Head interior bottom-right
	1.0f, 0.0f, 0.0f,		//Head interior top-right
	1.0f, 0.0f, 0.0f,		//Head interior top-left
	
	1.0f, 0.89f, 0.70f,		//Head interior bottom-left
	1.0f, 0.89f, 0.70f,		//Head interior bottom-right
	1.0f, 0.89f, 0.70f,		//Head interior top-right
	1.0f, 0.89f, 0.70f,		//Head interior top-left
};

//Vertex data for Teletubbies
GLfloat verticesTB_PoHead[NUM_SEGMENTS * 3];

GLfloat verticesTB_Po[] = {
	-0.60f, 0.20f, 0.0f,	//Head bottom-left
	-0.40f, 0.20f, 0.0f,	//Head bottom-right
	-0.40f, 0.40f, 0.0f,	//Head top-right
	-0.60f, 0.40f, 0.0f,	//Head top-left
	
	-0.58f, 0.22f, 0.0f,	//Head interior bottom-left
	-0.42f, 0.22f, 0.0f,	//Head interior bottom-right
	-0.42f, 0.38f, 0.0f,	//Head interior top-right
	-0.58f, 0.38f, 0.0f,	//Head interior top-left
};

GLfloat colorsTB_Po[] = {
	1.0f, 0.0f, 0.0f,		//Head interior bottom-left
	1.0f, 0.0f, 0.0f,		//Head interior bottom-right
	1.0f, 0.0f, 0.0f,		//Head interior top-right
	1.0f, 0.0f, 0.0f,		//Head interior top-left
	
	1.0f, 0.89f, 0.70f,		//Head interior bottom-left
	1.0f, 0.89f, 0.70f,		//Head interior bottom-right
	1.0f, 0.89f, 0.70f,		//Head interior top-right
	1.0f, 0.89f, 0.70f,		//Head interior top-left		
};

void renderBG() {
	if (isRenderSkyDisplayed){
		glGenBuffers(1,&VBOstoredVertexBGID);
		glBindBuffer(GL_ARRAY_BUFFER,VBOstoredVertexBGID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBG), verticesBG, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
		glGenBuffers(1,&VBOstoredColorsBGID);
		glBindBuffer(GL_ARRAY_BUFFER,VBOstoredColorsBGID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colorsBG), colorsBG, GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
		glPointSize(20.0f);
	
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
	
		glVertexPointer(3,GL_FLOAT,0,0);
		glColorPointer(3,GL_FLOAT,0,0);
		
		isRenderSkyDisplayed = false;
	}
	
	glDrawArrays(GL_QUADS, 0, 4);	//Draw gky
	glDrawArrays(GL_QUADS, 4, 4);	//Draw grass
    glDrawArrays(GL_QUADS, 8, 4);	//Draw clouds 1
    glDrawArrays(GL_QUADS, 12, 4);	//Draw clouds 2
}

void renderTB_Po(){
	//Render TB face
	if (isRenderTeletubbiesDisplayed){
		glGenBuffers(1,&VBOstoredVertexTB_PoID);
		glBindBuffer(GL_ARRAY_BUFFER,VBOstoredVertexTB_PoID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBG), verticesBG, GL_DYNAMIC_DRAW);
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
		glGenBuffers(1,&VBOstoredColorsTB_PoID);
		glBindBuffer(GL_ARRAY_BUFFER,VBOstoredColorsTB_PoID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colorsBG), colorsBG, GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		
		glPointSize(20.0f);
	
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
	
		glColorPointer(3,GL_FLOAT,0,0);
	}
	
	glDrawArrays(GL_POLYGON, 16, 4);
	glDrawArrays(GL_POLYGON, 20, 4);

	
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	renderBG();
	renderTB_Po();
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

void generateCircleVertices(GLfloat * vector_array, GLfloat position_x, GLfloat position_y, GLfloat radius) {
    float angleStep = 2.0f * 3.14159265359f / NUM_SEGMENTS;  // Angle between each segment

    for (int i = 0; i < NUM_SEGMENTS; i++) {
        float angle = i * angleStep;
        verticesTB_PoHead[i * 3] = position_x + radius * cos(angle);  // X coordinate
        verticesTB_PoHead[i * 3 + 1] = position_y + radius * sin(angle);  // Y coordinate
        verticesTB_PoHead[i * 3 + 2] = 0.0f;  // Z coordinate (flat 2D circle)
    }
}
