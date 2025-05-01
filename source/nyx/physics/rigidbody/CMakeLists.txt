set(CMAKE_CXX_STANDARD 23)

set(INC
  ../../../../include/
)

set(LIB
  math
)

set(SRC
  rigidbody_system.cpp
)

add_library(rigidbody ${SRC})

target_include_directories(rigidbody PUBLIC ${INC})

target_link_libraries(rigidbody PRIVATE ${LIB})
