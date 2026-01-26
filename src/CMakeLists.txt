add_library(metemengine STATIC 
			core/engine.c core/renderer.c 
			scene/2d/scene.c scene/2d/entity.c scene/2d/tile_map.c scene/2d/camera2d.c
			scene/2d/physics/collision_box2d.c
)

find_package(raylib REQUIRED)
find_package(cjson REQUIRED)

target_link_libraries(metemengine PUBLIC raylib)
target_link_libraries(metemengine PUBLIC cjson)

target_include_directories(metemengine PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_options(metemengine PRIVATE 
	$<$<CONFIG:DEBUG>:-Wall -g -O0>
	$<$<CONFIG:Release>:-O3
)