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

// Just here to practice the debugger
// counts how many steps it takes to get from the start number to 10
// if we increase by a given increment
// stepsToTen(6, 1) --> 4
// stepsToTen(8.5, 0.5) --> 3
// stepsToTen(9.0, 0.1) --> 10
int stepsToTen(double start, double inc) {

        int steps = 0;

        while (start != 10) {

                start += inc;

                steps++;

        }

        return steps;

}


int main(int argc, char* argv[]) {
    
    glm::dvec2 point(0, -2);
    
    cout <<  directionInRadians(2,2,2,0) << endl;
    
	return 0;
}
