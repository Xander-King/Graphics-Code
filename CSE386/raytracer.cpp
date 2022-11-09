/****************************************************
 * 2016-2022 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * PLEASE NOTE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/
#include "raytracer.h"
#include "ishape.h"
#include "io.h"

 /**
  * @fn	RayTracer::RayTracer(const color &defa)
  * @brief	Constructs a raytracers.
  * @param	defa	The clear color.
  */

RayTracer::RayTracer(const color& defa)
	: defaultColor(defa) {
}

/**
 * @fn	void RayTracer::raytraceScene(FrameBuffer &frameBuffer, int depth, const IScene &theScene) const
 * @brief	Raytrace scene
 * @param [in,out]	frameBuffer	Framebuffer.
 * @param 		  	depth	   	The current depth of recursion.
 * @param 		  	theScene   	The scene.
 */

//This is where the color math calculations happen.
void RayTracer::raytraceScene(FrameBuffer& frameBuffer, int depth,
	const IScene& theScene) const {
	const RaytracingCamera& camera = *theScene.camera;
	const vector<VisibleIShapePtr>& objs = theScene.opaqueObjs; // all our non-transparent objects
	const vector<PositionalLightPtr>& lights = theScene.lights;

    // frameBuffer is our pixels we want to show
    // looping through each pixel in the frame buffer
	for (int y = 0; y < frameBuffer.getWindowHeight(); ++y) {
		for (int x = 0; x < frameBuffer.getWindowWidth(); ++x) {
            // This is where we can debug a particular ray for a particular pixel.
            // Set a breakpoint on the cout line below
            // Right-click on a "problem pixel"
            // If you need to make the rendering window re-render (press space bar or click // the window)
			DEBUG_PIXEL = (x == xDebug && y == yDebug);
			if (DEBUG_PIXEL) {
				cout << "";
			}
			/* CSE 386 - todo  */
            Ray ray = camera.getRay(x, y); //get the ray for the pixel at (x,y)

            OpaqueHitRecord theHit;
            VisibleIShape::findIntersection(ray, theScene.opaqueObjs, theHit);
            
            // need to set the color based on the shape we hit
            color c;
            
            // when the above is done loop through all the shapes,
            // hitRecord will have the information about t, interceptPt, normal,
            // material, and texture.
            if(theHit.t < FLT_MAX) {
                for(auto l: lights) {
                c +=  l -> illuminate(theHit.interceptPt, theHit.normal, theHit.material, camera.getFrame(), l -> pointIsInAShadow(theHit.interceptPt, theHit.normal, objs, camera.getFrame()));
                    
                }
                if (c.x > 1) {
                    c.x = 1;
                }
                if (c.y > 1) {
                    c.y = 1;
                }
                if (c.z > 1) {
                    c.z = 1;
                }
            } else {
                c = defaultColor;
        }
            frameBuffer.setColor(x, y, c);
            frameBuffer.showAxes(x, y, ray, 0.25);
            
            
//			const VisibleIShape& firstVisibleShape = *theScene.opaqueObjs[0];
//			const IShape& firstShape = *firstVisibleShape.shape;
//			OpaqueHitRecord hit;
//			firstShape.findClosestIntersection(ray, hit);
////			if (hit.t != FLT_MAX) {
////				hit.material = firstVisibleShape.material;
////				color C = hit.material.diffuse;
////				frameBuffer.setColor(x, y, C);
////			}
//			frameBuffer.showAxes(x, y, ray, 0.25);
            
            // Displays R/x, G/y, B/z axes
		}
	}

	frameBuffer.showColorBuffer();
}

/**
 * @fn	color RayTracer::traceIndividualRay(const Ray &ray,
 *											const IScene &theScene,
 *											int recursionLevel) const
 * @brief	Trace an individual ray.
 * @param	ray			  	The ray.
 * @param	theScene	  	The scene.
 * @param	recursionLevel	The recursion level.
 * @return	The color to be displayed as a result of this ray.
 */

color RayTracer::traceIndividualRay(const Ray& ray, const IScene& theScene, int recursionLevel) const {
	/* CSE 386 - todo  */
	// This might be a useful helper function.
	return black;
}
