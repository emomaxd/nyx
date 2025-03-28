set(CMAKE_CXX_STANDARD 23)

set(INC
  ../../include/
)

set(LIB
  rigidbody
)

set(SRC
  main.cpp
)

add_executable(rb_0 ${SRC})

target_include_directories(rb_0 PUBLIC ${INC})

target_link_libraries(rb_0 PRIVATE ${LIB})
