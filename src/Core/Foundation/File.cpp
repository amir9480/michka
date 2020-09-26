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

#include "File.h"
#include <filesystem>

namespace Michka
{
    File::File()
    {
        //
    }

    File::File(const String& _path, const OpenMode& _openmode)
    {
        open(_path, _openmode);
    }

    File::~File()
    {
        close();
    }

    void File::close()
    {
        if (mFile)
        {
            fclose(mFile);
            mFile = nullptr;
            mPath.clear();
        }
    }

    String File::getPath() const
    {
        return mPath;
    }

    String File::getDirectory() const
    {
        if(mFile == nullptr)
        {
            return String::empty;
        }

        auto pathSplited = mPath.split('/');
        pathSplited.remove(pathSplited.getSize() - 1);
        return pathSplited.implode("/");
    }

    String File::getFileName() const
    {
        if(mFile == nullptr)
        {
            return String::empty;
        }

        auto pathSplited = mPath.split('/');
        if (pathSplited.getSize() - 1 > 0)
        {
            pathSplited.remove(0, pathSplited.getSize() - 1);
        }
        return pathSplited.implode("/");
    }

    i32 File::getPosition() const
    {
        if(mFile == nullptr)
        {
            return -1;
        }

        return ftell(mFile);
    }

    bool File::open(const String& _path, const OpenMode& _openmode)
    {
        close();
        mPath = _path.getReplaced("\\", "/");
        mPath = std::filesystem::absolute(mPath.toUtf8().cstr()).c_str();
        mPath = mPath.getReplaced("\\", "/");
        String8 path = mPath.toUtf8();
        String8 openmode;
        switch (_openmode & 0x03)
        {
            case OpenMode::ReadOnly:
                openmode += "r";
                break;
            case OpenMode::WriteOnly:
                openmode += "w";
                break;
            case OpenMode::ReadWrite:
                openmode += "r+";
                break;
        }
        if ((_openmode & OpenMode::Binary) == OpenMode::Binary)
        {
            openmode += "b";
        }

        mFile = fopen(path.cstr(), openmode.cstr());

        return mFile != nullptr;
    }

    bool File::seek(const i32& _pos)
    {
        if(mFile == nullptr)
        {
            return false;
        }

        if(_pos < 0)
        {
            return fseek(mFile, 0, SEEK_END) == 0;
        }

        return fseek(mFile, _pos, SEEK_SET) == 0;
    }

    bool File::write(const void* _data, u32 _size)
    {
        if (mFile == nullptr)
        {
            return false;
        }

        return fwrite(_data, 1, _size, mFile) > 0;
    }

    bool File::write(const String& _string)
    {
        String8 str = _string.toUtf8();
        return write((void*)str.cstr(), str.getSize());
    }
}
