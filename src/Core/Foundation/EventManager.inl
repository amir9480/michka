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

#include "EventManager.h"

namespace Michka
{
    FORCE_INLINE EventHandler::EventHandler(const EventCallback& _callback, const bool& _once) :
        mId(lastHandlerId++),
        mCallback(_callback),
        mOnce(_once)
    {
        //
    }

    FORCE_INLINE EventManager::EventManager()
    {

    }

    FORCE_INLINE void EventManager::clearEvents()
    {
        mEventHandlers.clear();
    }

    FORCE_INLINE void EventManager::off(const String& _name)
    {
        if (mEventHandlers.hasKey(_name))
        {
            mEventHandlers[_name].clear();
        }
    }

    FORCE_INLINE void EventManager::off(const String& _name, const u64& _handlerId)
    {
        if (mEventHandlers.hasKey(_name))
        {
            mEventHandlers[_name].filter([_handlerId] (const EventHandler& _handler) {
                return _handler.mId != _handlerId;
            });
        }
    }

    FORCE_INLINE u64 EventManager::on(const String& _name, const EventCallback& _callback, const bool& _once)
    {
        if (mEventHandlers.hasKey(_name) == false)
        {
            mEventHandlers[_name] = List<EventHandler>();
        }

        mEventHandlers[_name].pushBack(EventHandler(_callback, _once));

        return mEventHandlers[_name][mEventHandlers[_name].getSize() - 1].mId;
    }

    FORCE_INLINE u64 EventManager::once(const String& _name, const EventCallback& _callback)
    {
        return on(_name, _callback, true);
    }
}
