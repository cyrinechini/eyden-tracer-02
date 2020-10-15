#pragma once

#include "IShader.h"

class CShaderMirror : public IShader
{
public:
	/**
	 * @brief Constructor
	 * @param scene Reference to the scene
	 */
	CShaderMirror(CScene& scene)
		: m_scene(scene)
	{}
	virtual ~CShaderMirror(void) = default;

	virtual Vec3f shade(const Ray& ray) const override
	{
        //shading normal vector N
        Vec3f n = ray.hit->getNormal(ray);
        //make sure the vector is facing the right way
        if (ray.dir.dot(n) > 0)
            n = -n;
        
        //reflected vector R
        Ray r;
        r.org = ray.t * ray.dir + ray.org;
        //calculate reflected incident ray  direction
        r.dir = normalize(ray.dir - (2 * (n.dot(ray.dir)) * n));
        r.t = std::numeric_limits<double>::infinity();
        
        return m_scene.RayTrace(r);
	}
	
	
private:
	CScene& m_scene;
};
