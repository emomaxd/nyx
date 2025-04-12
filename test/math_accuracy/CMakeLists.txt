set(CMAKE_CXX_STANDARD 23)

set(INC
  ../../include/
)

set(LIB
  math
)

set(SRC
  main.cpp
)

add_executable(math_accuracy ${SRC})

target_include_directories(math_accuracy PUBLIC ${INC})

target_link_libraries(math_accuracy PRIVATE ${LIB})
