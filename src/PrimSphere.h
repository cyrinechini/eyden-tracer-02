// Sphere Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "IPrim.h"

// ================================ Sphere Primitive Class ================================
/**
 * @brief Sphere Geaometrical Primitive class
 */
class CPrimSphere : public IPrim
{
public:
	/**
	 * @brief Constructor
	 * @param pShader Pointer to the shader to be applied for the primitive
	 * @param origin Position of the center of the sphere
	 * @param radius Radius of the sphere
	 */
	CPrimSphere(ptr_shader_t pShader, Vec3f origin, float radius)
		: IPrim(pShader)
		, m_origin(origin)
		, m_radius(radius)
	{}
	virtual ~CPrimSphere(void) = default;

	virtual bool intersect(Ray &ray) const override
	{
	
		Vec3f diff = ray.org - m_origin;
		float a = ray.dir.dot(ray.dir);
		float b = 2 * ray.dir.dot(diff);
		float c = diff.dot(diff) - m_radius * m_radius;

		float inRoot = b * b - 4 * a * c;
		if (inRoot < 0)
            return false;
		float root = sqrtf(inRoot);
		
		float temp = (-b - root) / (2 * a);
		if (temp > ray.t)
			return false;
		
		if (temp < Epsilon) {
			temp = (-b + root) / (2 * a);
			if (temp < Epsilon || temp > ray.t)
				return false;
		}
		
		ray.t = temp;
        ray.hit = shared_from_this();
        
		return true;
	}
	
	virtual Vec3f getNormal(const Ray& ray) const override
	{
		return normalize((ray.org + (ray.t * ray.dir)) - m_origin);
	}
	
private:
	Vec3f m_origin;	///< Position of the center of the sphere
	float m_radius;	///< Radius of the sphere
};

