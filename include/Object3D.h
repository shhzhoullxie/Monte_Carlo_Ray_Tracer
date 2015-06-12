#ifndef OBJECT_3D

#include <vector>

#include <glm/glm.hpp>
#include "utils.h"

class Object3D
{
private:
	const Material* material_;
public:
	Object3D(Material* material);
	virtual ~Object3D(){};

	virtual bool intersect(IntersectionData* id, Ray r) const = 0;
	Material material() const;
};

class Mesh : public Object3D
{
private:
	std::vector<glm::vec3> positions_;
	std::vector<glm::vec2> uvs_;
	std::vector<glm::vec3> normals_;
	std::vector<int> indices_;

	glm::mat4 transform_;
public:
	Mesh(Material * material);
	static bool loadOBJ(
		const char * path, 
		std::vector<glm::vec3> & out_vertices, 
		std::vector<glm::vec2> & out_uvs,
		std::vector<glm::vec3> & out_normals
	);
	~Mesh(){};

	virtual bool intersect(IntersectionData* id, Ray r) const;
};

class Sphere : public Object3D
{
private:
	const glm::vec3 POSITION_;
	const float RADIUS_;
public:
	Sphere(glm::vec3 position, float radius, Material* material);
	~Sphere(){};

	bool intersect(IntersectionData* id, Ray r) const;
};

class Plane : public Object3D
{
private:
	const glm::vec3 P0_, P1_, P2_;
public:
	Plane(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, Material* material);
	~Plane(){};

	bool intersect(IntersectionData* id, Ray r) const;
	glm::vec3 getPointOnSurface(float u, float v) const;
};

class LightSource
{
private:
	const Plane emitter_;
public:
	LightSource(
		glm::vec3 p0,
		glm::vec3 p1,
		glm::vec3 p2,
		float emittance,
		SpectralDistribution color);
	~LightSource(){};
	bool intersect(LightSourceIntersectionData* light_id, Ray r);
	glm::vec3 getPointOnSurface(float u, float v);


	const float emittance;
	const SpectralDistribution color;
};

#define OBJECT_3D
#endif