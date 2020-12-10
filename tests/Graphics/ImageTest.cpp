// ------------------------------------------------------------------------------- //
//                                     Michka                                      //
// ------------------------------------------------------------------------------- //
//                                  MIT License                                    //
//                                                                                 //
// Copyright (c) 2020-2020 amir alizadeh.                                          //
//                                                                                 //
// Permission is hereby granted, free of charge, to any person obtaining a copy    //
// of this software and associated documentation files (the "Software"), to deal   //
// in the Software without restriction, including without limitation the rights    //
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell       //
// copies of the Software, and to permit persons to whom the Software is           //
// furnished to do so, subject to the following conditions:                        //
//                                                                                 //
// The above copyright notice and this permission notice shall be included in all  //
// copies or substantial portions of the Software.                                 //
//                                                                                 //
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      //
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        //
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     //
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          //
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   //
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   //
// SOFTWARE.                                                                       //
// ------------------------------------------------------------------------------- //

#include <gtest/gtest.h>
#include "Core/Container/String.h"
#include "Core/Foundation/File.h"
#include "Graphics/Image.h"

TEST(ImageTest, LoadFromFile)
{
    Michka::String testFilePath = Michka::File::realpath(Michka::String(__FILE__) + "/../../../tests/Files/Graphics/Images");
    {
        Michka::Image image(testFilePath + "/black1.jpg");
        ASSERT_EQ(image.getWidth(), 1);
        ASSERT_EQ(image.getHeight(), 1);
        ASSERT_EQ(image.getSize(), 3);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Vector4(0, 0, 0, 255));
    }
    {
        Michka::Image image(testFilePath + "/white1.jpg");
        ASSERT_EQ(image.getWidth(), 1);
        ASSERT_EQ(image.getHeight(), 1);
        ASSERT_EQ(image.getSize(), 3);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Vector4(255, 255, 255, 255));
    }
    {
        Michka::Image image(testFilePath + "/red1.jpg");
        ASSERT_EQ(image.getWidth(), 1);
        ASSERT_EQ(image.getHeight(), 1);
        ASSERT_EQ(image.getSize(), 3);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Vector4(254, 0, 0, 255));
    }
    {
        Michka::Image image(testFilePath + "/green1.jpg");
        ASSERT_EQ(image.getWidth(), 1);
        ASSERT_EQ(image.getHeight(), 1);
        ASSERT_EQ(image.getSize(), 3);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Vector4(0, 255, 1, 255));
    }
    {
        Michka::Image image(testFilePath + "/blue1.jpg");
        ASSERT_EQ(image.getWidth(), 1);
        ASSERT_EQ(image.getHeight(), 1);
        ASSERT_EQ(image.getSize(), 3);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Vector4(0, 0, 254, 255));
    }

    {
        Michka::Image image(testFilePath + "/black2.jpg");
        ASSERT_EQ(image.getWidth(), 2);
        ASSERT_EQ(image.getHeight(), 2);
        ASSERT_EQ(image.getSize(), 12);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Vector4(0, 0, 0, 255));
        ASSERT_EQ(image.getPixel(0, 1), Michka::Vector4(0, 0, 0, 255));
        ASSERT_EQ(image.getPixel(1, 0), Michka::Vector4(0, 0, 0, 255));
        ASSERT_EQ(image.getPixel(1, 1), Michka::Vector4(0, 0, 0, 255));
    }
    {
        Michka::Image image(testFilePath + "/white2.jpg");
        ASSERT_EQ(image.getWidth(), 2);
        ASSERT_EQ(image.getHeight(), 2);
        ASSERT_EQ(image.getSize(), 12);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Vector4(255, 255, 255, 255));
        ASSERT_EQ(image.getPixel(0, 1), Michka::Vector4(255, 255, 255, 255));
        ASSERT_EQ(image.getPixel(1, 0), Michka::Vector4(255, 255, 255, 255));
        ASSERT_EQ(image.getPixel(1, 1), Michka::Vector4(255, 255, 255, 255));
    }
    {
        Michka::Image image(testFilePath + "/red2.jpg");
        ASSERT_EQ(image.getWidth(), 2);
        ASSERT_EQ(image.getHeight(), 2);
        ASSERT_EQ(image.getSize(), 12);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Vector4(254, 0, 0, 255));
        ASSERT_EQ(image.getPixel(0, 1), Michka::Vector4(254, 0, 0, 255));
        ASSERT_EQ(image.getPixel(1, 0), Michka::Vector4(254, 0, 0, 255));
        ASSERT_EQ(image.getPixel(1, 1), Michka::Vector4(254, 0, 0, 255));
    }
    {
        Michka::Image image(testFilePath + "/green2.jpg");
        ASSERT_EQ(image.getWidth(), 2);
        ASSERT_EQ(image.getHeight(), 2);
        ASSERT_EQ(image.getSize(), 12);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Vector4(0, 255, 1, 255));
        ASSERT_EQ(image.getPixel(0, 1), Michka::Vector4(0, 255, 1, 255));
        ASSERT_EQ(image.getPixel(1, 0), Michka::Vector4(0, 255, 1, 255));
        ASSERT_EQ(image.getPixel(1, 1), Michka::Vector4(0, 255, 1, 255));
    }
    {
        Michka::Image image(testFilePath + "/blue2.jpg");
        ASSERT_EQ(image.getWidth(), 2);
        ASSERT_EQ(image.getHeight(), 2);
        ASSERT_EQ(image.getSize(), 12);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Vector4(0, 0, 254, 255));
        ASSERT_EQ(image.getPixel(0, 1), Michka::Vector4(0, 0, 254, 255));
        ASSERT_EQ(image.getPixel(1, 0), Michka::Vector4(0, 0, 254, 255));
        ASSERT_EQ(image.getPixel(1, 1), Michka::Vector4(0, 0, 254, 255));
    }

    {
        Michka::Image image(testFilePath + "/color_test.jpg");
        ASSERT_EQ(image.getWidth(), 2);
        ASSERT_EQ(image.getHeight(), 2);
        ASSERT_EQ(image.getSize(), 12);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Vector4(254, 0, 0, 255));
        ASSERT_EQ(image.getPixel(1, 0), Michka::Vector4(0, 255, 1, 255));
        ASSERT_EQ(image.getPixel(0, 1), Michka::Vector4(0, 0, 254, 255));
        ASSERT_EQ(image.getPixel(1, 1), Michka::Vector4(255, 255, 255, 255));
    }

    {
        Michka::Image image(testFilePath + "/alpha_test.png");
        ASSERT_EQ(image.getWidth(), 2);
        ASSERT_EQ(image.getHeight(), 2);
        ASSERT_EQ(image.getSize(), 16);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Vector4(255, 0, 0, 255));
        ASSERT_EQ(image.getPixel(1, 0), Michka::Vector4(0, 255, 0, 255));
        ASSERT_EQ(image.getPixel(0, 1), Michka::Vector4(0, 0, 255, 255));
        ASSERT_EQ(image.getPixel(1, 1), Michka::Vector4(255, 255, 255, 0));
    }
}
