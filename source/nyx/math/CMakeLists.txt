set(CMAKE_CXX_STANDARD 23)

set(INC
  ../../../include/
)

set(LIB
)

set(SRC
  vec2.cpp
  vec3.cpp
)

add_library(math ${SRC})

target_include_directories(math PUBLIC ${INC})

target_link_libraries(math PRIVATE ${LIB})
