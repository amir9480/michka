// ------------------------------------------------------------------------------- //
//                                     Michka                                      //
// ------------------------------------------------------------------------------- //
//                                  MIT License                                    //
//                                                                                 //
// Copyright (c) 2020-2021 amir alizadeh.                                          //
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
#include "MichkaTests.h"
#include "Core/Container/String.h"
#include "Core/Foundation/File.h"
#include "Graphics/Image.h"

TEST(ImageTest, Compare)
{
    Michka::String testFilePath = Michka::String(MICHKA_TESTS_PATH) + "/Files/Graphics/Images";

    {
        Michka::Image a;
        Michka::Image b;
        ASSERT_EQ(a, b);
    }
    {
        Michka::Image a(testFilePath + "/color_test.jpg");
        Michka::Image b;
        ASSERT_NE(a, b);
    }
    {
        Michka::Image a(testFilePath + "/color_test.jpg");
        Michka::Image b(testFilePath + "/color_test.jpg");
        ASSERT_EQ(a, b);
    }
    {
        Michka::Image a(testFilePath + "/green2.jpg");
        Michka::Image b(testFilePath + "/red2.jpg");
        ASSERT_NE(a, b);
    }
}

TEST(ImageTest, Flip)
{
    Michka::String testFilePath = Michka::String(MICHKA_TESTS_PATH) + "/Files/Graphics/Images";

    {
        Michka::Image image;
        ASSERT_FALSE(image.flip());
    }
    // Horizontal
    {
        Michka::Image image(testFilePath + "/color_test.jpg");
        ASSERT_EQ(image.getPixel(0, 0), Michka::Color::red);
        ASSERT_EQ(image.getPixel(1, 0), Michka::Color::green);
        ASSERT_EQ(image.getPixel(0, 1), Michka::Color::blue);
        ASSERT_EQ(image.getPixel(1, 1), Michka::Color::white);

        Michka::Image image2 = image.getFlipped(true, false);
        ASSERT_EQ(image2.getPixel(1, 0), Michka::Color::red);
        ASSERT_EQ(image2.getPixel(0, 0), Michka::Color::green);
        ASSERT_EQ(image2.getPixel(1, 1), Michka::Color::blue);
        ASSERT_EQ(image2.getPixel(0, 1), Michka::Color::white);
    }
    {
        Michka::Image image(testFilePath + "/color_test2.jpg");
        ASSERT_EQ(image.getPixel(0, 0), Michka::Color::white);
        ASSERT_EQ(image.getPixel(1, 1), Michka::Color::red);
        ASSERT_EQ(image.getPixel(3, 1), Michka::Color::green);
        ASSERT_EQ(image.getPixel(2, 2), Michka::Color::black);
        ASSERT_EQ(image.getPixel(1, 3), Michka::Color::blue);
        ASSERT_EQ(image.getPixel(3, 3), Michka::Color::yellow);
        ASSERT_EQ(image.getPixel(4, 4), Michka::Color::white);

        ASSERT_TRUE(image.flip(true, false));
        ASSERT_EQ(image.getPixel(4, 0), Michka::Color::white);
        ASSERT_EQ(image.getPixel(3, 1), Michka::Color::red);
        ASSERT_EQ(image.getPixel(1, 1), Michka::Color::green);
        ASSERT_EQ(image.getPixel(2, 2), Michka::Color::black);
        ASSERT_EQ(image.getPixel(3, 3), Michka::Color::blue);
        ASSERT_EQ(image.getPixel(1, 3), Michka::Color::yellow);
        ASSERT_EQ(image.getPixel(0, 4), Michka::Color::white);
    }

    // Vertical
    {
        Michka::Image image(testFilePath + "/color_test.jpg");
        ASSERT_EQ(image.getPixel(0, 0), Michka::Color::red);
        ASSERT_EQ(image.getPixel(1, 0), Michka::Color::green);
        ASSERT_EQ(image.getPixel(0, 1), Michka::Color::blue);
        ASSERT_EQ(image.getPixel(1, 1), Michka::Color::white);

        ASSERT_TRUE(image.flip());
        ASSERT_EQ(image.getPixel(0, 0), Michka::Color::blue);
        ASSERT_EQ(image.getPixel(1, 0), Michka::Color::white);
        ASSERT_EQ(image.getPixel(0, 1), Michka::Color::red);
        ASSERT_EQ(image.getPixel(1, 1), Michka::Color::green);
    }
    {
        Michka::Image image(testFilePath + "/color_test2.jpg");
        ASSERT_EQ(image.getPixel(0, 0), Michka::Color::white);
        ASSERT_EQ(image.getPixel(1, 1), Michka::Color::red);
        ASSERT_EQ(image.getPixel(3, 1), Michka::Color::green);
        ASSERT_EQ(image.getPixel(2, 2), Michka::Color::black);
        ASSERT_EQ(image.getPixel(1, 3), Michka::Color::blue);
        ASSERT_EQ(image.getPixel(3, 3), Michka::Color::yellow);
        ASSERT_EQ(image.getPixel(4, 4), Michka::Color::white);

        ASSERT_TRUE(image.flip());
        ASSERT_EQ(image.getPixel(0, 4), Michka::Color::white);
        ASSERT_EQ(image.getPixel(1, 3), Michka::Color::red);
        ASSERT_EQ(image.getPixel(3, 3), Michka::Color::green);
        ASSERT_EQ(image.getPixel(2, 2), Michka::Color::black);
        ASSERT_EQ(image.getPixel(1, 1), Michka::Color::blue);
        ASSERT_EQ(image.getPixel(3, 1), Michka::Color::yellow);
        ASSERT_EQ(image.getPixel(4, 0), Michka::Color::white);
    }
}

