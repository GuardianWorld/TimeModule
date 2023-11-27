#ifndef PRINTTHREAD_HPP
#define PRINTTHREAD_HPP

#include <iostream>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>
#include "../timeModule/TimeImport.hpp"

class PrintThread {
private:
    std::queue<std::string> print_queue;
    std::mutex mtx;
    std::condition_variable cv;
    bool stop_printing;
    std::thread thread;

    std::string accumulated_message;

    void printThread(){
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this]{ return !print_queue.empty() || stop_printing; });
            if (stop_printing) return;
            std::string message = print_queue.front();
            print_queue.pop();
            lock.unlock();

            // Print the message
            std::cout << "[ " << DateTimeFormat::build_internal_time_string() << " ]" << message << std::flush;
        }
    }
public:
    PrintThread() : stop_printing(false), thread(&PrintThread::printThread, this) {}
    ~PrintThread() {
        int loops = 0;

        while (!print_queue.empty()) {
            if (loops > 100) {
                std::cout << ">> Warning: Print queue not empty after 1 second" << std::endl;
                thread.join();
                return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Optional: Add a small delay to avoid busy-waiting
            loops++;
        }

        {
            std::unique_lock<std::mutex> lock(mtx);
            stop_printing = true;
            cv.notify_one();
        }

        thread.join();
    }
    
    // Add a method to join the printing thread
    void joinThread() {
        if (thread.joinable()) {
            thread.join();
        }
    }

    void print(const std::string& message) {
        std::unique_lock<std::mutex> lock(mtx);
        print_queue.push(message);
        cv.notify_one();
    }  

    // Static method to access the singleton instance
    static PrintThread& getInstance() {
        static PrintThread instance; // This will ensure a single instance is created
        return instance;
    }

    friend PrintThread& operator<<(PrintThread& pt, const std::string& message) {
        pt.print(message);
        return pt;
    }


    friend PrintThread& operator<<(PrintThread& pt, const char* message) {
        pt.print(message);
        return pt;
    }

    // friend PrintThread& operator<<(PrintThread& pt, const std::ostream& (*manip)(std::ostream&)) {
    //     std::unique_lock<std::mutex> lock(pt.mtx);
    //     pt.print_queue.push(pt.accumulated_message);
    //     pt.accumulated_message.clear();
    //     lock.unlock();
    //     pt.cv.notify_one();
    //     return pt;
    // }
};

#endif // PRINTTHREAD_HPP