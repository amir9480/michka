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

#include "EventManager.h"

namespace Michka
{
    u64 EventHandler::lastHandlerId = 1;

    EventManager::~EventManager()
    {
        //
    }

    void EventManager::callQueueListeners()
    {
        for (auto event : mEventsQueue)
        {
            if (this->onEvent(&event) == false && mEventHandlers.hasKey(event.getName()))
            {
                for (EventHandler eventHandler : mEventHandlers[event.getName()])
                {
                    eventHandler.mCallback(&event);
                }
                mEventHandlers[event.getName()].filter([] (const EventHandler& _handler)
                {
                    return _handler.mOnce == false;
                });
            }
        }
        mEventsQueue.clear();
    }

    void EventManager::emit(const String& _name, const Map<String, Variant>& _parameters)
    {
        Event event;
        event.mName = _name;
        event.mParameters = _parameters;
        if (mCallEventListenersManually)
        {
            mEventsQueue.pushBack(std::move(event));
            return;
        }

        if (this->onEvent(&event) == false && mEventHandlers.hasKey(_name))
        {
            for (EventHandler eventHandler : mEventHandlers[_name])
            {
                eventHandler.mCallback(&event);
            }
            mEventHandlers[_name].filter([] (const EventHandler& _handler)
            {
                return _handler.mOnce == false;
            });
        }
    }

    bool EventManager::onEvent(const Event* _event)
    {
        return false;
    }
}
