cmake_minimum_required(VERSION 3.24)
project(PGK)
set(CMAKE_CXX_STANDARD 17)


set(SFML_STATIC_LIBRARIES FALSE)
set(SFML_DIR "D:/Grafika/SFML/lib/cmake/SFML")

find_package(SFML 2.6 COMPONENTS system window graphics audio REQUIRED)

add_executable(PGK main.cpp
        Engine/Engine.cpp
        Engine/Engine.hpp
        Object/Renderer/PrimitiveRenderer.hpp
        Figures/Point2D/Point2D.cpp
        Figures/Point2D/Point2D.hpp
        Object/Renderer/PrimitiveRender.cpp
        Figures/LineSegment/LineSegment.cpp
        Figures/LineSegment/LineSegment.hpp
        Object/GameObject/GameObjects.hpp
        Object/UpdatableObject.hpp
        Object/DrawableObject.hpp
        Object/TransformableObject.hpp
        Object/ShapeObject.hpp
        Player/Player.hpp
        Object/BitmapHandler/BitmapHandler.hpp
        Object/AnimatedObject/AnimatedObject.hpp
        Object/BitmapObject/BitmapObject.hpp
        Object/BitmapHandler/BitmapHandler.cpp
        Object/BitmapObject/BitmapObject.cpp
        Object/sprite/SpriteObject.hpp
        Object/sprite/SpriteObject.cpp
        Player/Player.cpp
        Object/AnimatedObject/AnimatedObject.cpp
        Figures/drawAllFigures/drawAllFigures.cpp
        Figures/drawAllFigures/drawAllFigures.hpp
        Object/BitmapObject/BitmapObject.cpp
        Figures/Shapes/Helpers/Helpers.cpp
        Figures/Shapes/Helpers/Helpers.hpp
        Figures/Shapes/Points/Points.hpp
        Figures/Shapes/Points/Points.cpp
        Figures/Shapes/Lines/Lines.hpp
        Figures/Shapes/Lines/Lines.cpp
        Figures/Shapes/Polylines/Polylines.hpp
        Figures/Shapes/Polylines/Polylines.cpp
        Figures/Shapes/Circles/Circles.hpp
        Figures/Shapes/Circles/Circles.cpp
        Figures/Shapes/Elipses/Elipses.hpp
        Figures/Shapes/Elipses/Elipses.cpp
        Figures/Shapes/Polygon/Polygons.hpp
        Figures/Shapes/Polygon/Polygons.cpp
)

target_link_libraries(PGK PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)
