//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// 
// MIT License
// 
// Copyright(c) 2023 Gerald Filimonov
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <atomic>

template <typename T>
class Thread {
public:
    Thread(T *instance, void (T:: *method)()) : m_instance(instance), m_method(method), m_handle(NULL), m_id(0), m_running(false) { m_speed = 1000; }
    ~Thread() {
        if (m_handle != NULL) {
            stop();
            CloseHandle(m_handle);
            m_handle = NULL;            
        }
    }
    void start() {
        if (!m_running) {
            m_running = true;
            m_handle = CreateThread(NULL, 0, &Thread::Wrapper, this, 0, &m_id);
        }
    }
    void stop() {
        if (m_running) {
            m_running = false;
            WaitForSingleObject(m_handle, INFINITE);
            m_handle = NULL;
        }
    }
    void setspeed(int speed) {
        m_speed = speed;
    }
private:
    T* m_instance;
    void (T::* m_method)();
    HANDLE m_handle;
    DWORD m_id;
    std::atomic<bool> m_running;
    std::atomic<int> m_speed;

    static DWORD WINAPI Wrapper(LPVOID param) {
        Thread* thread = static_cast<Thread*>(param);
        while (thread->m_running) {
            Sleep(thread->m_speed);
            (thread->m_instance->*thread->m_method)();            
        }
        return 0;
    }
};

