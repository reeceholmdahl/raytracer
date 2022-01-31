#ifndef _SCENE_CONTAINER_REECE_
#define _SCENE_CONTAINER_REECE_

#include <vector>
#include <map>

#include "Camera.hpp"
#include "Shape.hpp"
#include "Light.hpp"
#include "Shader.hpp"

class SceneContainer
{
public:
  SceneContainer() = default;
  SceneContainer(const SceneContainer &sc);

  void addCamera(Camera *camera);
  void addLight(Light *light);
  void addShape(Shape *shape);
  void addShader(const std::string &name, Shader *shader);

private:
  std::vector<Camera *> cameras;
  std::vector<Light *> lights;
  std::vector<Shape *> shapes;
  std::map<std::string, Shader *> shaderMap;
};

#endif