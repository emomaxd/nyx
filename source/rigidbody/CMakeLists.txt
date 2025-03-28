set(CMAKE_CXX_STANDARD 23)

set(INC
  ../../include/
)

set(LIB
)

set(SRC
  rigidbody.cpp
)

add_library(rigidbody ${SRC})

target_include_directories(rigidbody PUBLIC ${INC})

target_link_libraries(rigidbody PRIVATE ${LIB})
