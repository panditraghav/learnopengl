project('glad', 'c')

inc = include_directories('include/')
libglad = shared_library('glad', 'src/glad.c', include_directories: inc, install: true)

libglad_dep = declare_dependency(include_directories: inc, link_with: libglad)
