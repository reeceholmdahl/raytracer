#include "SceneContainer.hpp"

SceneContainer::SceneContainer(const SceneContainer &sc)
    : m_cameras(sc.m_cameras.size()), m_lights(sc.m_lights.size()), m_shapes(sc.m_shapes.size())
{
  // Does this need a copy ctor?
}

void SceneContainer::addCamera(Camera *camera)
{
  m_cameras.push_back(camera);
}

void SceneContainer::addLight(Light *light)
{
  m_lights.push_back(light);
}

void SceneContainer::addShape(Shape *shape)
{
  m_shapes.push_back(shape);
}

void SceneContainer::addShader(const std::string &name, Shader *shader)
{
  m_shaders[name] = shader;
}

std::vector<Camera *> SceneContainer::cameras() const
{
}
std::vector<Light *> SceneContainer::lights() const;
std::vector<Shape *> SceneContainer::shapes() const;
std::map<std::string, Shader *> SceneContainer::shaders() const;