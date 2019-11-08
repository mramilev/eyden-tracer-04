#pragma once

#include "ShaderEyelight.h"
#include "texture.h"

/**
* @brief Eye-light shader with support of textures class
*/
class CShaderEyelightTextured : public CShaderEyelight
{
public:
	/**
	 * @brief Constructor
	 * @details This is a light-source-free shader
	 * @param color The color of the object
	 * @param fileName The path to the file with texture
	 */
	CShaderEyelightTextured(Vec3f color = RGB(0.5f, 0.5f, 0.5f), const std::string& fileName = {})
		: CShaderEyelight(color)
		, texture(fileName)
	{}
	virtual ~CShaderEyelightTextured(void) = default;
  
	virtual Vec3f Shade(const Ray& ray) const override
	{
		Vec2f UV_ray = ray.hit->getUV(ray);
		Vec3f tex_Shade = texture.GetTexel(UV_ray[0], UV_ray[1]);
		Vec3f eye_Shade = CShaderEyelight::Shade(ray);
		return tex_Shade.mul(eye_Shade);
	}

private:
	Texture texture;
};
