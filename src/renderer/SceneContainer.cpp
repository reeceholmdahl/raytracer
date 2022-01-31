#include "SceneContainer.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Shape.hpp"
#include "Shader.hpp"

SceneContainer::SceneContainer(const SceneContainer &sc)
  : cameras(sc.cameras.size()), lights(sc.lights.size()), shapes(sc.shapes.size())
{
  // Does this need a copy ctor?
}

void SceneContainer::addCamera(Camera *camera)
{
  cameras.push_back(camera);
}

void SceneContainer::addLight(Light *light)
{
  lights.push_back(light);
}

void SceneContainer::addShape(Shape *shape)
{
  shapes.push_back(shape);
}

void SceneContainer::addShader(const std::string &name, Shader *shader)
{
  shaderMap[name] = shader;
}