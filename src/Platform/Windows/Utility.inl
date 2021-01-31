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

#include "Core/Container/String.h"
#include "Platform/Utility.h"
#define HAVE_STRUCT_TIMESPEC
#include <Windows.h>

namespace Michka
{
    namespace Platform
    {
        FORCE_INLINE int getHeight()
        {
            return GetSystemMetrics(SM_CXSCREEN);
        }

        FORCE_INLINE Vector<Size> getPossibleResolutions()
        {
            Vector<Size> out;
            DEVMODE dm = { 0 };
            dm.dmSize = sizeof(dm);
            for (int iModeNum = 0; EnumDisplaySettings(NULL, iModeNum, &dm) != 0; iModeNum++)
            {
                if (dm.dmPelsWidth >= 640 && dm.dmPelsHeight >= 480)
                {
                    out.pushBack(Size(dm.dmPelsWidth, dm.dmPelsHeight));
                }
            }
            out.unique();
            return out;
        }

        FORCE_INLINE int getWidth()
        {
            return GetSystemMetrics(SM_CYSCREEN);
        }

        FORCE_INLINE void messageBox(const String& _text, const String& _title)
        {
#           if (MICHKA_DEBUG)
                if (getenv("MICHKA_TESTING") && strcmp(getenv("MICHKA_TESTING"), "true"))
                {
                    MessageBoxW(0, _text.cstr(), _title.cstr(), MB_OK); // @NOCOVERAGE
                }
#           else
                MessageBoxW(0, _text.cstr(), _title.cstr(), MB_OK);
#           endif
        }

        FORCE_INLINE void setConsoleColor(const ConsoleColor& _textColor, const ConsoleColor& _backgroundColor)
        {
            int textColor = 0;
            int backgroundColor = 0;

            switch (_textColor)
            {
            case ConsoleColor::black:
                textColor = 0;
                break;
            case ConsoleColor::blue:
                textColor = 9;
                break;
            case ConsoleColor::yellow:
                textColor = 14;
                break;
            case ConsoleColor::cyan:
                textColor = 11;
                break;
            case ConsoleColor::green:
                textColor = 10;
                break;
            case ConsoleColor::magenta:
                textColor = 13;
                break;
            case ConsoleColor::red:
                textColor = 12;
                break;
            case ConsoleColor::white:
                textColor = 15;
                break;
            }

            switch (_backgroundColor)
            {
            case ConsoleColor::black:
                backgroundColor = 0;
                break;
            case ConsoleColor::blue:
                backgroundColor = 1;
                break;
            case ConsoleColor::yellow:
                backgroundColor = 6;
                break;
            case ConsoleColor::cyan:
                backgroundColor = 3;
                break;
            case ConsoleColor::green:
                backgroundColor = 2;
                break;
            case ConsoleColor::magenta:
                backgroundColor = 5;
                break;
            case ConsoleColor::red:
                backgroundColor = 4;
                break;
            case ConsoleColor::white:
                backgroundColor = 7;
                break;
            }

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (backgroundColor * 16) + textColor);
        }
    }
}
