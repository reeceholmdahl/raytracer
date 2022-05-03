#include "Scene.hpp"

Scene::Scene(const size_t nx,
             const size_t ny,
             const bool useBVH,
             const bool useShadows,
             const int recursionDepth)
  : pixelsX(nx)
  , pixelsY(ny)
  , aspectRatio(static_cast<double>(nx) / ny)
  , recursionDepth(recursionDepth)
  , useBVH(useBVH)
  , useShadows(useShadows)
  , bvh(nullptr)
{
}

Scene::Scene(const size_t nx,
             const size_t ny,
             const fs::path& filename,
             const bool useBVH,
             const bool useShadows,
             const int recursionDepth)
  : Scene(nx, ny, useBVH, useShadows, recursionDepth)
{
  parseJsonFile(filename);
  if (useBVH)
    bvh = new BVH(shapes);
  else
    bvh = new BVH();
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

bool
Scene::closestHit(const Ray& r, HitStruct& hit) const
{
  auto k_tmax = hit.tmax;
  if (useBVH) {
    if (!bvh || !bvh->head) {
      std::cerr
        << "Scene::closestHit | Using BVH but it is improperly initialized"
        << std::endl;
      return false;
    }

    return bvh->head->closestHit(r, hit);
  } else {
    for (Shape* shape : shapes) {
      auto testHit(hit);
      if (shape->closestHit(r, testHit)) {
        hit = testHit;
      }
    }

    return hit.t != k_tmax;
  }
}

bool
Scene::anyHit(const Ray& r, HitStruct& hit) const
{
  if (useBVH) {
    if (!bvh || !bvh->head) {
      std::cerr << "Scene::anyHit | Using BVH but it is improperly initialized"
                << std::endl;
      return false;
    }

    return bvh->head->anyHit(r, hit);
  } else {
    for (Shape* shape : shapes) {
      if (shape->closestHit(r, hit)) {
        return true;
      }
    }

    return false;
  }
}