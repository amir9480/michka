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

#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "Core/Defines.h"
#include "Core/Foundation/Object.h"

namespace Michka
{
    class MICHKA_API Window : public Object
    {
        MICHKA_NON_COPYABLE_CLASS(Window)
    public:
        Window(const u32& _width, const u32& _height);
        ~Window();

        /**
         * @brief Destroy window.
         */
        void destroy();

        /**
         * @brief Get the Height of window
         */
        u32 getHeight() const;

        /**
         * @brief Get the Width of window
         */
        u32 getWidth() const;

        /**
         * @brief Check window destroyed or not.
         */
        bool isDestroyed();

        /**
         * @brief Resize window.
         *
         * @param _width
         * @param _height
         */
        void resize(const u32& _width, const u32& _height);

        /**
         * @brief Set the Height of window.
         *
         * @param _height
         */
        void setHeight(const u32& _height);

        /**
         * @brief Set window title.
         *
         * @param _title
         */
        void setTitle(const String& _title);

        /**
         * @brief Set the Width of window
         *
         * @param _width
         */
        void setWidth(const u32& _width);

    protected:
        /**
         * @brief callback to handle window event.
         *
         * @param _event
         */
        virtual bool onEvent(const Event* _event) override;

    protected:
        u32 mWidth = 640;
        u32 mHeight = 480;
        bool mDestroyed = false;
        bool mCallEventListenersManually = true;
    };
}

#endif // __WINDOW_H__
