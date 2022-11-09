/****************************************************
 * 2016-2022 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

//#include <ctime>
//#include "defs.h"
//#include "io.h"
//#include "ishape.h"
//#include "framebuffer.h"
//#include "raytracer.h"
//#include "iscene.h"
//#include "light.h"
//#include "image.h"
//#include "camera.h"
//#include "rasterization.h"
//
//PositionalLightPtr posLight = new PositionalLight(dvec3(10, 10, 10), white);
//vector<PositionalLightPtr> lights = { posLight };
//
//FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);
//RayTracer rayTrace(paleGreen);
//
//dvec3 cameraPos(1, 0, 0);
//dvec3 cameraFocus(0, 0, 0);
//dvec3 cameraUp = Y_AXIS;
//double cameraFOV = PI_2;
//
//IScene scene;
//
//void render() {
//	int frameStartTime = glutGet(GLUT_ELAPSED_TIME);
//	int width = frameBuffer.getWindowWidth();
//	int height = frameBuffer.getWindowHeight();
//
//	//scene.camera = new PerspectiveCamera(cameraPos, cameraFocus, cameraUp, cameraFOV, width, height);
//    scene.camera = new OrthographicCamera(cameraPos, cameraFocus, cameraUp, width, height, 1);
//
//	rayTrace.raytraceScene(frameBuffer, 0, scene);
//
//	int frameEndTime = glutGet(GLUT_ELAPSED_TIME); // Get end time
//	double totalTimeSec = (frameEndTime - frameStartTime) / 1000.0;
//	cout << "Render time: " << totalTimeSec << " sec." << endl;
//}
//
//void resize(int width, int height) {
//	frameBuffer.setFrameBufferSize(width, height);
//	glutPostRedisplay();
//}
//
//void buildScene() {
//    // Mathematical Definitions of Shapes
//    
//	IShape* plane = new IPlane(dvec3(0.0, 0.0, 0.0), dvec3(0.0, 1.0, 0.0)); //point, normal vector
//	ICylinder* cylinder1 = new ICylinder(dvec3(0.0, 8.0, 0.0), 5.0, 10.0, QuadricParameters::cylinderYQParams(1.0));
//    //Center, radius
//	ISphere* sphere2 = new ISphere(dvec3(-2.0, 0.0, -8.0), 2.0);
//	IEllipsoid* ellipsoid = new IEllipsoid(dvec3(4.0, 0.0, 3.0), dvec3(2.0, 1.0, 2.0)); //pos, sizes of axis
//	IDisk* disk = new IDisk(dvec3(15.0, 0.0, 0.0), dvec3(0.0, 0.0, 1.0), 5.0);
//    
//    ICone* cone = new ICone(dvec3(-10.0, 8.0, 0.0), 5.0, 8.0, QuadricParameters::coneYQParams(5.0, 8.0));
//    
//    ICone* cone2 = new ICone(dvec3(10.0, 8.0, 0.0), 5.0, 8.0, QuadricParameters::coneYQParams(5.0, 8.0));
//    
//    //We need atleast one visibleIShape or transparentShape
//    scene.addOpaqueObject(new VisibleIShape(cylinder1, polishedGold));
//	scene.addOpaqueObject(new VisibleIShape(plane, greenRubber));
//	//scene.addOpaqueObject(new VisibleIShape(sphere2, bronze));
//	scene.addOpaqueObject(new VisibleIShape(cone, redPlastic));
//	scene.addOpaqueObject(new VisibleIShape(cone2, cyanPlastic));
//    // loop to make five spheres
////    for (int i = 0; i < 5; i++) {
////        ISphere* sphere1 = new ISphere(dvec3(2 * (i + 1), -5.0, 0.0), 1.0); //Center, radius
////        scene.addOpaqueObject(new VisibleIShape(sphere1, redPlastic));
//
// //   }
//    scene.addLight(new PositionalLight(dvec3(5, 15, 5), white));
//    scene.addLight(new PositionalLight(dvec3(-5, 15, 5), red));
//    scene.addLight(new PositionalLight(dvec3(5, 15, -5), blue));
//    scene.addLight(new PositionalLight(dvec3(-5, 15, -5), green));
//
//}
//int main(int argc, char* argv[]) {
//	graphicsInit(argc, argv, __FILE__);
//
//	glutDisplayFunc(render);
//	glutReshapeFunc(resize);
//	glutKeyboardFunc(keyboardUtility);
//	glutMouseFunc(mouseUtility);
//
//	buildScene();
//
//	glutMainLoop();
//
//	return 0;
//}

