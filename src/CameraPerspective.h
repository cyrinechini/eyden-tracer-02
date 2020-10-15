// Perspective Camera class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "ICamera.h"

// ================================ Perspective Camera Class ================================
/**
 * @brief Perspective Camera class
 */
class CCameraPerspective : public ICamera
{
public:
    /**
     * @brief Constructor
     * @param resolution The image resolution in pixels
     * @param pos Camera origin (center of projection)
     * @param dir Normalized camera viewing direction
     * @param up Normalized camera up-vector
     * @param angle (Vertical) full opening angle of the viewing frustum in degrees
     */
    CCameraPerspective(Size resolution, const Vec3f& pos, const Vec3f& dir, const Vec3f& up, float angle)
        : ICamera(resolution)
        , m_pos(pos)
        , m_dir(dir)
        , m_up(up)
        , m_focus(1.0f / tanf(angle * Pif / 360))    // f = 1 / tg(angle / 2)
    {
        m_zAxis = dir;
        m_xAxis = m_zAxis.cross(m_up);
        m_yAxis = m_zAxis.cross(m_xAxis);
        
        m_xAxis = normalize(m_xAxis);
        m_yAxis = normalize(m_yAxis);
        m_zAxis = normalize(m_zAxis);
    }
    virtual ~CCameraPerspective(void) = default;

	virtual void InitRay(Ray& ray, int x, int y) override
	{
		float dx = 0.5f;	// x-shift to the center of the pixel
		float dy = 0.5f;	// y-shift to the center of the pixel
		
		// Screen space coordinates [-1, 1]
		float sscx = 2 * (x + dx) / getResolution().width - 1;
		float sscy = 2 * (y + dy) / getResolution().height - 1;
		
		ray.org = m_pos;
		ray.dir = normalize(getAspectRatio() * sscx * m_xAxis + sscy * m_yAxis + m_focus * m_zAxis);
		ray.t = std::numeric_limits<float>::infinity();
	}


private:
    // input values
    Vec3f m_pos;    ///< Camera origin (center of projection)
    Vec3f m_dir;    ///< Camera viewing direction
    Vec3f m_up;     ///< Camera up-vector
    float m_focus;  ///< The focal length

    // preprocessed values
    Vec3f m_xAxis;  ///< Camera x-axis in WCS
    Vec3f m_yAxis;  ///< Camera y-axis in WCS
    Vec3f m_zAxis;  ///< Camera z-axis in WCS
};