TEST(ImageTest, LoadFromFile)
{
    Michka::String testFilePath = Michka::String(MICHKA_TESTS_PATH) + "/Files/Graphics/Images";
    {
        Michka::Image image(testFilePath + "/black1.jpg");
        ASSERT_EQ(image.getFormat(), Michka::Image::Format::r8g8b8);
        ASSERT_EQ(image.getWidth(), 1);
        ASSERT_EQ(image.getHeight(), 1);
        ASSERT_EQ(image.getSize(), 3);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Color::black);
    }
    {
        Michka::Image image(testFilePath + "/white1.jpg");
        ASSERT_EQ(image.getFormat(), Michka::Image::Format::r8g8b8);
        ASSERT_EQ(image.getWidth(), 1);
        ASSERT_EQ(image.getHeight(), 1);
        ASSERT_EQ(image.getSize(), 3);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Color::white);
    }
    {
        Michka::Image image(testFilePath + "/red1.jpg");
        ASSERT_EQ(image.getFormat(), Michka::Image::Format::r8g8b8);
        ASSERT_EQ(image.getWidth(), 1);
        ASSERT_EQ(image.getHeight(), 1);
        ASSERT_EQ(image.getSize(), 3);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Color::red);
    }
    {
        Michka::Image image(testFilePath + "/green1.jpg");
        ASSERT_EQ(image.getFormat(), Michka::Image::Format::r8g8b8);
        ASSERT_EQ(image.getWidth(), 1);
        ASSERT_EQ(image.getHeight(), 1);
        ASSERT_EQ(image.getSize(), 3);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Color::green);
    }
    {
        Michka::Image image(testFilePath + "/blue1.jpg");
        ASSERT_EQ(image.getFormat(), Michka::Image::Format::r8g8b8);
        ASSERT_EQ(image.getWidth(), 1);
        ASSERT_EQ(image.getHeight(), 1);
        ASSERT_EQ(image.getSize(), 3);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Color::blue);
    }

    {
        Michka::Image image(testFilePath + "/black2.jpg");
        ASSERT_EQ(image.getFormat(), Michka::Image::Format::r8g8b8);
        ASSERT_EQ(image.getWidth(), 2);
        ASSERT_EQ(image.getHeight(), 2);
        ASSERT_EQ(image.getSize(), 12);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Color::black);
        ASSERT_EQ(image.getPixel(0, 1), Michka::Color::black);
        ASSERT_EQ(image.getPixel(1, 0), Michka::Color::black);
        ASSERT_EQ(image.getPixel(1, 1), Michka::Color::black);
    }
    {
        Michka::Image image(testFilePath + "/white2.jpg");
        ASSERT_EQ(image.getFormat(), Michka::Image::Format::r8g8b8);
        ASSERT_EQ(image.getWidth(), 2);
        ASSERT_EQ(image.getHeight(), 2);
        ASSERT_EQ(image.getSize(), 12);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Color::white);
        ASSERT_EQ(image.getPixel(0, 1), Michka::Color::white);
        ASSERT_EQ(image.getPixel(1, 0), Michka::Color::white);
        ASSERT_EQ(image.getPixel(1, 1), Michka::Color::white);
    }
    {
        Michka::Image image(testFilePath + "/red2.jpg");
        ASSERT_EQ(image.getFormat(), Michka::Image::Format::r8g8b8);
        ASSERT_EQ(image.getWidth(), 2);
        ASSERT_EQ(image.getHeight(), 2);
        ASSERT_EQ(image.getSize(), 12);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Color::red);
        ASSERT_EQ(image.getPixel(0, 1), Michka::Color::red);
        ASSERT_EQ(image.getPixel(1, 0), Michka::Color::red);
        ASSERT_EQ(image.getPixel(1, 1), Michka::Color::red);
    }
    {
        Michka::Image image(testFilePath + "/green2.jpg");
        ASSERT_EQ(image.getFormat(), Michka::Image::Format::r8g8b8);
        ASSERT_EQ(image.getWidth(), 2);
        ASSERT_EQ(image.getHeight(), 2);
        ASSERT_EQ(image.getSize(), 12);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Color::green);
        ASSERT_EQ(image.getPixel(0, 1), Michka::Color::green);
        ASSERT_EQ(image.getPixel(1, 0), Michka::Color::green);
        ASSERT_EQ(image.getPixel(1, 1), Michka::Color::green);
    }
    {
        Michka::Image image(testFilePath + "/blue2.jpg");
        ASSERT_EQ(image.getFormat(), Michka::Image::Format::r8g8b8);
        ASSERT_EQ(image.getWidth(), 2);
        ASSERT_EQ(image.getHeight(), 2);
        ASSERT_EQ(image.getSize(), 12);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Color::blue);
        ASSERT_EQ(image.getPixel(0, 1), Michka::Color::blue);
        ASSERT_EQ(image.getPixel(1, 0), Michka::Color::blue);
        ASSERT_EQ(image.getPixel(1, 1), Michka::Color::blue);
    }

    {
        Michka::Image image(testFilePath + "/color_test.jpg");
        ASSERT_EQ(image.getFormat(), Michka::Image::Format::r8g8b8);
        ASSERT_EQ(image.getWidth(), 2);
        ASSERT_EQ(image.getHeight(), 2);
        ASSERT_EQ(image.getSize(), 12);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Color::red);
        ASSERT_EQ(image.getPixel(1, 0), Michka::Color::green);
        ASSERT_EQ(image.getPixel(0, 1), Michka::Color::blue);
        ASSERT_EQ(image.getPixel(1, 1), Michka::Color::white);
    }

    {
        Michka::Image image(testFilePath + "/alpha_test.png");
        ASSERT_EQ(image.getFormat(), Michka::Image::Format::r8g8b8a8);
        ASSERT_EQ(image.getWidth(), 2);
        ASSERT_EQ(image.getHeight(), 2);
        ASSERT_EQ(image.getSize(), 16);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Color::red);
        ASSERT_EQ(image.getPixel(1, 0), Michka::Color::green);
        ASSERT_EQ(image.getPixel(0, 1), Michka::Color::blue);
        ASSERT_EQ(image.getPixel(1, 1), Michka::Color(255, 255, 255, 0));

        ASSERT_EQ(image.getPixel(1, 2), Michka::Color::black); // out of range
        ASSERT_EQ(image.getPixel(2, 1), Michka::Color::black); // out of range
        ASSERT_EQ(image.getPixel(2, 2), Michka::Color::black); // out of range

        ASSERT_EQ(image.getData()[0], 255);
        ASSERT_EQ(image.getData()[1], 0);
    }
}

