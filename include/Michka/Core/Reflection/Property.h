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

#ifndef __PROPERTY_H__
#define __PROPERTY_H__

#include "Michka/Core/Helpers.h"
#include "Michka/Core/Container/List.h"
#include "Michka/Core/Container/String.h"
#include "MetaAttributes.h"
#include <type_traits>

namespace Michka
{
    class Property : public MetaAttributes
    {
    public:

    protected:
        Property(const String& _name, const std::function<Variant(const Variant&)>& _getter, const std::function<bool(const Variant&, const Variant&)>& _setter);

        Variant get(const Variant& _instance) const;

        bool set(const Variant& _instance, const Variant& _newValue) const;

    protected:
        String mName;
        std::function<Variant(const Variant&)> mGetter;
        std::function<bool(const Variant&, const Variant&)> mSetter;
    };
}

#include "Core/Reflection/TypeInfo.inl"

#endif // __PROPERTY_H__
