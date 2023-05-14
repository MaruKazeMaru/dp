add_library(wavio STATIC wavio.c)

target_include_directories(wavio
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)