#include "ishape.h"
#include "camera.h"
#include "io.h"

// Returns true if the ray intersects the sphere
// Example: a ray with origin (0, 0, 0) and direction (1, 0, 0)
//  would intersect a sphere centered at (10, 0, 0) with radius 5
//  but a ray with origin (0, 0, 0) and direction (0, 1, 0) would not.
bool rayIntersectsSphere(const Ray& ray, const ISphere& sphere) {
    // when calling the findIntersections method, you will need to send
    // a HitRecord array, even though you don't need that array for this
    // particular function (you might need it for other functions). So, here
    // is a line you should keep, and then use the hits variable:
    HitRecord hits[2];
    int hitCount = sphere.findIntersections(ray, hits);
    
    if (hitCount == 0) {
        return false;
    }
    return true;
}

/* Returns true iff at least one of the camera's viewing rays interesects the sphere
   Recall that each pixel in a rendering window has a corresponding viewing ray.
   For example, consider the following two cameras:
 dvec3 camPos(0, 0, 0);
 dvec3 camLookPt(1, 0, 0);
 dvec3 up(0, 1, 0);
 double fov = glm::radians(45.0); // only for perspective cameras
 int scale = 1; // only for orthographic cameras
 int nx = 200;
 int ny = 200;
 
 PerspectiveCamera per(camPos, camLookPt, up, fov, nx, ny);
 OrthographicCamera ort(camPos, camLookPt, up, nx, ny, scale);
 
 Both of these cameras would be able to see a sphere at (20, 0, 0) with radius 5.
 But if you change the camLookPt to (-1, 0, 0), then neither camera would
 be able to see the sphere.
 
 If you put a camera inside a sphere, it should be able to see the sphere
 no matter which direction it is facing.
 
 Consider looping through all pixels to see if any of their corresponding rays
 intersect the sphere.
 
*/
bool cameraSeesSphere(const RaytracingCamera& cam, const ISphere& sphere) {
    HitRecord hits[2];
    for (int i = 0; i < cam.getNX(); i++) {
        for (int j = 0; j < cam.getNY(); j++) {
            int hitCount = sphere.findIntersections(cam.getRay(i, j), hits);
            if(hitCount > 0) {
                return true;
            }
        }
    }
    return false;
}

 /*Returns:
     1 if the viewing ray sees sphere1 (hits sphere1 before/without hitting sphere2)
     2 if the viewing ray sees sphere2 (hits sphere2 before/without hitting sphere1)
     3 if the viewing ray sees both spheres (hits both spheres at the same time)
     0 if the viewing ray sees neither sphere
       Note that the hit record for an intersection will let you get the t values
     where those intersections occurred. If a ray hits both spheres, the one
     with the lowest non-negative t value is the sphere that is seen. It's
     possible that two spheres that perfectly intersect in exactly one spot, and
     that spot is the location where the ray hits. That is the only time you should
     return 3.
       So, for example, if a ray hits a sphere in 2 places, then hits[0].t would give the first
     t value where it hits, and hits[1].t would give the second t where it hits
       Also note that the hit record returns the hits sorted by t value (unless you
     haven't correctly implemented your sorting in your quadratic method).
     Examples: assuming ray has origin (0, 0, 0) and direction (1, 0, 0):
     s1(dvec3(20, 0, 0), 5.0)
     s2(dvec3(10, 0, 0), 5.0)
     s3(dvec3(-8, 0, 0), 5.0)
     s4(dvec3(-20, 0, 0), 5.0)
     whichSphere(ray, s1, s2) should return 2
     whichSphere(ray, s1, s1) should return 3
     whichSphere(ray, s1, s3) should return 1
     whichSphere(ray, s3, s4) should return 0
  */
int whichSphere(const Ray& ray, const ISphere& sphere1, const ISphere& sphere2) {
    HitRecord hits[2];
    HitRecord hits2[2];
    
    int hitCount = sphere1.findIntersections(ray, hits);
    int hitCount2 = sphere2.findIntersections(ray, hits2);
    
    if (hitCount > 0 && hitCount2 == 0) {
        return 1;
    }
    
    if (hitCount2 > 0 && hitCount == 0) {
        return 2;
    }
    
    if (hitCount > 0 && hitCount2 > 0) {
        if (hits[0].t < 0) {
            return 2;
        }
        if (hits2[0].t < 0) {
            return 1;
        }
        if (hits[0].t < hits2[0].t) {
            return 1;
        }
        if (hits[0].t > hits2[0].t) {
            return 2;
        }
        if (hits[0].t == hits2[0].t) {
            return 3;
        }
    }
    
    return 0;
}

int main(int argc, char* argv[]) {
    // Do your testing here

    Ray rayray = Ray(dvec3(0,0,0), dvec3(0,1,0));
    ISphere s1 = ISphere(dvec3(10, 0, 0), 5.0);
    
    cout << rayIntersectsSphere(rayray, s1) << endl;
    return 0;
}
