
add_executable(virtual_dtor)

target_sources(
  virtual_dtor
  PRIVATE
  src/main.cpp
)

target_link_libraries(
  virtual_dtor
  PRIVATE
  fmt
)
