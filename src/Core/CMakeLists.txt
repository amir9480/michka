set(
    SOURCES
    ${SOURCES}

    # -------------------------------------------------------------------------- #

    ${CMAKE_CURRENT_SOURCE_DIR}/Container/String.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/BoundingBox.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/Matrix.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/Matrix3.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/Quaternion.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/Utility.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/Vector2.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/Vector3.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/Vector4.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Memory/Memory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Thread/Thread.cpp

    # -------------------------------------------------------------------------- #

    PARENT_SCOPE
)
