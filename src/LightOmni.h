#pragma once

#include "ILight.h"

/**
 * @brief Point light source class
 */
class CLightOmni : public ILight
{
public:
	/**
	 * @brief Constructor
	 * @param intensity The emission color and strength of the light source
	 * @param org The position (origin) of the light source
	 * @param castShadow Flag indicatin whether the light source casts shadow
	 */
	CLightOmni(const Vec3f& intensity, const Vec3f& org, bool castShadow = true)
		: ILight(castShadow)
		, m_intensity(intensity)
		, m_org(org)
	{}
	virtual ~CLightOmni(void) = default;

	virtual std::optional<Vec3f> illuminate(Ray& ray) override
	{
        //direction vector from the surface point to the light source
        ray.hit = NULL;
        ray.t   = norm(m_org - ray.org) - Epsilon;
        ray.dir = normalize(m_org - ray.org);
    
        return (1.0f / (ray.t * ray.t)) * m_intensity;
	}


private:
	Vec3f m_intensity;	///< The emission (red, green, blue)
	Vec3f m_org;		///< The light source origin
};
