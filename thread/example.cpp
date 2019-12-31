#include <stdio.h>
#include <list>
#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <string.h>

//所以的图片均存储在list中
std::mutex picQueue_mutex;
std::condition_variable picQueue_cond;
std::list<Pic*> picQueue;
int max_cache_pic=1000;


struct Pic{
public:
    Pic(int length):m_length(length){data=new unsigned char[m_length];};
    ~Pic(){delete[] data;};
    unsigned char* GetData(){return data;};

private:
    int m_length;
    unsigned char* data;
}


void PushPic(Pic* pic){
    bool awake=false;
    std::unique_lock<std::mutex> lck(picQueue_mutex);
    if(picQueue.size()==0)
        awake=true;
    if(picQueue>max_cache_pic){
        Pic tmpic=picQueue.front();
        delete tmpic;
        picQueue.pop_front();
    }
    picQueue.push_back(pic);
    if(awake)
        picQueue_cond.notify_one();
    
}



Pic* GetPic(int millisecond){
    std::unique_lock<std::mutex> lck(picQueue_mutex);
    if(picQueue.size()==0){
        //等待通知
        auto wait_result=picQueue_cond.wait_for(lck, std::chrono::milliseconds(millisecond));
        if(wait_result == std::cv_status::timeout)
            return NULL;
    }
    if(picQueue.size()==0){
        return NULL;
    }
    
    Pic* tmp=picQueue.front();
    picQueue.pop_front();
    return tmp;
    
}
