/****************************************************
 * 2016-2022 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * PLEASE NOTE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#include <ctime>
#include <vector>
#include "defs.h"
#include "utilities.h"
#include "framebuffer.h"
#include "colorandmaterials.h"
#include "rasterization.h"
#include "io.h"

FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

void render() {
	frameBuffer.clearColorBuffer();
	drawLine(frameBuffer, 0, 0, 100, 100, red);
	drawLine(frameBuffer, 100, 100, 200, 100, blue);
	frameBuffer.showColorBuffer();
}

void resize(int width, int height) {
	frameBuffer.setFrameBufferSize(width, height);
	glutPostRedisplay();
}

// compute the hypotenuse of two numbers
double hypot(double a, double b) {
    return sqrt(a*a + b*b);
}

void f(int &v) {
    v++;
}

// change both values to the maximum value
void makeMax(int &a, int &b) {
    if(a > b) {
        b = a;
    }
    else {
        a = b;
    }
}

int main(int argc, char* argv[]) {

    // This is where you will do your testing of the functions
            // you implement in utilities.cpp
    double rad = PI;
    double x = 0;
    double y = 0;
    pointOnUnitCircle(rad, x, y);
        std::cout << x << " " << y << std::endl;

	return 0;
}
