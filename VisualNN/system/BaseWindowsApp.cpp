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

#include "BaseWindowsApp.h"

extern bool glinit;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  CTORs/DTORs
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BaseWindowsApp::BaseWindowsApp(HINSTANCE hInstance, LPSTR ipCmdLine, int width, int height) {

	m_hInstance = hInstance;
	m_ClientWidth = width;
	m_ClientHeight = height;

	Logger::SetLogLevel(Logger::LogLevel::LOGLEVEL_INFO);	
	//Logger::SetLogLevel(Logger::LogLevel::LOGLEVEL_DEBUG);
	Logger::Start("applicationlog.txt");

	//create the main application window
	if (!(m_hWnd = createMainWindow(hInstance, width, height))) {
		Logger::Append(Logger::LogLevel::LOGLEVEL_ERROR, "Could not create application window!");
		exit(1);
	}

	//Intialize OpenGL
	if (!initGL()) {
		Logger::Append(Logger::LogLevel::LOGLEVEL_ERROR, "Could not initialize OpenGL!");
		exit(1);
	}
	

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function CreateMainWindow()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


HWND BaseWindowsApp::createMainWindow(HINSTANCE hInstance, int width, int height)
{
    WNDCLASS wc = {};
    wc.lpfnWndProc = BaseWindowsApp::WndProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = L"MainWndClass";
	if (!RegisterClass(&wc)) {
		DWORD error = GetLastError();
		// Handle the error
		Logger::Append(Logger::LogLevel::LOGLEVEL_ERROR, "Could not register window class!");
		return 0;
	}

	Logger::Append(Logger::LogLevel::LOGLEVEL_DEBUG, "Adjusting Window Rect!");

    RECT rc = { 0, 0, width, height };	
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    HWND hwnd = CreateWindowEx(0, L"MainWndClass", L"test",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, GetModuleHandle(nullptr), this);
		
	if (!hwnd) {
		Logger::Append(Logger::LogLevel::LOGLEVEL_ERROR, "CreateWindowEx function call failed!");
		return 0;
	}
	Logger::Append(Logger::LogLevel::LOGLEVEL_DEBUG, "Showing window!");
    ShowWindow(hwnd, SW_MAXIMIZE);

    return hwnd;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function InitGL()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool BaseWindowsApp::initGL() {


	Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "Initializing OpenGL");


	m_hDevContext = GetDC(m_hWnd);

	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;

	Logger::Append(Logger::LogLevel::LOGLEVEL_DEBUG, "Choosing PixelFormat!");
	int format = ChoosePixelFormat(m_hDevContext, &pfd);

	if (!SetPixelFormat(m_hDevContext, format, &pfd)) {
		Logger::Append(Logger::LogLevel::LOGLEVEL_ERROR, "FAILED TO SET PIXEL FORMAT");
		return false;
	}
	
	Logger::Append(Logger::LogLevel::LOGLEVEL_DEBUG, "Creating wgl context!");
	m_hGLRenderContext = wglCreateContext(m_hDevContext);

	Logger::Append(Logger::LogLevel::LOGLEVEL_DEBUG, "Making render context current!");
	if (!wglMakeCurrent(m_hDevContext, m_hGLRenderContext)) {		
		Logger::Append(Logger::LogLevel::LOGLEVEL_ERROR, "FAILED TO CREATE AND ACTIVIATE RENDER CONTEXT");
		return false;
	}

	Logger::Append(Logger::LogLevel::LOGLEVEL_DEBUG, "Intializing GLEW!");
	if (glewInit()) {
		Logger::Append(Logger::LogLevel::LOGLEVEL_ERROR, "FAILED TO INITIALIZE GLEW");
		return false;
	}


	//Let's enable/disable some default features.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);		// This Will Clear The Background Color To Black	
	glClearDepth(1.0);							// Enables Clearing Of The Depth Buffer	
	glEnable(GL_DEPTH_TEST);					// Enables Depth Testing
	glFrontFace(GL_CCW);
	

	glClearStencil(0);                          // clear stencil buffer
	glClearDepth(1.0f);                         // 0 is near, 1 is far
	glDepthFunc(GL_LEQUAL);

	glViewport(0, 0, m_ClientWidth, m_ClientHeight);			// Reset The Current Viewport And Perspective Transformation		

	glEnable(GL_CULL_FACE);

	Logger::Append(Logger::LogLevel::LOGLEVEL_DEBUG, "OpenGL Successfully Initialized!");

	return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function run
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int BaseWindowsApp::run() {
	initialize();

	// Initialize timer
	auto startTime = std::chrono::high_resolution_clock::now();
	auto lastUpdateTime = startTime;

	// Enter message loop
	MSG msg;
	while (true) {
		// Peek message
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// Handle message
			if (msg.message == WM_QUIT) {
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			// Calculate delta time
			auto currentTime = std::chrono::high_resolution_clock::now();

			float deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - lastUpdateTime).count();
			lastUpdateTime = currentTime;			

			// Run update method with delta time
			update(deltaTime);
			CalculateFPS(deltaTime);
		}
	}
	cleanup();

	return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function swapBuffers()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BaseWindowsApp::swapBuffers() {

	HDC dc = GetDC(m_hWnd);
	SwapBuffers(dc);
	ReleaseDC(m_hWnd, dc);


}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function CalculateFPS()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BaseWindowsApp::CalculateFPS(float dt)
{
	static float elapsed = 0;
	static int frameCnt = 0;

	elapsed += dt;
	frameCnt++;
	if (elapsed >= 1.0f) {

		m_FPS = (float)frameCnt;
		std::stringstream ss;
		ss << "FPS: " << m_FPS << " " << glGetString(GL_VENDOR) << " " << glGetString(GL_RENDERER) << " " << glGetString(GL_VERSION);
		std::string blah = ss.str();

		std::wstring titletext = std::wstring(blah.begin(), blah.end());
		SetWindowText(m_hWnd, titletext.c_str());

		elapsed = 0;
		frameCnt = 0;
	}
}
