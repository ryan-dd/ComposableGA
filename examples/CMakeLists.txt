add_executable(Rosenbrock Rosenbrock.cpp)
include(CompilerWarnings)
set_project_warnings(Rosenbrock)
target_link_libraries(Rosenbrock PRIVATE evy)

