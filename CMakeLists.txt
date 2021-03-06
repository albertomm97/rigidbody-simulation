cmake_minimum_required(VERSION 3.4)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/Modules/")

project(UTAD-SIM02-RigidBody)

add_executable(UTAD-SIM02-RigidBody
    src/Gfx/Gfx.cpp
    src/Gfx/Gfx.h
    src/Math/Matrix3f.h
    src/Math/Quaternionf.h
    src/Math/Vector2f.h
    src/Math/Vector3f.h
    src/Std/CMath.h
    src/Std/CStdInt.h
    src/BoxShape.cpp
    src/BoxShape.h
    src/main.cpp
    src/RigidBody.cpp
    src/RigidBody.h
    src/Shape.cpp
    src/Shape.h
    src/SphereShape.cpp
    src/SphereShape.h
    src/World.cpp
    src/World.h
    src/Particle.cpp
    src/Particle.h
    src/Spring.cpp
    src/Spring.h
    )

find_package(Eigen3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

target_include_directories(UTAD-SIM02-RigidBody
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/src
    ${EIGEN3_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${GLUT_INCLUDE_DIR}
    )

target_link_libraries(UTAD-SIM02-RigidBody
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARY}
    )

if (WIN32)
    add_custom_command(
        TARGET UTAD-SIM02-RigidBody
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different
        "${PROJECT_SOURCE_DIR}/External/freeglut-3.2.1/build-vs2019/bin/$<CONFIG>/freeglut$<$<CONFIG:Debug>:d>.dll"
        "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>"
        )
endif ()
