set(CMAKE_CXX_STANDARD 23)

set(INC
  ../../include/
)

set(LIB
  math
)

set(SRC
  physics_world.cpp
  rigidbody_system.cpp
)

add_library(physics ${SRC})

target_include_directories(physics PUBLIC ${INC})

target_link_libraries(physics PRIVATE ${LIB})
