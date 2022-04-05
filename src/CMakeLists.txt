add_library (sive-util
  ArgumentParsing.cpp ArgumentParsing.h
  handleGraphicsArgs.cpp handleGraphicsArgs.h
  #jsonSceneParser.cpp
  model_obj.cpp model_obj.h
  Random.cpp Random.h
  SceneDataContainer.h
  Timer.cpp Timer.h
  Vector3D.cpp Vector3D.h
  XMLSceneParser.h XMLSceneParser.cpp
)

#add_subdirectory(renderer)

target_link_libraries(sive-util renderer)

include_directories(${CMAKE_SOURCE_DIR}/renderer)
foreach(subdir ${RENDERER_SUBDIRS})
  include_directories(${CMAKE_SOURCE_DIR}/renderer/${subdir})
endforeach(subdir)