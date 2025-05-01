set(CMAKE_CXX_STANDARD 23)

set(INC
  ../../../../include/
)

set(LIB
  math
)

set(SRC
  physics_world.cpp
)

add_library(scene ${SRC})

target_include_directories(scene PUBLIC ${INC})

target_link_libraries(scene PRIVATE ${LIB})
