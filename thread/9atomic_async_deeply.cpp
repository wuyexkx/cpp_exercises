#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <atomic>

// 一、原子操作续谈
//   std::atomic cnt = cnt + 1;失效，原子操作只对某些操作符起作用

// 二、std::async深入 （async不一定创建线程，是创建一个异步任务）
//   参数包括std::launch::deferred【延迟调用，并不会创建线程】 std::launch::async【强制创建线程】
//      std::thread()在系统资源紧张时可能创建线程失败，整个程序崩溃
//   async和thread的不同就是async不一定创建线程，可能就在调用get的地方执行
//   std::launch::async | std::launch::deferred是std::async的默认参数，表示系统会自行决定是否异步运行 
//     （异步，创建新线程； 同步，不创建新线程），系统行决定是
  // std::thread 不容易得到线程返回值，std::async可以。
  //   std::async默认参数，由系统决定是否延迟执行或者创建新线程，如果资源紧张，就在调用get的地方执行而不创建新线程，
  //      加参数std::launch::async紧张则可能崩溃，这个参数会使创建新线程
  //      默认参数不一定创建新线程，所以编程有坑，不能理所当然认为会创建新线程，所以需要判断
  //        判断方法是前面学的，std::future_status status = futureObj.wait_for(std::chrono::seconds(0)); // 可以用0s代替std::chrono::seconds(0)
  //        

