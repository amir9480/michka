## ------------------------------------------------------------------------------- ##
##                                     Michka                                      ##
## ------------------------------------------------------------------------------- ##
##                                  MIT License                                    ##
##                                                                                 ##
## Copyright (c) 2020-2021 amir alizadeh.                                          ##
##                                                                                 ##
## Permission is hereby granted, free of charge, to any person obtaining a copy    ##
## of this software and associated documentation files (the "Software"), to deal   ##
## in the Software without restriction, including without limitation the rights    ##
## to use, copy, modify, merge, publish, distribute, sublicense, and/or sell       ##
## copies of the Software, and to permit persons to whom the Software is           ##
## furnished to do so, subject to the following conditions:                        ##
##                                                                                 ##
## The above copyright notice and this permission notice shall be included in all  ##
## copies or substantial portions of the Software.                                 ##
##                                                                                 ##
## THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      ##
## IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        ##
## FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     ##
## AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          ##
## LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   ##
## OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   ##
## SOFTWARE.                                                                       ##
## ------------------------------------------------------------------------------- ##

set(
    SOURCES
    ${SOURCES}

    # -------------------------------------------------------------------------- #

    ${CMAKE_CURRENT_SOURCE_DIR}/Container/ColorTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Container/HashTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Container/ListTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Container/MapTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Container/PositionTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Container/RectTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Container/SizeTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Container/StringTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Container/VariantTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Container/VectorTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Foundation/EventTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Foundation/FileTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Foundation/LogTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Foundation/TypesTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HelpersTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/BoundingBoxTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/BoundingSphereTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/MathUtilityTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/MatrixTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/Matrix3Test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/PlaneTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/QuaternionTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/RayTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/Vector2Test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/Vector3Test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/Vector4Test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Reflection/ClassReflectionTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Reflection/MetaAttributesTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Reflection/TypeTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Thread/ThreadTest.cpp

    # -------------------------------------------------------------------------- #

    PARENT_SCOPE
)
