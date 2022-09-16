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

#ifndef __EVENT_H__
#define __EVENT_H__

#include <functional>
#include "Core/Helpers.h"
#include "Core/Container/String.h"
#include "Core/Container/Map.h"
#include "Core/Container/Variant.h"

namespace Michka
{
    class MICHKA_API Event
    {
        MICHKA_CLASS();

        friend class EventManager;
    public:
        FORCE_INLINE Event();
        FORCE_INLINE Event(const Event& _event);
        FORCE_INLINE Event(Event&& _event);
        virtual ~Event();

        /**
         * @brief Get event name.
         */
        FORCE_INLINE String getName() const;

        /**
         * @brief Get parameter by name.
         *
         * @param _name
         */
        FORCE_INLINE Variant getParameter(const String& _name) const;

        /**
         * @brief Get all parameters.
         */
        FORCE_INLINE const Map<String, Variant>& getParameters() const;

    protected:
        String mName;
        Map<String, Variant> mParameters;
    };
}

#include "Event.inl"

#endif // __EVENT_H__
