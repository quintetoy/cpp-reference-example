### cpp的线程相关接口说明和使用用例

c++的 Thread library

主要介绍c++标准库线程的一些例子和用法

- 线程之间的通信，状态变量和通知 std::condition_variable::notify_one

  ```c++
  void notify_one() noexcept; (since c++11)
  ```

  如果有线程正在等待*this，调用notify_one，可以唤醒

  

  ```c++
  #include <iostream>
  #include <condition_variable>
  #include <thread>
  #include <chrono>
  
  using namespace std;
  std::condition_variable cv;//有通知和等待的功能
  std::mutex cv_m;
  int i=0;
  bool done=false;
  
  void waits(){
    std::unique_lock<std::mutex>lk(cv_m);
    std::cout<<"waiting ...\n";
    cv.wait(lk,[]{return i==1;});
    std::cout<<"...finished waiting. i==1\n";
    done=true;
  }
  
  void signals(){
    std::this_thread::sleep_for(std::chrono::seconds(1));//等待一秒，超时等待
    std::cout<<"Notifying falsely...\n";
    cv.notify_one();//等待线程被通知i=0,cv.wait唤醒，检查i，然后继续等待
    std::unique_lock<std::mutex>lk(cv_m);//c++的锁是一个阻塞功能，代表当前的程序如果被调用的话，锁以下的c++语句的变量被控制，不能被其他的线程调用
    i=1;
    while(!done){
      std::cout<<"Notifying true change ...\n";
      lk.unlock();
      cv.notify_one();//等待线程被通知i=1，cv.wait返回
      std::this_thread::sleep_for(std::chrono::seconds(1));
      lk.lock();
    }
  }
  
  int main(){
    std::thread t1(waits),t2(signals);
    t1.join();
    t2.join();
  }
  
  ```

  



```c++
结果输出为：
Waiting... 
Notifying falsely...
Notifying true change...
...finished waiting. i == 1
```

- 参考网址：

<https://en.cppreference.com/w/cpp/thread/condition_variable/notify_one>



#### 互斥锁

- Std::unique_lock<Mutex>::unique_lock

  ```c++
  unique_lock() noexcept;
  
  unique_lock( unique_lock&& other ) noexcept;
  
  explicit unique_lock( mutex_type& m );
  
  unique_lock( mutex_type& m, [std::defer_lock_t](http://zh.cppreference.com/w/cpp/thread/lock_tag_t) t ) noexcept;
  
  unique_lock( mutex_type& m, [std::try_to_lock_t](http://zh.cppreference.com/w/cpp/thread/lock_tag_t) t );
  
  unique_lock( mutex_type& m, [std::adopt_lock_t](http://zh.cppreference.com/w/cpp/thread/lock_tag_t) t );
  
  template<class Rep,class Period>unique_lock(mutex_type& m,const std::chrono::duration<Rep,Period>& timeout_duration);
  
  template<class Clock,class Duration>unique_lock(mutex_type& m,const std::chrono::time_point<Clock,Duration>& timeout_time);
                                                  
                                                
  ```



参考代码示例

```c++
#include<iostream>
#include<thread>
#include<vector>
#include<mutex>

std::mutex m_a,m_b,m_c;
int a,b,c=1;
void update(){
  {
  std::unique_lock<std::mutex>lk(m_a);
  a++;
  }
  {
    std::unique_lock<std::mutex>lk_b(m_b,std::defer_lock);
    std::unique_lock<std::mutex> lk_c(m_c, std::defer_lock);
    std::lock(lk_b, lk_c);
    b = std::exchange(c, b+c);
  }

}


int main(){
  std::vector<std::thread> threads;
  for(unsigned i=0;i<12;++i)
    threads.emplace_back(update);
  for(auto& i:threads)
    i.join()
  std::cout << a << "'th and " << a+1 << "'th Fibonacci numbers: "
            << b << " and " << c << '\n';
}
```

- 当前文件夹中补充一个例子example.cpp，一个往队列中写数据的函数，一个从队列中取数据的函数



