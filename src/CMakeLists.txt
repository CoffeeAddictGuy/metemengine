add_library(metemengine STATIC 
			core/engine.c core/renderer.c core/game_manager.c 
			scene/2d/scene.c scene/2d/entity.c scene/2d/tile_map.c scene/2d/camera2d.c
			scene/2d/physics/collision_box2d.c
)

find_package(raylib REQUIRED)
find_package(cJSON REQUIRED)

target_link_libraries(metemengine PUBLIC raylib)
target_link_libraries(metemengine PUBLIC cjson)

target_compile_definitions(metemengine PRIVATE $<$<CONFIG:Debug>:DEBUG>)
target_sources(metemengine PRIVATE ui/profiler.c)

target_include_directories(metemengine PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../includes
)

target_compile_options(metemengine PRIVATE 
	$<$<CONFIG:DEBUG>:-Wall -g -O3>
	$<$<CONFIG:Release>:-O3>
)
