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

  void add(Camera *camera);
  void add(Light *light);
  void add(Shape *shape);
  void add(const std::string &name, Shader *shader);

  const std::vector<Camera *> &cameras() const;
  const std::vector<Light *> &lights() const;
  const std::vector<Shape *> &shapes() const;
  const std::map<std::string, Shader *> &shaders() const;

private:
  std::vector<Camera *> m_cameras;
  std::vector<Light *> m_lights;
  std::vector<Shape *> m_shapes;
  std::map<std::string, Shader *> m_shaders;
};

#endif