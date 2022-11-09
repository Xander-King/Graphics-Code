/****************************************************
 * 2016-2022 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * PLEASE NOTE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#include "light.h"
#include "io.h"
#include "ishape.h"

 /**
  * @fn	color ambientColor(const color &matAmbient, const color &lightColor)
  * @brief	Computes the ambient color produced by a single light at a single point.
  * @param	matAmbient  	Ambient material property.
  * @param	lightColor	Light's color.
  * @return	Ambient color.
   */

color ambientColor(const color& matAmbient, const color& lightColor) {
	/* CSE 386 - todo  */
	return matAmbient*lightColor;
}

/**
 * @fn	color diffuseColor(const color &matDiffuse, const color &light, const dvec3 &l, const dvec3 &n)
 * @brief	Computes diffuse color produce by a single light at a single point.
 * @param	matDiffuse		 	Diffuse material property.
 * @param	lightColor	 	The light's color.
 * @param	l		 	Light vector.
 * @param	n		 	Normal vector.
 * @return	Diffuse color.
 */

color diffuseColor(const color& matDiffuse, const color& lightColor,
	const dvec3& l, const dvec3& n) {
	/* CSE 386 - todo  */
	return matDiffuse*lightColor*(max(glm::dot(l, n), 0, 0));

}

/**
 * @fn	color specularColor(const color &matSpecular, const color &lightColor, double shininess,
 *							const dvec3 &r, const dvec3 &v)
 * @brief	Computes specular color produce by a single light at a single point.
 * @param	matSpecular		 	Material.
 * @param	lightColor	 	The light's color.
 * @param	shininess	Material shininess.
 * @param	r		 	Reflection vector.
 * @param	v		 	Viewing vector.
 * @return	Specular color.
 */

color specularColor(const color& matSpecular, const color& lightColor,
	double shininess,
	const dvec3& r, const dvec3& v) {
	/* CSE 386 - todo  */
	return matSpecular*lightColor*glm::pow((max(((glm::dot(r, v))), 0, 0)), shininess);
}

/**
 * @fn	color totalColor(const Material &mat, const color &lightColor,
 *						const dvec3 &viewingDir, const dvec3 &normal,
 *						const dvec3 &lightPos, const dvec3 &intersectionPt,
 *						bool attenuationOn, const LightAttenuationParameters &ATparams)
 * @brief	Color produced by a single light at a single point.
 * @param	mat			  	Material.
 * @param	lightColor	  	The light's color.
 * @param	v	  			The v vector.
 * @param	n   		  	Normal vector.
 * @param	lightPos	  	Light position.
 * @param	intersectionPt	(x,y,z) of intersection point.
 * @param	attenuationOn 	true if attenuation is on.
 * @param	ATparams	  	Attenuation parameters.
 * @return	Color produced by a single light at a single point.
 */

color totalColor(const Material& mat, const color& lightColor,
	const dvec3& v, const dvec3& n,
	const dvec3& lightPos, const dvec3& intersectionPt,
	bool attenuationOn,
	const LightATParams& ATparams) {
    
   dvec3 lightVec = glm::normalize(lightPos - intersectionPt);
    dvec3 reflectVec = (((2 * (glm::dot(lightVec, n))) * n) - lightVec);
	/* CSE 386 - todo  */
    color spec = specularColor(mat.specular, lightColor, mat.shininess, reflectVec, v );
    color diff = diffuseColor(mat.diffuse, lightColor, lightVec, n);
    color amb = ambientColor(mat.ambient, lightColor);
    
   
    
    if (!attenuationOn) {
        dvec3 attOffSum = amb + diff + spec;
        
        if (attOffSum.x > 1.0) {
            attOffSum.x = 1.0;
        }
        
        if (attOffSum.y > 1.0) {
            attOffSum.y = 1.0;
        }
        
        if (attOffSum.z > 1.0) {
            attOffSum.z = 1.0;
        }
        
        if (attOffSum.x < 0.0) {
            attOffSum.x = 0.0;
        }
        
        if (attOffSum.y < 0.0) {
            attOffSum.y = 0.0;
        }
        
        if (attOffSum.z < 0.0) {
            attOffSum.z = 0.0;
        }
        
        return attOffSum;
    }
    
    double d = glm::length(lightPos - intersectionPt);
    
    double att = (1/(ATparams.constant + (ATparams.linear*d) +(ATparams.quadratic*(glm::pow(d, 2)))));
    
    dvec3 attOnSum = amb + (att*diff) + (att*spec);
    
    if (attOnSum.x > 1.0) {
        attOnSum.x = 1.0;
    }
    
    if (attOnSum.y > 1.0) {
        attOnSum.y = 1.0;
    }
    
    if (attOnSum.z > 1.0) {
        attOnSum.z = 1.0;
    }
    
    if (attOnSum.x < 0.0) {
        attOnSum.x = 0.0;
    }
    
    if (attOnSum.y < 0.0) {
        attOnSum.y = 0.0;
    }
    
    if (attOnSum.z < 0.0) {
        attOnSum.z = 0.0;
    }
    
    return attOnSum;
    

}

/**
 * @fn	color PositionalLight::illuminate(const dvec3 &interceptWorldCoords,
 *										const dvec3 &normal, const Material &material,
 *										const Frame &eyeFrame, bool inShadow) const
 * @brief	Computes the color this light produces in RAYTRACING applications.
 * @param	interceptWorldCoords	(x, y, z) at the intercept point.
 * @param	normal				The normal vector.
 * @param	material			The object's material properties.
 * @param	eyeFrame			The coordinate frame of the camera.
 * @param	inShadow			true if the point is in a shadow.
 * @return	The color produced at the intercept point, given this light.
 */

