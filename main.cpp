#include <iostream>
#include <list>

#include "Shufflin.hpp"

// Main program entry point.
int main(int argc, const char * argv[])
{
    //CShuffler objShuffler(8, 3);
    //CShuffler objShuffler(8, 5);
    //CShuffler objShuffler(10, 5);
    //CShuffler objShuffler(9, 3);
    //CShuffler objShuffler(102, 11);
    
    int decSize = 1002;
    int cutSize = 101;
    
    if (argc > 1)
    {
        decSize = atoi(argv[1]);
    }
    
    if (argc > 2)
    {
        cutSize = atoi(argv[2]);
    }
    
    cout<<"\r\nDec Size = "<<decSize;
    cout<<"\r\nCut Size = "<<cutSize;
    std::cout.flush();
    
    if (cutSize >= decSize)
    {
        cout<<"\r\nCut should be smaller than dec size\r\n";
        return 0;
    }

    CShuffler objShuffler(decSize, cutSize);
    
    time_t start = time(NULL);
    
    unsigned long iterations = objShuffler.CalculateIterationsRequired();

    std::cout << "\r\nNumber of iterations required = "<<iterations;
    cout<<"\r\nTime elapsed :"<<(time(NULL) - start)<<" Second(s)\r\n";
    std::cout.flush();
    
    return 0;
}
