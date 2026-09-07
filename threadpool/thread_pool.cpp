#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <condition_variable>
#include <mutex>
#include <iostream>

// class threadPool {
//     public:
//     threadPool(int thread_count){
//         for (int i; i < thread_count; i++) {
//             std::thread t1(task_init) ;
//             thread_pool.emplace_back([this](){
//                 this->task_init();
//             }
//             );
//         }
//     };
//     void push(std::function<void()> task) {
//         {
//             std::lock_guard<std::mutex> lock(mtx);
//             tasks.push(task);
//         }
//         cv.notify_one();
//     };
//     private:
//     std::vector<std::thread> thread_pool;
//     std::queue<std::function<void()>> tasks;
//     std::condition_variable cv;
//     std::mutex mtx;
//     void task_init() {
//         while(true) {
//             std::unique_lock<std::mutex> thread_lock(mtx);
//             cv.wait(thread_lock, [this]{
//                 return !tasks.empty();
//             });
//         }
// };

// };

class threadpool
{
private:
    std::vector<std::thread> thread_pool;
    std::condition_variable cv;
    std::mutex mtx;
    // std::unique_lock<std::mutex> lock(mtx);
    std::queue<std::function<void()>> tasks;
    bool bool_is_shutdown;

public:
    threadpool(int n)
    {
        this->bool_is_shutdown = false;
        // std::unique_lock<std::mutex> lock(mtx);
        for (int i = 0; i <= n - 1; ++i)
        {
            thread_pool.emplace_back([this]
                                     {
                                         while (true)
                                         {
                                             // if (this->bool_is_shutdown) {
                                             //     return;
                                             // }
                                             std::function<void()> task;
                                             {
                                                 std::unique_lock<std::mutex> lock(mtx);
                                                 this->cv.wait(lock, [this]
                                                               { return !this->tasks.empty() || this->bool_is_shutdown; });
                                                 if (this->bool_is_shutdown && this->tasks.empty())
                                                 {
                                                     return;
                                                 };
                                                 if (!this->tasks.empty())
                                                 {
                                                     task = this->tasks.front();
                                                     this->tasks.pop();
                                                 };
                                             };
                                             if (task != nullptr)
                                             {
                                                 task();
                                             }
                                             // if (this->bool_is_shutdown) {
                                             //     return;
                                             // }
                                             // task();
                                         }; });
        };
    };
    ~threadpool()
    {
        {
            std::lock_guard<std::mutex> lock(mtx);
            this->bool_is_shutdown = true;
        }
        cv.notify_all();
        for (std::thread &thread : this->thread_pool)
        {
            if (thread.joinable())
            {
                thread.join();
            };
        };
    };

    void push(std::function<void()> task)
    {
        {
            std::lock_guard<std::mutex> lock(mtx);
            this->tasks.push(task);
        };
        this->cv.notify_one();
    }

    // void thread_function_init(){
    //     while(true){
    //         this->cv.wait(lock, [this]{return !this->tasks.empty();});
    //     }
    // }
};

void test()
{
    std::cout << "test" << std::endl;
};

// int main()
// {
//     threadpool thread_pool(5);
// };