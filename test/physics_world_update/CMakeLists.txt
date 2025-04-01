set(CMAKE_CXX_STANDARD 23)

set(INC
  ../../include/
)

set(LIB
  math
  physics
)

set(SRC
  main.cpp
)

add_executable(physics_world_update ${SRC})

target_include_directories(physics_world_update PUBLIC ${INC})

target_link_libraries(physics_world_update PRIVATE ${LIB})
