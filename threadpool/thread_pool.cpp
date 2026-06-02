#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <condition_variable>
#include <mutex>
// 线程池 
// 1. 线程池的构造函数，创建指定数量的线程，并将它们加入线程池中。
// 2. push()函数，用于向线程池中添加任务。它将任务添加到任务队列中，并通知一个等待的线程来执行任务。
// 3. task_init()函数，线程池中的每个线程都会执行这个函数。它会不断地等待任务队列
// 中有任务可执行，并在有任务时执行它们。线程会一直运行，直到线程池被销毁。
// 4. 线程池的成员变量包括一个线程池向量、一个任务队列、一个条件变量和一个互斥锁。线程池向量用于存储线程对象，任务队列用于存储待执行的任务，条件变量用于通知等待的线程有新任务可执行，互斥锁用于保护对共享资源的访问。
// 5. 线程池的析构函数，负责清理线程池中的资源，确保所有线程都正确地退出。
// 6 .线程池的其他成员函数，如停止线程池、等待所有线程完成等，可以根据需要进行实现。
// 7. 线程池的使用示例，展示如何创建线程池、添加任务以及等待任务完成等操作。
// 8. 线程池的错误处理机制，确保在添加任务或执行任务时能够正确处理异常情况。
// 9. 线程池的性能优化，如使用线程局部存储、减少锁的竞争等，以提高线程池的效率和响应能力。
// 10. 线程池的扩展功能，如支持任务优先级、定时任务等，以满足不同应用场景的需求。
// 11. 线程池的测试和调试方法，确保线程池的正确性和稳定性。
// 12. 线程池的文档和注释，提供清晰的说明和使用指南，帮助开发者理解和使用线程池。



class threadPool {
    public:
    threadPool(int thread_count){
        for (int i; i < thread_count; i++) {
            std::thread t1(task_init) ;
            thread_pool.emplace_back([this](){
                this->task_init();
            }
            );
        }
    };
    void push(std::function<void()> task) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            tasks.push(task);
        }
        cv.notify_one();
    };
    private:
    std::vector<std::thread> thread_pool;
    std::queue<std::function<void()>> tasks;
    std::condition_variable cv;
    std::mutex mtx;

    void task_init() {
        while(true) {
            std::unique_lock<std::mutex> thread_lock(mtx);
            cv.wait(thread_lock, [this]{
                return !tasks.empty();
            });     
        }
};

};