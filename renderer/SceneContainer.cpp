#include "SceneContainer.hpp"

SceneContainer::SceneContainer(const SceneContainer &sc)
    : m_cameras(sc.m_cameras.size()), m_lights(sc.m_lights.size()), m_shapes(sc.m_shapes.size())
{
  // Does this need a copy ctor?
}

void SceneContainer::add(Camera *camera)
{
  m_cameras.push_back(camera);
}

void SceneContainer::add(Light *light)
{
  m_lights.push_back(light);
}

void SceneContainer::add(Shape *shape)
{
  m_shapes.push_back(shape);
}

void SceneContainer::add(const std::string &name, Shader *shader)
{
  m_shaders[name] = shader;
}

const std::vector<Camera *> &SceneContainer::cameras() const
{
  return m_cameras;
}

const std::vector<Light *> &SceneContainer::lights() const
{
  return m_lights;
}
const std::vector<Shape *> &SceneContainer::shapes() const
{
  return m_shapes;
}
const std::map<std::string, Shader *> &SceneContainer::shaders() const
{
  return m_shaders;
}