color PositionalLight::illuminate(const dvec3& interceptWorldCoords,
	const dvec3& normal,
	const Material& material,
	const Frame& eyeFrame,
	bool inShadow) const {

    if(!LightSource::isOn) {
        return color (0,0,0);
    }
    
    if(LightSource::isOn && inShadow) {
       return ambientColor(material.ambient, LightSource::lightColor);
    }
    
    dvec3 v = glm::normalize(eyeFrame.origin - interceptWorldCoords);
	/* CSE 386 - todo  */
	return totalColor(material, LightSource::lightColor, v, normal, PositionalLight::pos, interceptWorldCoords, PositionalLight::attenuationIsTurnedOn, PositionalLight::atParams);
}

/*
* @fn PositionalLight::actualPosition(const Frame& eyeFrame) const
* @brief	Returns the global world coordinates of this light.
* @param	eyeFrame	The camera's frame
* @return	The global world coordinates of this light. This will be the light's
*			raw position. Or, it will be the position relative to the camera's
*			frame (transformed from camera's frame into the world coordinate frame).
*/

dvec3 PositionalLight::actualPosition(const Frame& eyeFrame) const {
	return isTiedToWorld ? pos : eyeFrame.globalCoordToFrameCoords(pos);
}

/**
* @fn	bool PositionalLight::pointIsInAShadow(const dvec3& intercept, const dvec3& normal, const vector<VisibleIShapePtr>& objects, const Frame& eyeFrame) const
* @brief	Determines if an intercept point falls in a shadow.
* @param	intercept	the position of the intercept.
* @param	normal		the normal vector at the intercept point
* @param	objects		the collection of opaque objects in the scene
*/

bool PositionalLight::pointIsInAShadow(const dvec3& intercept,
	const dvec3& normal,
	const vector<VisibleIShapePtr>& objects,
	const Frame& eyeFrame) const {
	/* CSE 386 - todo  */
    OpaqueHitRecord hit;
    hit.t = FLT_MAX;
    for (VisibleIShapePtr o : objects) {
        OpaqueHitRecord tempHit;
        o -> findClosestIntersection(getShadowFeeler(intercept, normal, eyeFrame), tempHit);
        if (tempHit.t < hit.t) {
            hit = tempHit;
        }
    }
    
    double distance = glm::distance(intercept, pos);
    if (glm::distance(hit.interceptPt, pos) < distance) {
        return true;
    }
	return false;
}

/**
* @fn	Ray PositionalLight::getShadowFeeler(const dvec3& interceptWorldCoords, const dvec3& normal, const Frame &eyeFrame) const
* @brief	Returns the shadow feeler for this light.
* @param	interceptWorldCoords	the position of the intercept.
* @param	normal		The normal vector at the intercept point
* @param	eyeFrame	The coordinate frame of the camera.
*/

Ray PositionalLight::getShadowFeeler(const dvec3& interceptWorldCoords,
	const dvec3& normal,
	const Frame& eyeFrame) const {
	/* 386 - todo */
    
    double distance = glm::distance(pos, interceptWorldCoords);
    dvec3 dir = glm::normalize(pos - interceptWorldCoords);
    
	Ray shadowFeeler(interceptWorldCoords, dir);
    
	return shadowFeeler;
}

/**
 * @fn	color SpotLight::illuminate(const dvec3 &interceptWorldCoords,
 *									const dvec3 &normal, const Material &material,
 *									const Frame &eyeFrame, bool inShadow) const
 * @brief	Computes the color this light produces in raytracing applications.
 * @param	interceptWorldCoords				The surface properties of the intercept point.
 * @param	normal					The normal vector.
 * @param	material			The object's material properties.
 * @param	eyeFrame			The coordinate frame of the camera.
 * @param	inShadow			true if the point is in a shadow.
 * @return	The color produced at the intercept point, given this light.
 */

color SpotLight::illuminate(const dvec3& interceptWorldCoords,
	const dvec3& normal,
	const Material& material,
	const Frame& eyeFrame,
	bool inShadow) const {
	/* CSE 386 - todo  */
	return material.diffuse;
}

/**
* @fn	void setDir (double dx, double dy, double dz)
* @brief	Sets the direction of the spotlight.
* @param	dx		x component of the direction
* @param	dy		y component of the direction
* @param	dz		z component of the direction
*/

void SpotLight::setDir(double dx, double dy, double dz) {
	spotDir = glm::normalize(dvec3(dx, dy, dz));
}

/**
* @fn	SpotLight::isInSpotlightCone(const dvec3& spotPos, const dvec3& spotDir, double spotFOV, const dvec3& intercept)
* @brief	Determines if an intercept point falls within a spotlight's cone.
* @param	spotPos		where the spotlight is positioned
* @param	spotDir		normalized direction of spotlight's pointing direction
* @param	spotFOV		spotlight's field of view, which is 2X of the angle from the viewing axis
* @param	intercept	the position of the intercept.
*/

bool SpotLight::isInSpotlightCone(const dvec3& spotPos,
	const dvec3& spotDir,
	double spotFOV,
	const dvec3& intercept) {
	/* CSE 386 - todo  */
	return false;
}
