## ------------------------------------------------------------------------------- ##
##                                     Michka                                      ##
## ------------------------------------------------------------------------------- ##
##                                  MIT License                                    ##
##                                                                                 ##
## Copyright (c) 2020-2020 amir alizadeh.                                          ##
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

    ${CMAKE_CURRENT_SOURCE_DIR}/Container/Color.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Container/String.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Container/Variant.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Foundation/Event.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Foundation/EventManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Foundation/File.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Foundation/Types.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/BoundingBox.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/BoundingSphere.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/Matrix.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/Matrix3.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/Plane.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/Quaternion.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/Ray.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/Utility.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/Vector2.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/Vector3.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/Vector4.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Memory/Memory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Thread/Thread.cpp

    # -------------------------------------------------------------------------- #

    PARENT_SCOPE
)
