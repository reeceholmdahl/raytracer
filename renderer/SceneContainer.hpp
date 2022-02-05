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

  std::vector<Camera *> cameras() const;
  std::vector<Light *> lights() const;
  std::vector<Shape *> shapes() const;
  std::map<std::string, Shader *> shaders() const;

private:
  std::vector<Camera *> m_cameras;
  std::vector<Light *> m_lights;
  std::vector<Shape *> m_shapes;
  std::map<std::string, Shader *> m_shaders;
};

#endif