TEST(ImageTest, SaveToFile)
{
    Michka::String testFilePath = Michka::String(MICHKA_TESTS_PATH) + "/Files/Graphics/Images";
    {
        Michka::Image imageWrite(testFilePath + "/color_test.jpg");
        ASSERT_TRUE(imageWrite.save(testFilePath + "/Output/color_test.jpg"));

        Michka::Image image(testFilePath + "/Output/color_test.jpg");
        ASSERT_EQ(image.getWidth(), 2);
        ASSERT_EQ(image.getHeight(), 2);
        ASSERT_EQ(image.getSize(), 12);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Color::red);
        ASSERT_EQ(image.getPixel(1, 0), Michka::Color::green);
        ASSERT_EQ(image.getPixel(0, 1), Michka::Color::blue);
        ASSERT_EQ(image.getPixel(1, 1), Michka::Color::white);
    }
    {
        Michka::Image imageWrite(testFilePath + "/alpha_test.png");
        ASSERT_TRUE(imageWrite.save(testFilePath + "/Output/alpha_test.png"));

        Michka::Image image(testFilePath + "/Output/alpha_test.png");
        ASSERT_EQ(image.getWidth(), 2);
        ASSERT_EQ(image.getHeight(), 2);
        ASSERT_EQ(image.getSize(), 16);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Color::red);
        ASSERT_EQ(image.getPixel(1, 0), Michka::Color::green);
        ASSERT_EQ(image.getPixel(0, 1), Michka::Color::blue);
        ASSERT_EQ(image.getPixel(1, 1), Michka::Color(255, 255, 255, 0));
    }
    {
        Michka::Image imageWrite(testFilePath + "/color_test.jpg");
        ASSERT_TRUE(imageWrite.save(testFilePath + "/Output/Test/color_test.bmp"));
        ASSERT_TRUE(imageWrite.save(testFilePath + "/Output/Test/color_test.bmp")); // To test file overwrite

        Michka::Image image(testFilePath + "/Output/Test/color_test.bmp");
        ASSERT_EQ(image.getWidth(), 2);
        ASSERT_EQ(image.getHeight(), 2);
        ASSERT_EQ(image.getSize(), 12);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Color::red);
        ASSERT_EQ(image.getPixel(1, 0), Michka::Color::green);
        ASSERT_EQ(image.getPixel(0, 1), Michka::Color::blue);
        ASSERT_EQ(image.getPixel(1, 1), Michka::Color::white);
    }
    ASSERT_TRUE(Michka::File::remove(testFilePath + "/Output/color_test.jpg"));
    ASSERT_TRUE(Michka::File::remove(testFilePath + "/Output/alpha_test.png"));
    ASSERT_TRUE(Michka::File::remove(testFilePath + "/Output/Test"));
}

