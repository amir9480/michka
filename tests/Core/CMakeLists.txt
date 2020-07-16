set(
    TEST_SOURCES
    ${TEST_SOURCES}

    # -------------------------------------------------------------------------- #

    ${CMAKE_CURRENT_SOURCE_DIR}/Container/ListTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Container/MapTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Container/StringTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Container/VectorTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HelpersTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/BoundingBoxTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/BoundingSphereTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/MathUtilityTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/MatrixTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/Matrix3Test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/QuaternionTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/Vector2Test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/Vector3Test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/Vector4Test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Reflection/TypeTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Thread/ThreadTest.cpp

    # -------------------------------------------------------------------------- #

    PARENT_SCOPE
)
