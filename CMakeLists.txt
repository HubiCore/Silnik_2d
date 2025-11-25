cmake_minimum_required(VERSION 3.24)
project(PGK)
set(CMAKE_CXX_STANDARD 17)


set(SFML_STATIC_LIBRARIES FALSE)
set(SFML_DIR "C:/SFML/lib/cmake/SFML")

find_package(SFML 2.6 COMPONENTS system window graphics audio REQUIRED)

add_executable(PGK main.cpp
        Engine.cpp
        Engine.hpp
        PrimitiveRenderer.hpp
        Point2D.cpp
        Point2D.hpp
        PrimitiveRender.cpp
        LineSegment.cpp
        LineSegment.hpp
        GameObjects.cpp
        GameObjects.hpp
        UpdatableObject.hpp
        DrawableObject.hpp
        TransformableObject.hpp
        ShapeObject.hpp
        Player.hpp
        BitmapHandler.hpp
        AnimatedObject.hpp
        BitmapObject.hpp
        BitmapHandler.cpp
        BitmapObject.cpp
        SpriteObject.hpp
        SpriteObject.cpp
        Player.cpp
)

target_link_libraries(PGK PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)