TEST(ImageTest, Set)
{
    u8* imageData = new u8[3]();
    imageData[1] = 255;
    Michka::Image image;
    image.set(1, 1, Michka::Image::Format::r8g8b8, imageData);

    ASSERT_EQ(image.getFormat(), Michka::Image::Format::r8g8b8);
    ASSERT_EQ(image.getWidth(), 1);
    ASSERT_EQ(image.getHeight(), 1);
    ASSERT_EQ(image.getPixel(0, 0), Michka::Color::green);
}

TEST(ImageTest, SetPixel)
{
    Michka::String testFilePath = Michka::String(MICHKA_TESTS_PATH) + "/Files/Graphics/Images";
    {
        Michka::Image image(1, 1, Michka::Image::Format::unknown, new u8[1]);
        ASSERT_FALSE(image.setPixel(0, 0, Michka::Color::cyan));
    }
    {
        Michka::Image image(testFilePath + "/color_test.jpg");
        ASSERT_EQ(image.getFormat(), Michka::Image::Format::r8g8b8);
        ASSERT_EQ(image.getWidth(), 2);
        ASSERT_EQ(image.getHeight(), 2);
        ASSERT_EQ(image.getSize(), 12);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Color::red);
        ASSERT_EQ(image.getPixel(1, 0), Michka::Color::green);
        ASSERT_EQ(image.getPixel(0, 1), Michka::Color::blue);
        ASSERT_EQ(image.getPixel(1, 1), Michka::Color::white);

        image.setPixel(0, 1, Michka::Color::cyan);

        ASSERT_EQ(image.getPixel(0, 0), Michka::Color::red);
        ASSERT_EQ(image.getPixel(1, 0), Michka::Color::green);
        ASSERT_EQ(image.getPixel(0, 1), Michka::Color::cyan);
        ASSERT_EQ(image.getPixel(1, 1), Michka::Color::white);
    }
    {
        Michka::Image image(testFilePath + "/alpha_test.png");
        ASSERT_EQ(image.getFormat(), Michka::Image::Format::r8g8b8a8);
        ASSERT_EQ(image.getWidth(), 2);
        ASSERT_EQ(image.getHeight(), 2);
        ASSERT_EQ(image.getSize(), 16);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Color::red);
        ASSERT_EQ(image.getPixel(1, 0), Michka::Color::green);
        ASSERT_EQ(image.getPixel(0, 1), Michka::Color::blue);
        ASSERT_EQ(image.getPixel(1, 1), Michka::Color(255, 255, 255, 0));

        image.setPixel(1, 1, Michka::Color::cyan);

        ASSERT_EQ(image.getPixel(0, 0), Michka::Color::red);
        ASSERT_EQ(image.getPixel(1, 0), Michka::Color::green);
        ASSERT_EQ(image.getPixel(0, 1), Michka::Color::blue);
        ASSERT_EQ(image.getPixel(1, 1), Michka::Color::cyan);
    }
}

TEST(ImageTest, UnknownFormat)
{
    {
        u8* testBuffer = new u8[16];
        Michka::Image image(4, 4, Michka::Image::Format::unknown, testBuffer);
        ASSERT_EQ(image.getBytesPerPixel(), 0);
        ASSERT_EQ(image.getPixel(0, 0), Michka::Color::black);
    }
}
