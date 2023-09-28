//Intel Core i3 3220 @ 3.30GHz два ядра 4 потока.
/*
при разбивке на два потока происходит самое быстрое вычисление

*/



#include <vector>
#include <iostream>
#include <chrono>
#include <random>
#include <thread>
//#include <cstdlib>



void sum(std::vector<int> myVector, int l, int r)
{
  
    int s = 0;
    for (int i = l; i < r; i++)
    {
        s += myVector[i];
    }
    std::cout << s << "\n\n";
 }

int all = 0;

void sum_(std::vector<int> myVector, int l, int r)
{
    
    int s = 0;
    for (int i = l; i < r; i++)
    {
        s += myVector[i];
    }
   
     all += s;
}




int main()
{
  const int size=10000000;
  
  std::vector<int> myVector;
  std::vector<std::thread> threads;
 
  for (int i =0; i < size; i++)
    {
    int b = rand()%5+1;
    myVector.push_back(b);
    }
    std::cout << std::endl;
    int l = 0;
    int r = 0;
    //вычисление без потоков
    auto timePoint1 = std::chrono::steady_clock::now();
    sum(myVector, 0, size);
    auto timePoint2 = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds> (timePoint2 - timePoint1).count();
    std::cout << "Duration: " << duration << " ms" << std::endl << std::endl;
  
    
    //вычисление с потоками 
    const int quantity_t = 2;//количество потоков
    int n = size / quantity_t;
    
    timePoint1 = std::chrono::steady_clock::now();
    for (int i = 0; i < quantity_t; i++)
    {
          l = r;
        r = (i + 1) * n;
        std::thread t(&sum_, myVector, l, r);
        threads.push_back(std::move(t));
    }
   
    for (auto& t : threads)
    {
        if (t.joinable())
            t.join();
    }
    std::cout << all << "\n\n";
    timePoint2 = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds> (timePoint2 - timePoint1).count();
    std::cout << "Duration: " << duration << " ms" << std::endl << std::endl;
 }
