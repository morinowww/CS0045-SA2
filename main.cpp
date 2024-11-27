#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>

// Prototypes
void generateCircleVertices();

// VBO variables
GLuint VBOstoredVerticesID;
GLuint VBOstoredColorsID;
bool isRenderDisplayed = false;


// Translate variables
bool tinky_winky_translateR = true;
float tinky_winky_translateValX = 0.00f;
float tinky_winky_translateValY = 0.00f;
float po_translateVal = 0.0f;
float lala_translateVal = 1.0f;
float dipsy_translateVal = 0.0f;

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); 
    glMatrixMode(GL_MODELVIEW);
}

spinDipsy_left(){
	dipsy_translateVal += 1.0f;
}
spinDipsy_right(){
	dipsy_translateVal -= 1.0f;
}

void idle_2000(int value){
	if (tinky_winky_translateValX == 0.050f)
		tinky_winky_translateR = false;
	else if (tinky_winky_translateValX == -0.050f)
		tinky_winky_translateR = true;
		
    if (tinky_winky_translateR){
		tinky_winky_translateValX += 0.010;
		tinky_winky_translateValY += 0.005;
	}
	else if (!tinky_winky_translateR){
		tinky_winky_translateValX -= 0.010;
		tinky_winky_translateValY -= 0.005;
	}
    glutPostRedisplay();
    glutTimerFunc(2000, idle_2000, 0);
}

void idle_500(int value){
	po_translateVal += 1.0f;
    if (po_translateVal > 360.0f) 
		po_translateVal -= 360.0f;

    glutPostRedisplay();
    glutTimerFunc(500, idle_500, 0);
}

void mouseWheel(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON)
		spinDipsy_left();
	else if (button == GLUT_RIGHT_BUTTON)
		spinDipsy_right();
	else if (button == 3) 
        lala_translateVal += 0.1f; 
    else {
        lala_translateVal -= 0.1f;
        if (lala_translateVal < 0.1f) 
			lala_translateVal = 0.1f; 
    }
    glutPostRedisplay(); 
}

