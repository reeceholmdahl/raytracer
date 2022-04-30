#include "Scene.hpp"

Scene::Scene(const size_t nx, const size_t ny)
  : pixelsX(nx)
  , pixelsY(ny)
  , aspectRatio(static_cast<double>(nx) / ny)
{
}

Scene::Scene(const size_t nx, const size_t ny, const fs::path& filename)
  : Scene(nx, ny)
{
  parseJsonFile(filename);
}

Scene::~Scene()
{
  while (!cameras.empty()) {
    auto c = cameras.back();
    cameras.pop_back();
    delete c;
  }

  while (!lights.empty()) {
    auto l = lights.back();
    lights.pop_back();
    delete l;
  }

  while (!shapes.empty()) {
    auto s = shapes.back();
    shapes.pop_back();
    delete s;
  }

  for (auto s : shaders) {
    delete s.second;
  }
  shaders.clear();
}

void
Scene::add(Camera* camera)
{
  cameras.push_back(camera);
}

void
Scene::add(Light* light)
{
  lights.push_back(light);
}

void
Scene::add(Shape* shape)
{
  shapes.push_back(shape);
}

void
Scene::addShader(const std::string& name, Shader* shader)
{
  shaders.insert({ name, shader });
}

Shader*
Scene::getShader(const std::string& name) const
{
  return shaders.at(name);
}
