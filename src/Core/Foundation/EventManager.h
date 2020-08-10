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

#ifndef __EVENTMANAGER_H__
#define __EVENTMANAGER_H__

#include <functional>
#include "Core/Defines.h"
#include "Core/Foundation/Event.h"
#include "Core/Container/List.h"

namespace Michka
{
    class Event;
    typedef std::function<void(const Event*)> EventCallback;

    class EventHandler
    {
        friend class EventManager;
    public:
        FORCE_INLINE EventHandler(const EventCallback& _callback, const bool& _once = false);

    private:
        u64 mId;
        EventCallback mCallback;
        bool mOnce;

    private:
        static u64 lastHandlerId;
    };

    class MICHKA_API EventManager
    {
    public:
        FORCE_INLINE EventManager();
        virtual ~EventManager();

        /**
         * @brief Clear all event listeners.
         */
        FORCE_INLINE void clearEvents();

        /**
         * @brief Emit an event.
         *
         * @param _name
         * @param _parameters
         */
        void emit(const String& _name, const Map<String, Variant>& _parameters = {});

        /**
         * @brief Remove all listeners to an event.
         *
         * @param _name
         */
        FORCE_INLINE void off(const String& _name);

        /**
         * @brief Remove specific event listener by handler id
         *
         * @param _name
         * @param _handlerId
         */
        FORCE_INLINE void off(const String& _name, const u64& _handlerId);

        /**
         * @brief Add an event listener.
         *
         * @param _name
         * @param _callback
         * @param _once
         * @return event listener id
         */
        FORCE_INLINE u64 on(const String& _name, const EventCallback& _callback, const bool& _once = false);

        /**
         * @brief Add an event listener but listen only once.
         *
         * @param _name
         * @param _callback
         * @param _once
         * @return event listener id
         */
        FORCE_INLINE u64 once(const String& _name, const EventCallback& _callback);

    private:
        Map<String, List<EventHandler>> mEventHandlers;
    };
}

#include "EventManager.inl"

#endif // __EVENTMANAGER_H__
