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
            ReadOnly  = 1 << 0,
            WriteOnly = 1 << 1,
            Binary    = 1 << 2,
            Append    = 1 << 3,
            ReadWrite = ReadOnly | WriteOnly
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
         * @brief Get full path of file.
         *
         * @return String
         */
        String getPath() const;

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
         * @brief Get the position of file stream.
         *
         * @return i32 . returns negetive value if file is not valid or not opened yet.
         */
        i32 getPosition() const;

        /**
         * @brief Open file.
         *
         * @param _path
         * @param _openmode
         * @return false if opening file failed.
         */
        bool open(const String& _path, const OpenMode& _openmode = OpenMode::ReadOnly);

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
