#ifndef RENDERER_SCENE_H_
#define RENDERER_SCENE_H_

#include <filesystem>
#include <vector>
#include <map>

#include <glm/glm.hpp>

#include <nlohmann/json.hpp>

#include "Vector3.hpp"
#include "Camera.hpp"
#include "Shape.hpp"
#include "Light.hpp"
#include "Shader.hpp"
#include "BVH.hpp"

using json = nlohmann::json;

namespace fs = std::filesystem;

class Scene
{
public:
  Scene(const size_t nx, const size_t ny, const bool useBVH,
        const bool useShadows, const int recursionDepth);
  Scene(const size_t nx, const size_t ny, const fs::path& filename,
        const bool useBVH, const bool useShadows, const int recursionDepth);
  Scene(const Scene& scene) = delete;
  virtual ~Scene();

  void parseJsonFile(const std::string& filename);
  void parseJsonFile(const fs::path& filename);

  void add(Camera* camera);
  void add(Light* light);
  void add(Shape* shape);
  void addShader(const std::string& name, Shader* shader);

  Shader* getShader(const std::string& name) const;

  bool closestHit(const Ray& r, HitStruct& hit) const;
  bool anyHit(const Ray& r, HitStruct& hit) const;

  const size_t pixelsX, pixelsY;
  const double aspectRatio;
  const bool useShadows;
  const int recursionDepth;
  Vec3f bgColor;
  std::vector<Camera*> cameras;
  std::vector<Light*> lights;
  std::vector<Shape*> shapes;

private:
  bool useBVH;
  BVH* bvh;
  std::map<std::string, Shader*> shaders;
  glm::mat4 parseTransformData(json& transformData);
  Shape* extractAndCreateShapeFromJSONData(json& shapeData);
};

#endif
