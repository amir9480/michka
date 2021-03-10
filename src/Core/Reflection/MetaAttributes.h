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

#ifndef __META_PROPERTIES_H__
#define __META_PROPERTIES_H__

#include "Core/Helpers.h"
#include "Core/Container/String.h"
#include "Core/Container/Variant.h"
#include "Core/Container/Map.h"

namespace Michka
{
    class MICHKA_API MetaAttributes
    {
    public:
        MetaAttributes();
        ~MetaAttributes();

        /**
         * @brief Get the Properties object.
         *
         * @return const Map<String, Variant>&
         */
        const Map<String, Variant>& getProperties();

        /**
         * @brief Get a property value.
         *
         * @param _name
         * @return Variant
         */
        Variant getProperty(const String& _name) const;

        /**
         * @brief Check if specific property exists.
         *
         * @param _name
         */
        bool hasProperty(const String& _name) const;

        /**
         * @brief Set a property value.
         *
         * @param _name
         * @param _value
         * @return Self
         */
        MetaAttributes& setProperty(const String& _name, const Variant& _value);

    protected:
        Map<String, Variant> mProperties;
    };
}

#endif // __META_PROPERTIES_H__