GLfloat verticesVBO[] = {
	// BG: Sky (Quad)
    -1.0f,  0.0f, 0.0f,  	// Bottom-left
    1.0f,  0.0f, 0.0f,  	// Bottom-right
	1.0f,  1.0f, 0.0f,  	// Top-right
    -1.0f,  1.0f, 0.0f,  	// Top-left

    // BG: Grass (Quad)
    -1.0f, -1.0f, 0.0f,  	// Bottom-left
    1.0f, -1.0f, 0.0f,  	// Bottom-right
    1.0f,  0.50f, 0.0f,  	// Top-right
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

	//Po: Head (Antenna)
	-0.54f, 0.48f, 0.0f,        // 0°
	-0.5472f, 0.5118f, 0.0f,    // 22.5°
	-0.55758f, 0.52242f, 0.0f,  // 45°
	-0.5682f, 0.5322f, 0.0f,    // 67.5°
	-0.6f, 0.54f, 0.0f,         // 90°
	-0.6312f, 0.5322f, 0.0f,    // 112.5°
	-0.64242f, 0.52242f, 0.0f,  // 135°
	-0.6522f, 0.5118f, 0.0f,    // 157.5°
	-0.66f, 0.48f, 0.0f,        // 180°
	-0.6522f, 0.4482f, 0.0f,    // 202.5°
	-0.64242f, 0.43758f, 0.0f,  // 225°
	-0.6312f, 0.4278f, 0.0f,    // 247.5°
	-0.6f, 0.42f, 0.0f,         // 270°
	-0.5682f, 0.4278f, 0.0f,    // 292.5°
	-0.55758f, 0.43758f, 0.0f,  // 315°
	-0.5472f, 0.4482f, 0.0f,    // 337.5°
	-0.6f, 0.42f, 0.0f,			// Atenna Line
	-0.6f, 0.40f, 0.0f,			// Antenna Line
	//Po: Head
    -0.50f, 0.30f, 0.0f,    	// 0°
    -0.512f, 0.353f, 0.0f,  	// 22.5°
    -0.5293f, 0.3707f, 0.0f, 	// 45°
    -0.547f, 0.387f, 0.0f,   	// 67.5°
    -0.60f, 0.40f, 0.0f,     	// 90°
    -0.652f, 0.387f, 0.0f,   	// 112.5°
    -0.6707f, 0.3707f, 0.0f, 	// 135°
    -0.687f, 0.353f, 0.0f,   	// 157.5°
    -0.70f, 0.30f, 0.0f,     	// 180°
    -0.687f, 0.247f, 0.0f,   	// 202.5°
    -0.6707f, 0.2293f, 0.0f, 	// 225°
    -0.652f, 0.213f, 0.0f,   	// 247.5°
    -0.60f, 0.20f, 0.0f,     	// 270°
    -0.547f, 0.213f, 0.0f,   	// 292.5°
    -0.5293f, 0.2293f, 0.0f, 	// 315°
    -0.512f, 0.247f, 0.0f,   	// 337.5°
    //Po: Head (Internal)
	-0.510f, 0.300f, 0.0f,      // 0°
	-0.521f, 0.348f, 0.0f,      // 22.5°
	-0.536f, 0.364f, 0.0f,      // 45°
	-0.552f, 0.378f, 0.0f,      // 67.5°
	-0.600f, 0.390f, 0.0f,      // 90°
	-0.647f, 0.378f, 0.0f,      // 112.5°
	-0.664f, 0.364f, 0.0f,      // 135°
	-0.678f, 0.348f, 0.0f,      // 157.5°
	-0.690f, 0.300f, 0.0f,      // 180°
	-0.678f, 0.252f, 0.0f,      // 202.5°
	-0.664f, 0.236f, 0.0f,      // 225°
	-0.647f, 0.222f, 0.0f,      // 247.5°
	-0.600f, 0.210f, 0.0f,      // 270°
	-0.552f, 0.222f, 0.0f,      // 292.5°
	-0.536f, 0.236f, 0.0f,      // 315°
	-0.521f, 0.252f, 0.0f,      // 337.5°
	//Po: Body
	-0.70f, 0.20f, 0.0f,		// Top-left
	-0.65f, 0.23f, 0.0f,
	-0.55f, 0.23f, 0.0f,
	-0.50f, 0.20f, 0.0f,		// Top-right
	-0.50f, -0.20f, 0.0f,		// Bottom-right
	-0.70f, -0.20f, 0.0f,		// Bottom-left		
	//Po: Body (Internal)
	-0.65f, 0.0f, 0.0f,			// Top-left
	-0.55f, 0.0f, 0.0f,			// Top-right
	-0.55f, -0.10f, 0.0f,		// Bottom-right
	-0.65f, -0.10f, 0.0f,		// Bottom-left	
	//Po: Arm (Left)
	-0.75f, 0.18f, 0.0f,		// Top-left
	-0.70f, 0.20f, 0.0f,		// Top-right
	-0.70f, 0.15f, 0.0f,
	-0.71f, -0.20f, 0.0f,		// Bottom-right
	-0.76f, -0.20f, 0.0f,		// Bottom-left
	//Po: Arm (Right)
	-0.50f, 0.15, 0.0f,
	-0.50f, 0.20f, 0.0f,		// Top-left
	-0.45f, 0.18f, 0.0f,		// Top-right
	-0.44f, -0.20f, 0.0f,		// Bottom-right
	-0.49f, -0.20f, 0.0f,		// Bottom-left
	//Po: Leg (Left)
	-0.70f, -0.20f, 0.0f,		// Top-left
	-0.60f, -0.20f, 0.0f,		// Top-right
	-0.62f, -0.50f, 0.0f,		// Bottom-right
	-0.72f, -0.50f, 0.0f,		// Bottom-left
	//Po: Leg (Right)
	-0.60f, -0.20f, 0.0f,		// Top-left
	-0.50f, -0.20f, 0.0f,		// Top-right
	-0.48f, -0.50f, 0.0f,		// Bottom-right
	-0.58f, -0.50f, 0.0f,		// Bottom-left
	
	
	//Lala: Head (Antenna)
	-0.20f, 0.40f, 0.f,
	-0.18f, 0.47f, 0.f,
	-0.22f, 0.50, 0.0f,
	-0.20, 0.54f, 0.0f,
	//Lala: Head
    -0.10f, 0.30f, 0.0f,    	// 0°
    -0.112f, 0.353f, 0.0f,  	// 22.5°
    -0.1293f, 0.3707f, 0.0f, 	// 45°
    -0.147f, 0.387f, 0.0f,   	// 67.5°
    -0.20f, 0.40f, 0.0f,     	// 90°
    -0.252f, 0.387f, 0.0f,   	// 112.5°
    -0.2707f, 0.3707f, 0.0f, 	// 135°
    -0.287f, 0.353f, 0.0f,   	// 157.5°
    -0.30f, 0.30f, 0.0f,     	// 180°
    -0.287f, 0.247f, 0.0f,   	// 202.5°
    -0.2707f, 0.2293f, 0.0f, 	// 225°
    -0.252f, 0.213f, 0.0f,   	// 247.5°
    -0.20f, 0.20f, 0.0f,     	// 270°
    -0.147f, 0.213f, 0.0f,   	// 292.5°
    -0.1293f, 0.2293f, 0.0f, 	// 315°
    -0.112f, 0.247f, 0.0f,   	// 337.5°
    //Lala: Head (Internal)
	-0.110f, 0.300f, 0.0f,      // 0°
	-0.121f, 0.348f, 0.0f,      // 22.5°
	-0.136f, 0.364f, 0.0f,      // 45°
	-0.152f, 0.378f, 0.0f,      // 67.5°
	-0.200f, 0.390f, 0.0f,      // 90°
	-0.247f, 0.378f, 0.0f,      // 112.5°
	-0.264f, 0.364f, 0.0f,      // 135°
	-0.278f, 0.348f, 0.0f,      // 157.5°
	-0.290f, 0.300f, 0.0f,      // 180°
	-0.278f, 0.252f, 0.0f,      // 202.5°
	-0.264f, 0.236f, 0.0f,      // 225°
	-0.247f, 0.222f, 0.0f,      // 247.5°
	-0.200f, 0.210f, 0.0f,      // 270°
	-0.152f, 0.222f, 0.0f,      // 292.5°
	-0.136f, 0.236f, 0.0f,      // 315°
	-0.121f, 0.252f, 0.0f,      // 337.5°
	//Lala: Body
	-0.30f, 0.20f, 0.0f,		// Top-left
	-0.25f, 0.23f, 0.0f,
	-0.15f, 0.23f, 0.0f,
	-0.10f, 0.20f, 0.0f,		// Top-right
	-0.10f, -0.20f, 0.0f,		// Bottom-right
	-0.30f, -0.20f, 0.0f,		// Bottom-left		
	//Lala: Body (Internal)
	-0.25f, 0.0f, 0.0f,			// Top-left
	-0.15f, 0.0f, 0.0f,			// Top-right
	-0.15f, -0.10f, 0.0f,		// Bottom-right
	-0.25f, -0.10f, 0.0f,		// Bottom-left	
	//Lala: Arm (Left)
	-0.35f, 0.18f, 0.0f,		// Top-left
	-0.30f, 0.20f, 0.0f,		// Top-right
	-0.30f, 0.15f, 0.0f,
	-0.31f, -0.20f, 0.0f,		// Bottom-right
	-0.36f, -0.20f, 0.0f,		// Bottom-left
	//Lala: Arm (Right)
	-0.10f, 0.15, 0.0f,
	-0.10f, 0.20f, 0.0f,		// Top-left
	-0.05f, 0.18f, 0.0f,		// Top-right
	-0.04f, -0.20f, 0.0f,		// Bottom-right
	-0.09f, -0.20f, 0.0f,		// Bottom-left
	//Lala: Leg (Left)
	-0.30f, -0.20f, 0.0f,		// Top-left
	-0.20f, -0.20f, 0.0f,		// Top-right
	-0.22f, -0.50f, 0.0f,		// Bottom-right
	-0.32f, -0.50f, 0.0f,		// Bottom-left
	//Lala: Leg (Right)
	-0.20f, -0.20f, 0.0f,		// Top-left
	-0.10f, -0.20f, 0.0f,		// Top-right
	-0.08f, -0.50f, 0.0f,		// Bottom-right
	-0.18f, -0.50f, 0.0f,		// Bottom-left
	
	
	//Dipsy: Head (Antenna)
	0.20f, 0.40f, 0.f,
	0.20, 0.54f, 0.0f,
	//Dipsy: Head
    0.30f, 0.30f, 0.0f,    		// 0°
    0.288f, 0.353f, 0.0f,	  	// 22.5°
    0.2707f, 0.3707f, 0.0f, 	// 45°
    0.253f, 0.387f, 0.0f,   	// 67.5°
    0.20f, 0.40f, 0.0f,     	// 90°
    0.148f, 0.387f, 0.0f,   	// 112.5°
    0.1293f, 0.3707f, 0.0f, 	// 135°
    0.113f, 0.353f, 0.0f,   	// 157.5°
    0.10f, 0.30f, 0.0f,     	// 180°
    0.113f, 0.247f, 0.0f,   	// 202.5°
    0.1293f, 0.2293f, 0.0f, 	// 225°
    0.148f, 0.213f, 0.0f,   	// 247.5°
    0.20f, 0.20f, 0.0f,     	// 270°
    0.253f, 0.213f, 0.0f,   	// 292.5°
    0.2707f, 0.2293f, 0.0f, 	// 315°
    0.288f, 0.247f, 0.0f,   	// 337.5°
    //Dipsy: Head (Internal)
	0.110f, 0.300f, 0.0f,      // 0°
	0.121f, 0.348f, 0.0f,      // 22.5°
	0.136f, 0.364f, 0.0f,      // 45°
	0.152f, 0.378f, 0.0f,      // 67.5°
	0.200f, 0.390f, 0.0f,      // 90°
	0.247f, 0.378f, 0.0f,      // 112.5°
	0.264f, 0.364f, 0.0f,      // 135°
	0.278f, 0.348f, 0.0f,      // 157.5°
	0.290f, 0.300f, 0.0f,      // 180°
	0.278f, 0.252f, 0.0f,      // 202.5°
	0.264f, 0.236f, 0.0f,      // 225°
	0.247f, 0.222f, 0.0f,      // 247.5°
	0.200f, 0.210f, 0.0f,      // 270°
	0.152f, 0.222f, 0.0f,      // 292.5°
	0.136f, 0.236f, 0.0f,      // 315°
	0.121f, 0.252f, 0.0f,      // 337.5°
	//Dipsy: Body
	0.10f, 0.20f, 0.0f,			// Top-left
	0.15f, 0.23f, 0.0f,
	0.25f, 0.23f, 0.0f,
	0.30f, 0.20f, 0.0f,			// Top-right
	0.30f, -0.20f, 0.0f,		// Bottom-right
	0.10f, -0.20f, 0.0f,		// Bottom-left		
	//Dipsy: Body (Internal)
	0.15f, 0.0f, 0.0f,			// Top-left
	0.25f, 0.0f, 0.0f,			// Top-right
	0.25f, -0.10f, 0.0f,		// Bottom-right
	0.15f, -0.10f, 0.0f,		// Bottom-left	
	//Dipsy: Arm (Left)
	0.05f, 0.18f, 0.0f,			// Top-left
	0.10f, 0.20f, 0.0f,			// Top-right
	0.10f, 0.15f, 0.0f,
	0.09f, -0.20f, 0.0f,		// Bottom-right
	0.04f, -0.20f, 0.0f,		// Bottom-left
	//Dipsy: Arm (Right)
	0.30f, 0.15, 0.0f,
	0.30f, 0.20f, 0.0f,			// Top-left
	0.35f, 0.18f, 0.0f,			// Top-right
	0.36f, -0.20f, 0.0f,		// Bottom-right
	0.31f, -0.20f, 0.0f,		// Bottom-left
	//Dipsy: Leg (Left)
	0.10f, -0.20f, 0.0f,		// Top-left
	0.20f, -0.20f, 0.0f,		// Top-right
	0.18f, -0.50f, 0.0f,		// Bottom-right
	0.08f, -0.50f, 0.0f,		// Bottom-left
	//Dipsy: Leg (Right)
	0.20f, -0.20f, 0.0f,		// Top-left
	0.30f, -0.20f, 0.0f,		// Top-right
	0.32f, -0.50f, 0.0f,		// Bottom-right
	0.22f, -0.50f, 0.0f,		// Bottom-left

	//Tinky-Winky: Head (Antenna)
	0.55f, 0.55f, 0.0f,
	0.65f, 0.55f, 0.0f,
	0.60f, 0.45f, 0.0f,
	0.60f, 0.45f, 0.0f,
	0.60f, 0.35f, 0.0f,
	0.60f, 0.30f, 0.0f,
	//Tinky-Winky: Head
    0.70f, 0.30f, 0.0f,    		// 0°
    0.688f, 0.353f, 0.0f,	  	// 22.5°
    0.6707f, 0.3707f, 0.0f, 	// 45°
    0.653f, 0.387f, 0.0f,   	// 67.5°
    0.60f, 0.40f, 0.0f,     	// 90°
    0.548f, 0.387f, 0.0f,   	// 112.5°
    0.5293f, 0.3707f, 0.0f, 	// 135°
    0.513f, 0.353f, 0.0f,   	// 157.5°
    0.50f, 0.30f, 0.0f,     	// 180°
    0.513f, 0.247f, 0.0f,   	// 202.5°
    0.5293f, 0.2293f, 0.0f, 	// 225°
    0.548f, 0.213f, 0.0f,   	// 247.5°
    0.60f, 0.20f, 0.0f,     	// 270°
    0.653f, 0.213f, 0.0f,   	// 292.5°
    0.6707f, 0.2293f, 0.0f, 	// 315°
    0.688f, 0.247f, 0.0f,   	// 337.5°
    //Tinky-Winky: Head (Internal)
	0.510f, 0.300f, 0.0f,      // 0°
	0.521f, 0.348f, 0.0f,      // 22.5°
	0.536f, 0.364f, 0.0f,      // 45°
	0.552f, 0.378f, 0.0f,      // 67.5°
	0.600f, 0.390f, 0.0f,      // 90°
	0.647f, 0.378f, 0.0f,      // 112.5°
	0.664f, 0.364f, 0.0f,      // 135°
	0.678f, 0.348f, 0.0f,      // 157.5°
	0.690f, 0.300f, 0.0f,      // 180°
	0.678f, 0.252f, 0.0f,      // 202.5°
	0.664f, 0.236f, 0.0f,      // 225°
	0.647f, 0.222f, 0.0f,      // 247.5°
	0.600f, 0.210f, 0.0f,      // 270°
	0.552f, 0.222f, 0.0f,      // 292.5°
	0.536f, 0.236f, 0.0f,      // 315°
	0.521f, 0.252f, 0.0f,      // 337.5°
	//Tinky-Winky: Body
	0.50f, 0.20f, 0.0f,			// Top-left
	0.55f, 0.23f, 0.0f,
	0.65f, 0.23f, 0.0f,
	0.70f, 0.20f, 0.0f,			// Top-right
	0.70f, -0.20f, 0.0f,		// Bottom-right
	0.50f, -0.20f, 0.0f,		// Bottom-left		
	//Tinky-Winky: Body (Internal)
	0.55f, 0.0f, 0.0f,			// Top-left
	0.65f, 0.0f, 0.0f,			// Top-right
	0.65f, -0.10f, 0.0f,		// Bottom-right
	0.55f, -0.10f, 0.0f,		// Bottom-left	
	//Tinky-Winky: Arm (Left)
	0.45f, 0.18f, 0.0f,			// Top-left
	0.50f, 0.20f, 0.0f,			// Top-right
	0.50f, 0.15f, 0.0f,
	0.49f, -0.20f, 0.0f,		// Bottom-right
	0.44f, -0.20f, 0.0f,		// Bottom-left
	//Tinky-Winky: Arm (Right)
	0.70f, 0.15, 0.0f,
	0.70f, 0.20f, 0.0f,			// Top-left
	0.75f, 0.18f, 0.0f,			// Top-right
	0.76f, -0.20f, 0.0f,		// Bottom-right
	0.71f, -0.20f, 0.0f,		// Bottom-left
	//Tinky-Winky: Leg (Left)
	0.50f, -0.20f, 0.0f,		// Top-left
	0.60f, -0.20f, 0.0f,		// Top-right
	0.58f, -0.50f, 0.0f,		// Bottom-right
	0.48f, -0.50f, 0.0f,		// Bottom-left
	//Tinky-Winky: Leg (Right)
	0.60f, -0.20f, 0.0f,		// Top-left
	0.70f, -0.20f, 0.0f,		// Top-right
	0.72f, -0.50f, 0.0f,		// Bottom-right
	0.62f, -0.50f, 0.0f,		// Bottom-left
	
	//Sun Baby
	0.98f, 0.6786f, 0.0f,      // 0°
	0.9629f, 0.7540f, 0.0f,    // 22.5°
	0.9381f, 0.7801f, 0.0f,    // 45°
	0.9037f, 0.8029f, 0.0f,    // 67.5°
	0.8271f, 0.8214f, 0.0f,    // 90°
	0.7529f, 0.8029f, 0.0f,    // 112.5°
	0.7253f, 0.7801f, 0.0f,    // 135°
	0.7014f, 0.7540f, 0.0f,    // 157.5°
	0.6843f, 0.6786f, 0.0f,    // 180°
	0.7014f, 0.6026f, 0.0f,    // 202.5°
	0.7253f, 0.5764f, 0.0f,    // 225°
	0.7529f, 0.5540f, 0.0f,    // 247.5°
	0.8271f, 0.5357f, 0.0f,    // 270°
	0.9137f, 0.5540f, 0.0f,    // 292.5°
	0.9281f, 0.5764f, 0.0f,    // 315°
	0.9529f, 0.6026f, 0.0f,    // 337.5°
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

    //Po: Head (Antenna)
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
    1.0f, 0.0f, 0.0f,  	// Antenna
    1.0f, 0.0f, 0.0f,  	// Antenna
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
    //Po: Head (Internal)
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    //Po: Body
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
	//Po: Body (Internal)
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
    //Po: Arm (Left)
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    //Po: Body (Right)
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    //Po: Leg (Left)
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    //Po: Leg (Right)
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,

    
	//Lala: Head (Antenna)
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
    //Lala: Head
    1.0f, 1.0f, 0.0f,	// 0°
    1.0f, 1.0f, 0.0f,  	// 22.5°
    1.0f, 1.0f, 0.0f, 	// 45°
    1.0f, 1.0f, 0.0f,  	// 67.5°
    1.0f, 1.0f, 0.0f, 	// 90°
    1.0f, 1.0f, 0.0f,  	// 112.5°
    1.0f, 1.0f, 0.0f, 	// 135°
    1.0f, 1.0f, 0.0f,  	// 157.5°
    1.0f, 1.0f, 0.0f, 	// 180°
    1.0f, 1.0f, 0.0f,  	// 202.5°
    1.0f, 1.0f, 0.0f, 	// 225°
    1.0f, 1.0f, 0.0f,  	// 247.5°
    1.0f, 1.0f, 0.0f,   // 270°
    1.0f, 1.0f, 0.0f,  	// 292.5°
    1.0f, 1.0f, 0.0f, 	// 315°
    1.0f, 1.0f, 0.0f,  	// 337.5°
    //Lala: Head (Internal)
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    //Lala: Body
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
	//Lala: Body (Internal)
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
    //Lala: Arm (Left)
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    //Lala: Body (Right)
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    //Lala: Leg (Left)
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    //Lala: Leg (Right)
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    
    
	//Dipsy: Head (Antenna)
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
    //Dipsy: Head
    0.0f, 1.0f, 0.0f,	// 0°
    0.0f, 1.0f, 0.0f,  	// 22.5°
    0.0f, 1.0f, 0.0f, 	// 45°
    0.0f, 1.0f, 0.0f,  	// 67.5°
    0.0f, 1.0f, 0.0f, 	// 90°
    0.0f, 1.0f, 0.0f,  	// 112.5°
    0.0f, 1.0f, 0.0f, 	// 135°
    0.0f, 1.0f, 0.0f,  	// 157.5°
    0.0f, 1.0f, 0.0f, 	// 180°
    0.0f, 1.0f, 0.0f,  	// 202.5°
    0.0f, 1.0f, 0.0f, 	// 225°
    0.0f, 1.0f, 0.0f,  	// 247.5°
    0.0f, 1.0f, 0.0f,   // 270°
    0.0f, 1.0f, 0.0f,  	// 292.5°
    0.0f, 1.0f, 0.0f, 	// 315°
    0.0f, 1.0f, 0.0f,  	// 337.5°
    //Dipsy: Head (Internal)
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    //Dipsy: Body
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
   	//Dipsy: Body (Internal)
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
    //Dipsy: Arm (Left)
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    //Dipsy: Body (Right)
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    //Dipsy: Leg (Left)
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    //Dipsy: Leg (Right)
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    
    
	//Tink-Wink: Head (Antenna)
	0.5f, 0.0f, 1.0f,
	0.5f, 0.0f, 1.0f,
	0.5f, 0.0f, 1.0f,
	0.5f, 0.0f, 1.0f,
	0.5f, 0.0f, 1.0f,
	0.5f, 0.0f, 1.0f,
    //Tink-Winky: Head
    0.5f, 0.0f, 1.0f,	// 0°
    0.5f, 0.0f, 1.0f,  	// 22.5°
    0.5f, 0.0f, 1.0f, 	// 45°
    0.5f, 0.0f, 1.0f,  	// 67.5°
    0.5f, 0.0f, 1.0f, 	// 90°
    0.5f, 0.0f, 1.0f,  	// 112.5°
    0.5f, 0.0f, 1.0f, 	// 135°
    0.5f, 0.0f, 1.0f,  	// 157.5°
    0.5f, 0.0f, 1.0f, 	// 180°
    0.5f, 0.0f, 1.0f,  	// 202.5°
    0.5f, 0.0f, 1.0f, 	// 225°
    0.5f, 0.0f, 1.0f,  	// 247.5°
    0.5f, 0.0f, 1.0f,   // 270°
    0.5f, 0.0f, 1.0f,  	// 292.5°
    0.5f, 0.0f, 1.0f, 	// 315°
    0.5f, 0.0f, 1.0f,  	// 337.5°
    //Tink-Winky: Head (Internal)
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    1.0f, 0.89f, 0.70f,
    //Tink-Winky: Body
    0.5f, 0.0f, 1.0f,
    0.5f, 0.0f, 1.0f,
    0.5f, 0.0f, 1.0f,
    0.5f, 0.0f, 1.0f,
    0.5f, 0.0f, 1.0f,
    0.5f, 0.0f, 1.0f,
   	//Tink-Winky: Body (Internal)
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
    //Tink-Winky: Arm (Left)
    0.5f, 0.0f, 1.0f,
    0.5f, 0.0f, 1.0f,
    0.5f, 0.0f, 1.0f,
    0.5f, 0.0f, 1.0f,
    0.5f, 0.0f, 1.0f,
    //Tink-Winky: Body (Right)
    0.5f, 0.0f, 1.0f,
    0.5f, 0.0f, 1.0f,
    0.5f, 0.0f, 1.0f,
    0.5f, 0.0f, 1.0f,
    0.5f, 0.0f, 1.0f,
    //Tink-Winky: Leg (Left)
    0.5f, 0.0f, 1.0f,
    0.5f, 0.0f, 1.0f,
    0.5f, 0.0f, 1.0f,
    0.5f, 0.0f, 1.0f,
    //Tink-Winky: Leg (Right)
    0.5f, 0.0f, 1.0f,
    0.5f, 0.0f, 1.0f,
    0.5f, 0.0f, 1.0f,
    0.5f, 0.0f, 1.0f,
    
    //Sun Baby
    1.0f, 1.0f, 0.0f,	// 0°
    1.0f, 1.0f, 0.0f,  	// 22.5°
    1.0f, 1.0f, 0.0f, 	// 45°
    1.0f, 1.0f, 0.0f,  	// 67.5°
    1.0f, 1.0f, 0.0f, 	// 90°
    1.0f, 1.0f, 0.0f,  	// 112.5°
    1.0f, 1.0f, 0.0f, 	// 135°
    1.0f, 1.0f, 0.0f,  	// 157.5°
    1.0f, 1.0f, 0.0f, 	// 180°
    1.0f, 1.0f, 0.0f,  	// 202.5°
    1.0f, 1.0f, 0.0f, 	// 225°
    1.0f, 1.0f, 0.0f,  	// 247.5°
    1.0f, 1.0f, 0.0f,   // 270°
    1.0f, 1.0f, 0.0f,  	// 292.5°
    1.0f, 1.0f, 0.0f, 	// 315°
    1.0f, 1.0f, 0.0f,  	// 337.5°
};

