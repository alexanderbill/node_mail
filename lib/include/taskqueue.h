#ifndef __toon__TaskQueue__
#define __toon__TaskQueue__

#include <thread>
#include <queue>
#include <functional>
#include <list>
#include <mutex>
#include <memory>
#include <condition_variable>
#include <string>

namespace toon {

class TaskQueue
{
public:

    typedef std::function<void()> Task;

    class TaskQueueThread
    {
    public:
        /*!
         @brief
         Constructor.
         */
        TaskQueueThread(const std::string &threadName = "");
        
        /*!
         @brief
         Destructor, all cached tasks will be removed after destruct.
         */
        virtual ~TaskQueueThread();
        
        /*!
         @brief
         Add a task to task queue.
         */
        void executeTask(Task);
        
        /*!
         @brief
         Get count of cached tasks.
         @return
         Count of cached tasks.
         */
        size_t taskCount();

        /*
         * Clear the waiting task in the mTasks
        */
        void clearTask();

    private:
        /*!
         @brief
         Forbidden copy construct and assign operator.
         */
        TaskQueueThread(const TaskQueueThread&);
        TaskQueueThread& operator=(const TaskQueueThread&);
        void main();

        bool mRunning;
        std::queue<Task> mTaskQueue;
        std::recursive_mutex mQueueMutex;
        std::recursive_mutex mRunningMutex;
        std::mutex mConditionMutex;
        std::condition_variable mCondition;
        std::thread mThread;
    };

    /*!
     @brief
     Constructor, will create a thread pool.
     */
    TaskQueue(int capability = 1, const std::string &taskQueueName = "");

    /*!
     @brief
     Destructor, all cached tasks will be removed after destruct.
     */
    virtual ~TaskQueue();

    /**
     *  Clear the waiting task in the each mRunningPool
     */
    void clearTask();
    
    /*!
     @brief
     Add a task to task queue, the task may execute in different threads.
     */
    void addTask(Task);

private:
    /*!
     @brief
     Forbidden copy construct and assign operator.
     */
    TaskQueue(const TaskQueue&);
    TaskQueue& operator=(const TaskQueue&);

    TaskQueueThread *getThread();

    int mCapability;
    std::string mTaskQueueName;
    std::recursive_mutex mMutex;
    std::list<TaskQueueThread*> mRunningPool;
};

typedef std::shared_ptr<TaskQueue::TaskQueueThread> TaskQueueThreadPtr;
typedef std::shared_ptr<TaskQueue> TaskQueuePtr;

}

#endif /* defined(__toon__TaskQueue__) */
