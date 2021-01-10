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
#include "Core/Foundation/File.h"

TEST(FileTest, Append)
{
    Michka::String testFilePath = Michka::File::realpath(Michka::String(MICHKA_TESTS_PATH) + "/Files/Core/file_test_append.txt");
    Michka::String testFileContents = "Hello\nWorld";
    Michka::File file(testFilePath, Michka::File::OpenMode::writeOnly);
    file.write(testFileContents);
    file.close();
    ASSERT_EQ(Michka::File::getContents(testFilePath), testFileContents);
    file.open(testFilePath, Michka::File::OpenMode::append);
    file.write("\nTest");
    file.close();
    ASSERT_EQ(Michka::File::getContents(testFilePath), testFileContents + "\nTest");

    file.open(testFilePath, Michka::File::OpenMode::readAppend);
    file.write(".");
    file.flush();
    ASSERT_EQ(file.readAll(), testFileContents + "\nTest.");
    file.close();

    ASSERT_TRUE(Michka::File::remove(testFilePath));
}

TEST(FileTest, CreateDirectory)
{
    Michka::String testDirectory = Michka::File::realpath(Michka::String(MICHKA_TESTS_PATH) + "/Files/Core/TestDirectory");
    ASSERT_FALSE(Michka::File::isDirectory(testDirectory));
    Michka::File::createDirectory(testDirectory);
    ASSERT_TRUE(Michka::File::isDirectory(testDirectory));
    Michka::File::remove(testDirectory);
    ASSERT_FALSE(Michka::File::isDirectory(testDirectory));
}

TEST(FileTest, EmptyFile)
{
    Michka::File file;

    ASSERT_FALSE(file.isOpen());
    ASSERT_EQ(file.getSize(), 0);
    ASSERT_FALSE(file.isEndOfFile());
    ASSERT_EQ(file.getPath(), Michka::String::empty);
    ASSERT_EQ(file.getDirectory(), Michka::String::empty);
    ASSERT_EQ(file.getFileName(), Michka::String::empty);
    ASSERT_EQ(file.readAll(), Michka::String::empty);
    ASSERT_FALSE(file.seek(0));
    ASSERT_EQ(file.readLine(), Michka::String::empty);
    ASSERT_FALSE(file.seek(0));
    ASSERT_EQ(file.readCharacter(), '\0');
    ASSERT_FALSE(file.flush());
    ASSERT_FALSE(file.write("Hello"));
}

TEST(FileTest, Exists)
{
    Michka::String testFileDirectory = Michka::File::realpath(Michka::String(MICHKA_TESTS_PATH) + "/Files/Core");
    ASSERT_TRUE(Michka::File::exists(testFileDirectory + "/file_test_read.txt"));
    ASSERT_FALSE(Michka::File::exists(testFileDirectory + "/not_exists.txt"));
}

TEST(FileTest, IsDirectory)
{
    Michka::String testFileDirectory = Michka::File::realpath(Michka::String(MICHKA_TESTS_PATH) + "/Files/Core");
    ASSERT_TRUE(Michka::File::isDirectory(testFileDirectory));
    ASSERT_FALSE(Michka::File::isDirectory(testFileDirectory + "/file_test_read.txt"));
}

TEST(FileTest, IsFile)
{
    Michka::String testFileDirectory = Michka::File::realpath(Michka::String(MICHKA_TESTS_PATH) + "/Files/Core");
    ASSERT_TRUE(Michka::File::isFile(testFileDirectory + "/file_test_read.txt"));
    ASSERT_FALSE(Michka::File::isFile(testFileDirectory));
}

TEST(FileTest, Read)
{
    Michka::String testFilePath = Michka::File::realpath(Michka::String(MICHKA_TESTS_PATH) + "/Files/Core/file_test_read.txt");
    Michka::String testFileContents = "Hello\nWorld\nMichka";
    Michka::File file(testFilePath, Michka::File::OpenMode::readOnly);

    ASSERT_TRUE(file.isOpen());
    ASSERT_EQ(file.getSize(), 20);
    ASSERT_FALSE(file.isEndOfFile());
    ASSERT_EQ(file.getPath(), testFilePath);
    ASSERT_EQ(file.getDirectory(), Michka::File::realpath(Michka::String(MICHKA_TESTS_PATH) + "/Files/Core"));
    ASSERT_EQ(file.getFileName(), "file_test_read.txt");
    ASSERT_EQ(file.readAll(), testFileContents);
    ASSERT_TRUE(file.seek(0));
    ASSERT_EQ(file.readLine(), "Hello\n");
    ASSERT_EQ(file.readLine(), "World\n");
    ASSERT_EQ(file.readLine(), "Michka");
    ASSERT_EQ(file.readLine(), Michka::String::empty);
    ASSERT_TRUE(file.seek(0));
    ASSERT_EQ(file.readCharacter(), 'H');
    ASSERT_EQ(file.readCharacter(), 'e');
    ASSERT_EQ(file.readCharacter(), 'l');
    ASSERT_EQ(file.readCharacter(), 'l');
    ASSERT_EQ(file.readCharacter(), 'o');
    ASSERT_EQ(file.readCharacter(), '\n');
    ASSERT_EQ(Michka::File::getContents(testFilePath), testFileContents);
}

TEST(FileTest, Remove)
{
    Michka::String testFilePath = Michka::File::realpath(Michka::String(MICHKA_TESTS_PATH) + "/Files/Core/file_test_remove.txt");
    ASSERT_FALSE(Michka::File::exists(testFilePath));
    ASSERT_TRUE(Michka::File::putContents(testFilePath, "Hello"));
    ASSERT_TRUE(Michka::File::exists(testFilePath));
    ASSERT_TRUE(Michka::File::remove(testFilePath));
    ASSERT_FALSE(Michka::File::exists(testFilePath));
}

TEST(FileTest, Write)
{
    Michka::String testFilePath = Michka::File::realpath(Michka::String(MICHKA_TESTS_PATH) + "/Files/Core/file_test_write.txt");
    Michka::String testFileContents = "Hello\nWorld";
    Michka::File file(testFilePath, Michka::File::OpenMode::writeOnly);
    file.write(testFileContents);
    file.close();
    ASSERT_EQ(Michka::File::getContents(testFilePath), testFileContents);
    ASSERT_TRUE(Michka::File::remove(testFilePath));

    file.open(testFilePath, Michka::File::OpenMode::writeOnly | Michka::File::OpenMode::binary);
    file.write(testFileContents);
    file.close();
    file.open(testFilePath, Michka::File::OpenMode::readOnly | Michka::File::OpenMode::binary);
    ASSERT_EQ(file.readAll(), testFileContents);
    file.close();
    file.open(testFilePath, Michka::File::OpenMode::readWrite);
    file.write(testFileContents);
    file.flush();
    ASSERT_EQ(file.readAll(), testFileContents);
    file.close();

    ASSERT_TRUE(Michka::File::remove(testFilePath));
}
