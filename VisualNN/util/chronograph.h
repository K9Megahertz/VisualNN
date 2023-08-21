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

#include <chrono>
#include <iomanip>
#include <iostream>

class Chronograph {
public:
    void start() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    void stop() {
        stop_time = std::chrono::high_resolution_clock::now();
    }

    void print_elapsed_time() const {
        std::chrono::duration<double> diff = stop_time - start_time;
        int seconds = static_cast<int>(diff.count());
        int days = seconds / 86400;
        seconds -= days * 86400;
        int hours = seconds / 3600;
        seconds -= hours * 3600;
        int minutes = seconds / 60;
        seconds -= minutes * 60;
        std::cout << std::setfill('0') << std::setw(2) << days << ":"
            << std::setw(2) << hours << ":"
            << std::setw(2) << minutes << ":"
            << std::setw(2) << seconds << std::endl;
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time, stop_time;
};

