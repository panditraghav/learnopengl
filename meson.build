project('lopengl', 'cpp')
cmake = import('cmake')

src = ['main.cpp']
inc = []

glfw = cmake.subproject('glfw-3.4')
glfw_dep = glfw.dependency('glfw')
# message('CMake targets:\n - ' + '\n - '.join(glfw.target_list()))

glad = subproject('glad')
glad_dep = glad.get_variable('libglad_dep')

executable('lopengl', src, include_directories: inc, dependencies: [glfw_dep, glad_dep])
