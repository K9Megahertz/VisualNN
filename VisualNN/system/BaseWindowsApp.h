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

#include <Windows.h>
#include <gl/glew.h>
#include "../util/logger.h"
#include "../io/keyboard.h"
#include "../io/mouse.h"



class BaseWindowsApp {

public:

    BaseWindowsApp(HINSTANCE hInstance, LPSTR ipCmdLine, int width, int height);
    virtual ~BaseWindowsApp() {}
    
    //setup OpengGL
    bool initGL();
    void CalculateFPS(float dt);

    //run the application, runs until it dies or the user exits
    int run();    

    HWND createMainWindow(HINSTANCE hInstance, int width, int height);    
    

protected:
    virtual bool initialize() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void cleanup() = 0;    
    virtual void OnBaseResize(WPARAM wParam, LPARAM lParam) {
        int newWidth = LOWORD(lParam);
        int newHeight = HIWORD(lParam);
        glViewport(0, 0, newWidth, newHeight);
        m_ClientWidth = newWidth;
        m_ClientHeight = newHeight;        
    }
    virtual void OnBaseKeyDown(WPARAM wParam, LPARAM lParam) { keyboard.onKeyDown(wParam); OnKeyDown(wParam, lParam); }
    virtual void OnBaseKeyUp(WPARAM wParam, LPARAM lParam) { keyboard.onKeyUp(wParam); OnKeyUp(wParam, lParam); }
    virtual void OnBaseMouseMove(WPARAM wParam, LPARAM lParam) { OnMouseMove(wParam, lParam); }
    virtual void OnBaseMouseWheel(WPARAM wParam, LPARAM lParam) { OnMouseWheel(wParam, lParam); }
    virtual void OnBaseLeftButtonDown(WPARAM wParam, LPARAM lParam) { mouse.OnLeftButtonDown(wParam, lParam); OnLeftButtonDown(wParam, lParam); }
    virtual void OnBaseLeftButtonUp(WPARAM wParam, LPARAM lParam) { mouse.OnLeftButtonUp(); OnLeftButtonUp(wParam, lParam); }
    virtual void OnBaseRightButtonDown(WPARAM wParam, LPARAM lParam) { mouse.OnRightButtonDown(wParam, lParam); OnRightButtonDown(wParam, lParam); }
    virtual void OnBaseRightButtonUp(WPARAM wParam, LPARAM lParam) { mouse.OnRightButtonUp(); OnRightButtonUp(wParam, lParam); }
    virtual void OnBaseMiddleButtonDown(WPARAM wParam, LPARAM lParam) { OnMiddleButtonDown(wParam, lParam); }
    virtual void OnBaseMiddleButtonUp(WPARAM wParam, LPARAM lParam) { OnMiddleButtonUp(wParam, lParam); }
    bool isKeyPressed(unsigned int key) { return keyboard.isPressed(key); }
    bool isLeftMousePressed() { return mouse.isLeftMousePressed(); }
    bool isRightMousePressed() { return mouse.isRightMousePressed(); }


    //derived class can implement these if they want to add functionality
    virtual void OnResize(WPARAM wParam, LPARAM lParam) {}
    virtual void OnKeyDown(WPARAM wParam, LPARAM lParam) {}
    virtual void OnKeyUp(WPARAM wParam, LPARAM lParam) {}
    virtual void OnMouseMove(WPARAM wParam, LPARAM lParam) {}
    virtual void OnMouseWheel(WPARAM wParam, LPARAM lParam) {}
    virtual void OnLeftButtonDown(WPARAM wParam, LPARAM lParam) {}
    virtual void OnLeftButtonUp(WPARAM wParam, LPARAM lParam) {}
    virtual void OnRightButtonDown(WPARAM wParam, LPARAM lParam) {}
    virtual void OnRightButtonUp(WPARAM wParam, LPARAM lParam) {}
    virtual void OnMiddleButtonDown(WPARAM wParam, LPARAM lParam) {}
    virtual void OnMiddleButtonUp(WPARAM wParam, LPARAM lParam) {}




    void swapBuffers();

    UINT        m_ClientWidth;
    UINT        m_ClientHeight;
    HWND        m_hWnd;

private:
    HINSTANCE   m_hInstance;    
    HDC         m_hDevContext;
    HGLRC       m_hGLRenderContext;    
    DWORD       m_WindowStyle;
    float       m_FPS;

    Keyboard keyboard;
    Mouse mouse;

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
        BaseWindowsApp* pApp = nullptr;
        if (message == WM_NCCREATE) {
            CREATESTRUCT* pCreateStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
            pApp = reinterpret_cast<BaseWindowsApp*>(pCreateStruct->lpCreateParams);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pApp));
            pApp->m_hWnd = hWnd;
        }
        else {
            pApp = reinterpret_cast<BaseWindowsApp*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
        }

        if (pApp) {
            switch (message) {
            case WM_SIZE:
                pApp->OnBaseResize(wParam, lParam);
                break;
            case WM_KEYDOWN:
                pApp->OnBaseKeyDown(wParam, lParam);
                break;
            case WM_KEYUP:
                pApp->OnBaseKeyUp(wParam, lParam);
                break;
            case WM_MOUSEMOVE:
                pApp->OnBaseMouseMove(wParam, lParam);
                break;
            case WM_MOUSEWHEEL:
                pApp->OnBaseMouseWheel(wParam, lParam);
                break;
            case WM_LBUTTONDOWN:
                pApp->OnBaseLeftButtonDown(wParam, lParam);
                break;
            case WM_LBUTTONUP:
                pApp->OnBaseLeftButtonUp(wParam, lParam);
                break;
            case WM_RBUTTONDOWN:
                pApp->OnBaseRightButtonDown(wParam, lParam);
                break;
            case WM_RBUTTONUP:
                pApp->OnBaseRightButtonUp(wParam, lParam);
                break;
            case WM_MBUTTONDOWN:
                pApp->OnBaseMiddleButtonDown(wParam, lParam);
                break;
            case WM_MBUTTONUP:
                pApp->OnBaseMiddleButtonUp(wParam, lParam);
                break;
            case WM_DESTROY:
                PostQuitMessage(0);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
            return 0;
        }
        return 0;
    }
};
