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

#ifndef __FILE_H__
#define __FILE_H__

#include "Core/Defines.h"
#include "Core/Helpers.h"
#include "Core/Container/String.h"

namespace Michka
{
    class MICHKA_API File
    {
    public:
        enum class OpenMode
        {
            ReadOnly   = 1 << 0,
            WriteOnly  = 1 << 1,
            Append     = 1 << 2,
            Binary     = 1 << 3,
            ReadAppend = ReadOnly | Append,
            ReadWrite  = ReadOnly | WriteOnly,
        };

    public:
        File();
        File(const String& _path, const OpenMode& _openmode = OpenMode::ReadOnly);
        ~File();

        /**
         * @brief Close open file.
         */
        void close();

        /**
         * @brief Extract directory from file path.
         *
         * @param _path
         * @return String
         */
        static String directory(const String& _path);

        /**
         * @brief Check file exists.
         *
         * @param _path
         */
        static bool exists(const String& _path);

        /**
         * @brief Extract filename from file path.
         *
         * @param _path
         * @return String
         */
        static String filename(const String& _path);

        /**
         * @brief Flush buffer to file.
         *
         * @return false if failed.
         */
        bool flush();

        /**
         * @brief Get contents of a file.
         *
         * @param _path
         * @return String
         */
        static String getContents(const String& _path);

        /**
         * @brief Get the directory of the file.
         *
         * @return String
         */
        String getDirectory() const;

        /**
         * @brief Get the directory of the file.
         *
         * @return String
         */
        String getFileName() const;

        /**
         * @brief Get full path of file.
         *
         * @return String
         */
        String getPath() const;

        /**
         * @brief Get the position of file stream.
         *
         * @return i32 . returns negetive value if file is not valid or not opened yet.
         */
        i32 getPosition() const;

        /**
         * @brief Get the file size in bytes.
         *
         * @return u32
         */
        u32 getSize();

        /**
         * @brief Is pointer at end of file.
         */
        bool isEndOfFile() const;

        /**
         * @brief Check file is open.
         */
        bool isOpen() const;

        /**
         * @brief Open file.
         *
         * @param _path
         * @param _openmode
         * @return false if opening file failed.
         */
        bool open(const String& _path, const OpenMode& _openmode = OpenMode::ReadOnly);

        /**
         * @brief Put string to a file.
         *
         * @param _path
         * @param _contents
         * @return false if failed.
         */
        static bool putContents(const String& _path, const String& _contents);

        /**
         * @brief Read file.
         *
         * @param _buffer
         * @param _size
         * @return false if reading file failed.
         */
        bool read(void* _buffer, const u32& _size);

        /**
         * @brief Get all file content as a string.
         *
         * @return char
         */
        String readAll();

        /**
         * @brief Get file content character by character.
         *
         * @return char
         */
        char readCharacter();

        /**
         * @brief Get file content line by line.
         *
         * @return char
         */
        String readLine();

        /**
         * @brief Get full absolute path.
         *
         * @param _path
         * @return String
         */
        static String realpath(const String& _path);

        /**
         * @brief Remove file.
         *
         * @param _path
         * @return true if deleted successfully
         */
        static bool remove(const String& _path);

        /**
         * @brief Seek file stream position.
         *
         * @param _pos  position to seek. pass -1 to seek to end of file.
         * @return false if seek failed.
         */
        bool seek(const i32& _pos);

        /**
         * @brief Write data on file.
         *
         * @param _data
         * @param _size
         * @return returns false if writing to file failed.
         */
        bool write(const void* _data, u32 _size);

        /**
         * @brief Write text on file.
         *
         * @param _string
         * @return returns false if writing to file failed.
         */
        bool write(const String& _string);

    protected:
        FILE* mFile = nullptr;
        String mPath;
    };

    MICHKA_ENUM_OPERATORS(File::OpenMode);
}

#endif // __FILE_H__
