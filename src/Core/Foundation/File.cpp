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

    String File::directory(const String& _path)
    {
        String path = realpath(_path);
        auto pathSplited = path.split('/');
        pathSplited.remove(pathSplited.getSize() - 1);
        return pathSplited.implode("/");
    }

    bool File::exists(const String& _path)
    {
        return std::filesystem::exists(_path.toUtf8().cstr());
    }

    String File::filename(const String& _path)
    {
        String path = realpath(_path);

        auto pathSplited = path.split('/');
        if (pathSplited.getSize() - 1 > 0)
        {
            pathSplited.remove(0, pathSplited.getSize() - 1);
        }
        return pathSplited.implode("/");
    }

    bool File::flush()
    {
        if(mFile == nullptr)
        {
            return false;
        }

        return fflush(mFile) == 0;
    }

    String File::getContents(const String& _path)
    {
        return File(_path).readAll();
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

        return directory(mPath);
    }

    String File::getFileName() const
    {
        if(mFile == nullptr)
        {
            return String::empty;
        }

        return filename(mPath);
    }

    i32 File::getPosition() const
    {
        if(mFile == nullptr)
        {
            return -1;
        }

        return ftell(mFile);
    }

    u32 File::getSize()
    {
        if(mFile == nullptr)
        {
            return 0;
        }

        i32 position = getPosition();
        seek(-1);
        u32 size = getPosition();
        seek(position);

        return size;
    }

    bool File::isEndOfFile() const
    {
        if (mFile == nullptr)
        {
            return false;
        }

        return feof(mFile);
    }

    bool File::isOpen() const
    {
        return mFile != nullptr;
    }

    bool File::open(const String& _path, const OpenMode& _openmode)
    {
        close();
        mPath = realpath(_path);
        String8 path = mPath.toUtf8();
        String8 openmode;
        switch (_openmode & 0x07)
        {
            case OpenMode::readOnly:
                openmode += "r";
                break;
            case OpenMode::writeOnly:
                openmode += "w";
                break;
            case OpenMode::append:
                openmode += "a";
                break;
            case OpenMode::readAppend:
                openmode += "a+";
                break;
            case OpenMode::readWrite:
                openmode += "r+";
                break;
        }
        if ((_openmode & OpenMode::binary) == OpenMode::binary)
        {
            openmode += "b";
        }

        mFile = fopen(path.cstr(), openmode.cstr());

        return mFile != nullptr;
    }

    bool File::putContents(const String& _path, const String& _contents)
    {
        return File(_path, OpenMode::writeOnly).write(_contents);
    }

    bool File::read(void* _buffer, const u32& _size)
    {
        if (mFile == nullptr)
        {
            return false;
        }

        return fread(_buffer, 1, _size, mFile) != 0;
    }

    String File::readAll()
    {
        i32 position = getPosition();
        u32 fileSize = getSize();
        char* fileContent = new char[fileSize + 1];
        memset((void*)fileContent, 0, sizeof(char) * (fileSize + 1));

        seek(0);
        read((void*)fileContent, fileSize);
        fileContent[fileSize] = '\0';

        String output = String::fromUtf8(fileContent);
        delete[] fileContent;

        seek(position);

        return output;
    }

    char File::readCharacter()
    {
        if (mFile == nullptr)
        {
            return '\0';
        }

        return fgetc(mFile);
    }

    String File::readLine()
    {
        if (mFile == nullptr)
        {
            return String::empty;
        }

        char line[2048];
        if (fgets(line, 2048, mFile))
        {
            return line;
        }

        return String::empty;
    }

    String File::realpath(const String& _path)
    {
        return String(std::filesystem::absolute(_path.toUtf8().cstr()).c_str()).getReplaced("\\", "/");
    }

    bool File::remove(const String& _path)
    {
        return exists(_path) && std::filesystem::remove(_path.toUtf8().cstr());
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
