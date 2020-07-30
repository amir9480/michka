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
#include <utility>
#include "Core/Container/Variant.h"
#include "../../Classes/Person.h"

TEST(VariantTest, CreateTest)
{
    {
        Michka::Variant a;
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeNull);
        ASSERT_EQ(a.to<int>(), 0);
    }
    {
        Michka::Variant a(nullptr);
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeNull);
        ASSERT_EQ(a.to<int>(), 0);
    }
    {
        Michka::Variant a(true);
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeBool);
        ASSERT_EQ(a.to<int>(), 1);
        ASSERT_EQ(a.to<bool>(), true);

        a = false;
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeBool);
        ASSERT_EQ(a.to<int>(), 0);
        ASSERT_EQ(a.to<bool>(), 0);

        a = nullptr;
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeNull);
        ASSERT_EQ(a.to<bool>(), false);
    }
    {
        Michka::Variant a(5);
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeInt);
        ASSERT_EQ(a.to<int>(), 5);
        ASSERT_EQ(a.to<bool>(), true);

        a = 8;
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeInt);
        ASSERT_EQ(a.to<int>(), 8);
        ASSERT_EQ(a.to<bool>(), true);

        a = 3.14;
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeFloat);
        ASSERT_EQ(a.to<int>(), 3);
        ASSERT_EQ(a.to<bool>(), true);
        ASSERT_FLOAT_EQ(a.to<float>(), 3.14f);
    }
    {
        Michka::Variant a(3.14);
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeFloat);
        ASSERT_EQ(a.to<int>(), 3);
        ASSERT_FLOAT_EQ(a.to<float>(), 3.14f);

        a = 9.99;
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeFloat);
        ASSERT_EQ(a.to<int>(), 9);
        ASSERT_FLOAT_EQ(a.to<float>(), 9.99f);
    }
    {
        Michka::Variant a("3.14");
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeString);
        ASSERT_EQ(a.to<int>(), 3);
        ASSERT_EQ(a.to<Michka::String>(), "3.14");
        ASSERT_FLOAT_EQ(a.to<float>(), 3.14f);

        a = "Hello World";
        ASSERT_EQ(a.getType(), Michka::Variant::Type::typeString);
        ASSERT_EQ(a.to<Michka::String>(), "Hello World");
        ASSERT_EQ(a.to<Michka::String8>(), "Hello World");
        ASSERT_EQ(a.to<Michka::String32>(), U"Hello World");
    }
}
