
add_executable(inheritance_vtable)

target_sources(
  inheritance_vtable
  PRIVATE
  src/main.cpp
)

target_link_libraries(
  inheritance_vtable
  PRIVATE
  fmt
)
