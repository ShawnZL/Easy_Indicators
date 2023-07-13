//
// Created by Shawn Zhao on 2023/7/13.
//

#ifndef EASY_INDICATORS_INDICATORS_H
#define EASY_INDICATORS_INDICATORS_H

#include <string>
// 提供处理时间和时间间隔的库。它提供各种时钟类型、时间点和持续时间的定义
#include <chrono>
#include <thread>
#include <mutex>
#include <vector>
#include <iostream>

namespace indicator {
    using namespace std::chrono;

    std::vector<std::vector<std::string>> IndicatorFrames = {
            {"|", "/", "-", "\\"},
            {"+", "x"},
            {"v", "<", "^", ">"},
            {"(o     )", "( o    )", "(  o   )", "(   o  )", "(    o )", "(     o)", "(    o )", "(   o  )", "(  o   )", "( o    )"},
            {">))'>    ", " >))'>   ", "  >))'>  ", "   >))'> ", "    >))'>", "    <'((<", "   <'((< ", "  <'((<  ", " <'((<   ", "<'((<    "},
            {"  o o o o o", "o   o o o o", "o o   o o o", "o o o   o o", "o o o o   o", "o o o o o  ", "o o o o o o"},
            {"::|\\____________::", "::_|\\___________::", "::__|\\__________::", "::___|\\_________::", "::____|\\________::", "::_____|\\_______::", "::______|\\______::", "::_______|\\_____::", "::________|\\____::", "::_________|\\___::", "::__________|\\__::", "::___________|\\_::", "::____________|\\::", "::____________/|::", "::___________/|_::", "::__________/|__::", "::_________/|___::", "::________/|____::", "::_______/|_____::", "::______/|______::", "::_____/|_______::", "::____/|________::", "::___/|_________::", "::__/|__________::", "::_/|___________::", "::/|____________::"},

    };

    class indicator {
    public:
        indicator(const duration<int, std::milli> &delay = 200ms, // 来自chrono::duration的类型对象 std::milli -> millisecond
                  int type = 0,
                  const std::string &endmsg = "",
                  const std::string &prefix = "",
                  const std::string &suffix = "",
                  bool hide_on_end = false,
                  const std::vector<std::string> &custom_frames = {}) : frame_delay(delay),
                                                                        type(type),
                                                                        endmsg(endmsg),
                                                                        prefix(prefix),
                                                                        suffix(suffix),
                                                                        hide_on_end(hide_on_end),
                                                                        custom_frames(custom_frames),
                                                                        is_active(false)
        {}
        ~indicator() {
            stop();
        }

        void start() {
            is_active = true;
            std::cout.flush();
            last_text_size = 0;
            if (type >= IndicatorFrames.size())
                // 首先进行隐式转换，char 1byte -> int
                type = 0;
            // thread = std::thread([&]() {}) 使用 lambda 表达式创建一个匿名函数，
            // 并将其作为参数传递给 std::thread 构造函数，
            // 以创建新的线程。lambda 表达式使用 [&] 捕获外部作用域的所有变量，以便在线程函数中使用。
            thread = std::thread([&]() {
                unsigned int c = 0;
                const std::vector<std::string> &frames = (custom_frames.size() > 0) ? custom_frames: IndicatorFrames[type];
                int l = frames.size();
                while (is_active) {
                    const std::string &frame = frames[c % l];
                    c++;
                    std::cout << "\r" << prefix << frame << suffix;
                    last_text_size = prefix.length() + frame.length() + suffix.length();
                    std::cout.flush();
                    std::this_thread::sleep_for(frame_delay); // 暂停当前线程，延迟
                }
            });
        }

        void stop() {
            if (is_active) {
                is_active = false;
                thread.join();
                if (endmsg.size() > 0) {
                    if (hide_on_end) {
                        std::cout << "\r" << std::string(last_text_size, ' ');
                        std::cout << "\r"
                                  << " - " << endmsg << std::endl;
                    }
                    else {
                        std::cout << "\n"
                                  << " - " << endmsg << std::endl;
                    }
                }
                std::cout.flush(); // 强行将缓存区刷新
                // endl 终止一行并刷新缓冲区
                // ends 终止字符串并在末尾加入空字符
            }
        }

        void set_frame_delay(const duration<int, std::milli> &delay) {
            frame_delay = delay;
        }

        void set_prefix(const std::string &str) {
            prefix = str;
        }

        void set_suffix(const std::string &str) {
            suffix = str;
        }

        void set_end_msg(const std::string &str) {
            endmsg = str;
        }

    private:
        duration<int, std::milli> frame_delay; // 暂停时间
        std::string prefix;
        std::string suffix;
        std::vector<std::string> custom_frames;
        unsigned char type;
        std::string endmsg;
        unsigned int last_text_size;
        bool hide_on_end;
        bool is_active;
        std::thread thread;
    };
}

#endif //EASY_INDICATORS_INDICATORS_H
