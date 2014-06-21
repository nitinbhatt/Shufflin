//
//  main.cpp
//  Shuffle
//
//  Created by Nitin on 4/12/13.
// Problem solution : Based on the dec size and the cut size, determine how many iterations
// each card in our dec will take (irrespective of other cards) to come back to the original position.
// Once we have those numbers, it is just calculation from there to get the Least Common Multiplier of
// all those (unique) numbers.

//#define _DEBUG_
#undef _DEBUG_

#include <iostream>
#include <list>
using namespace std;

class CShuffler
{
    // Member variabled
    int m_decSize;
    int m_cutSize;
    int m_shuffledDecSize;

    list<unsigned long> m_wrapAroundResults;

    // Helper functions
    void DisplayWrapAroundsUnique();
    
    bool WillBeShuffled(int position);
    int CalculateShuffledDecSize();
    
    unsigned long FindNumberOfIterationsForWrapArround(int pos);

    // Math related functions
    unsigned long GCD(unsigned long a, unsigned long b);
    unsigned long LCM(unsigned long a, unsigned long b);
    
    unsigned long CalculateIterationsFromWraparounds();
    
public:
    
    // Overloaded constructor for setting the default values
    // dec size and the cut size
    CShuffler(int decSize, int cutSize)
    {
        m_decSize = decSize;
        m_cutSize = cutSize;
        
        m_shuffledDecSize = -1;
    }
    
    // Only (other) public function in out class. This does all the work.
    unsigned long CalculateIterationsRequired();
};

bool CShuffler::WillBeShuffled(int position)
{
    bool willShuffle = false;
    
    if (m_cutSize > m_decSize/2)
    {
        int shuffleStartLocation = m_decSize - ((m_decSize - m_cutSize) * 2) + 1;
        
        if (position < shuffleStartLocation)
        {
            willShuffle = false;
        }
        else
        {
            willShuffle = true;
        }
    }
    else
    {
        if (position > m_cutSize &&
            position  < (m_decSize-m_cutSize+1))
        {
            willShuffle = false;
        }
        else
        {
            willShuffle = true;
        }
    }
    
    return willShuffle;

}


void CShuffler::DisplayWrapAroundsUnique()
{
    std::list<unsigned long>::iterator itr;
    itr = m_wrapAroundResults.begin();
    
    cout<<"\r\n";
    
    while (itr!= m_wrapAroundResults.end())
    {
        cout<<" "<<*itr<<",";
        itr++;
    }
    
    cout.flush();
}

int CShuffler::CalculateShuffledDecSize()
{
    // We don't need to calculate this again and again.
    // For a pair of Dec size and cut size, this will always be the same,
    // just calculate this one and cache it.
    if (m_shuffledDecSize == -1)
    {
        int decSize = m_decSize;
        
        if (decSize %2 != 0)
        {
            decSize = decSize - 1;
        }
        
        int shuffledSize = 0;
        
        if (m_cutSize < decSize/2)
        {
            shuffledSize = (m_cutSize * 2);
        }
        else
        {
            shuffledSize = (decSize-m_cutSize)*2;
        }
        
        m_shuffledDecSize = shuffledSize;
        
    }
    
    return m_shuffledDecSize;
}

unsigned long CShuffler::FindNumberOfIterationsForWrapArround(int pos)
{
    int originalPos = pos;
    int newLocation = 0;
    
    unsigned long numberOfIterationsRequired = 0;
    
    while (true)
    {
        numberOfIterationsRequired++;

        bool willShuffle = WillBeShuffled(pos);
        
        if (willShuffle)
        {
            if (pos > m_cutSize)
            {
                newLocation = (m_decSize - pos + 1) * 2;
            }
            else
            {
                newLocation = ((m_cutSize - pos) * 2) + 1;
            }
        }
        else
        {
            int shuffledDecSize = CalculateShuffledDecSize();
            if (pos > m_cutSize)
            {
                newLocation = shuffledDecSize + (m_decSize - shuffledDecSize/2 - pos) + 1;
            }
            else
            {
                newLocation = shuffledDecSize + (m_cutSize - shuffledDecSize/2 - pos) + 1;
            }
        }
        
        newLocation = m_decSize - newLocation + 1;
        
        if (newLocation == originalPos)
        {
            break;
        }
        else
        {
            pos = newLocation;
        }
    }
    
    return numberOfIterationsRequired;
}

unsigned long CShuffler::CalculateIterationsRequired()
{
    // We could have dispatched the function "FindNumberOfIterationsForWrapArround"
    // in seperate threads for each value of "pos" but since the calculate in this
    // function is really trivial it would be an overhead.
    for (int i = 0 ; i < m_decSize; i++)
    {
        m_wrapAroundResults.push_back(FindNumberOfIterationsForWrapArround(i+1));
    }
    
    m_wrapAroundResults.sort();
    m_wrapAroundResults.unique();
    
#ifdef _DEBUG_
    DisplayWrapAroundsUnique();
#endif
    
    return CalculateIterationsFromWraparounds();
}

unsigned long CShuffler::GCD(unsigned long a, unsigned long b)
{
    unsigned long gcd = 0;
    if (a < b)
    {
        gcd = a;
    }
    else
    {
        gcd = b;
    }
    
    while (true)
    {
        if (a%gcd == 0 && b%gcd == 0)
        {
            break;
        }
        else
        {
            gcd--;
        }
    }
    
    return gcd;
}

unsigned long CShuffler::LCM(unsigned long a, unsigned long b)
{
    unsigned long lcm = 0;
    
    lcm = (a*b)/GCD(a, b);
    
    return lcm;
}

unsigned long CShuffler::CalculateIterationsFromWraparounds()
{
    unsigned long iterations = 0;
    
    std::list<unsigned long>::iterator itr;
    itr = m_wrapAroundResults.begin();
    
    if (m_wrapAroundResults.size() == 0)
    {
        // This is an error case .. should never come here
    }
    if (m_wrapAroundResults.size() == 1)
    {
        iterations = *itr;
    }
    else
    {
        iterations = *itr;
        itr++;
        for (size_t i = 0; i < m_wrapAroundResults.size()-1; i++)
        {
            iterations = LCM(iterations, *itr);
            itr++;
        }
    }
    
    return iterations;
}