void renderVerticesVBO() {
	
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
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
		
    glLineWidth(5); 						//Set line width (scale to window size)
    
	glDrawArrays(GL_QUADS, 0, 4);			//Draw sky
	glDrawArrays(GL_QUADS, 4, 4);			//Draw grass
	
    glDrawArrays(GL_POLYGON, 286, 16);		//Draw Sun Baby
    
    glDrawArrays(GL_QUADS, 8, 4);			//Draw clouds 1
    glDrawArrays(GL_QUADS, 12, 4);			//Draw clouds 2  

	glPushMatrix();
    glRotatef(po_translateVal, 0.0f, 0.0f, 1.0f); 	
    glDrawArrays(GL_LINE_LOOP, 16, 16);		//Draw Po: Head (Antenna)
    glDrawArrays(GL_LINES, 32, 2);			//Draw Po: Head (Antenna)
    glDrawArrays(GL_POLYGON, 34, 16);		//Draw Po: Head
    glDrawArrays(GL_POLYGON, 50, 16);		//Draw Po: Head (Internal)
    glDrawArrays(GL_POLYGON, 66, 6);		//Draw Po: Body
    glDrawArrays(GL_POLYGON, 72, 4);		//Draw Po: Body (Internal)
    glDrawArrays(GL_POLYGON, 76, 5);		//Draw Po: Arm (Left)
    glDrawArrays(GL_POLYGON, 81, 5);		//Draw Po: Arm (Right)
    glDrawArrays(GL_QUADS, 86, 4);			//Draw Po: Leg (Left)
    glDrawArrays(GL_QUADS, 90, 4);			//Draw Po: Leg (Right)
	glPopMatrix();
	
	glPushMatrix();
    glScalef(lala_translateVal, lala_translateVal, 1.0f);
    glDrawArrays(GL_LINE_STRIP, 94, 4);		//Draw Lala: Head (Antenna)
	glDrawArrays(GL_POLYGON, 98, 16);		//Draw Lala: Head
    glDrawArrays(GL_POLYGON, 114, 16);		//Draw Lala: Head (Internal)
    glDrawArrays(GL_POLYGON, 130, 6);		//Draw Lala: Body
    glDrawArrays(GL_POLYGON, 136, 4);		//Draw Lala: Body (Internal)
    glDrawArrays(GL_POLYGON, 140, 5);		//Draw Lala: Arm (Left)
    glDrawArrays(GL_POLYGON, 145, 5);		//Draw Lala: Arm (Right)
    glDrawArrays(GL_QUADS, 150, 4);			//Draw Lala: Leg (Left)
    glDrawArrays(GL_QUADS, 154, 4);			//Draw Lala: Leg (Right)
	glPopMatrix();

	glPushMatrix();
	glRotatef(dipsy_translateVal, 0.0f, 0.0f, 1.0f);
    glDrawArrays(GL_LINE_STRIP, 158, 2);	//Draw Dipsy: Head (Antenna)
	glDrawArrays(GL_POLYGON, 160, 16);		//Draw Dipsy: Head
    glDrawArrays(GL_POLYGON, 176, 16);		//Draw Dipsy: Head (Internal)
    glDrawArrays(GL_POLYGON, 192, 6);		//Draw Dipsy: Body
    glDrawArrays(GL_POLYGON, 198, 4);		//Draw Dipsy: Body (Internal)
    glDrawArrays(GL_POLYGON, 202, 5);		//Draw Dipsy: Arm (Left)
    glDrawArrays(GL_POLYGON, 207, 5);		//Draw Dipsy: Arm (Right)
    glDrawArrays(GL_QUADS, 212, 4);			//Draw Dipsy: Leg (Left)
    glDrawArrays(GL_QUADS, 216, 4);			//Draw Dipsy: Leg (Right)
    glPopMatrix();

	glPushMatrix();  
	glTranslatef(tinky_winky_translateValX, tinky_winky_translateValY, 0.0f);    
    glDrawArrays(GL_LINE_LOOP, 220, 3);		//Draw Tink-Winky: Head (Antenna)
    glDrawArrays(GL_LINE_STRIP, 223, 3);	//Draw Tink-Winky: Head (Antenna)
	glDrawArrays(GL_POLYGON, 226, 16);		//Draw Tink-Winky: Head
    glDrawArrays(GL_POLYGON, 242, 16);		//Draw Tink-Winky: Head (Internal)
    glDrawArrays(GL_POLYGON, 258, 6);		//Draw Tink-Winky: Body
    glDrawArrays(GL_POLYGON, 264, 4);		//Draw Tink-Winky: Body (Internal)
    glDrawArrays(GL_POLYGON, 268, 5);		//Draw Tink-Winky: Arm (Left)
    glDrawArrays(GL_POLYGON, 273, 5);		//Draw Tink-Winky: Arm (Right)
    glDrawArrays(GL_QUADS, 278, 4);			//Draw Tink-Winky: Leg (Left)
    glDrawArrays(GL_QUADS, 282, 4);			//Draw Tink-Winky: Leg (Right)
	glPopMatrix();
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
    glutReshapeFunc(reshape);
    glutTimerFunc(2000, idle_2000, 0);
    glutTimerFunc(500, idle_500, 0);
    glutMouseFunc(mouseWheel);
    
    // Enter the main loop
    glutMainLoop();
    return 0;
}
