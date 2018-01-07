#include "lab.h"

Heap::~Heap()
{
    //Destructor
    
    //delete [] buf;
}

bool Heap::Insert(Order x)
{
    if (isFull())
    {
        return false;
    }
        
    nNodes++; //The last node of the heap is now vacant
    
    //Starting from the (vacant) last node, go from node i to
    //its parent iParent and, as long as the parent is smaller
    //than x, move the parent down (MAX HEAP):
    
    int i = nNodes;
    int iParent;
    while (i > 1)
    {
        iParent = i/2;
        if(heapType == "buy")
        {
            if (x.price <= buf[iParent].price)
            {
                break;
            }
        }
        if(heapType == "sell")
        {
            if (x.price >= buf[iParent].price)
            {
                break;
            }
        }
        buf[i] = buf[iParent];  //Move the parent down
        i = iParent;            //buf[i] is now vacant
    }
    
    //Insert x into the created vacancy:
    buf[i] = x;
    
    return true;
}

bool Heap::Remove(Order &x)
{
    //Removes the largest element (from the root of the heap).
    //Retruns true if successful, false if the heap is empty.
    
    if (isEmpty())
    {
        return false;
    }
    
    //Retreat top element:
    x = buf[1];
    
    //Starting from the vacant root, go from node iParent to its
    //larger child i and, as long as the child is greater than the last 
    //element of the heap, move that child up:
    
    int iParent = 1; //root
    int i = 2; //its left child
    while (i <= nNodes)
    {
        if (heapType == "buy")
        {
            //Set i to the right child, i+1, if it exists and is larger:
            if (i < nNodes && buf[i].price < buf[i+1].price)
            {
                i++;
            }
            
            //Compare with the last node:
            if (buf[i].price <= buf[nNodes].price)
            {
                break;
            }
        }
        else if (heapType == "sell")
        {
            //Set i to the right child, i+1, if it exists and is larger:
            if (i < nNodes && buf[i].price > buf[i+1].price)
            {
                i++;
            }
            
            //Compare with the last node:
            if (buf[i].price >= buf[nNodes].price)
            {
                break;
            }
        }
        
        
        
        buf[iParent] = buf[i]; //Move the child up;
        iParent = 1;            //buf[iParent] is now vacant.
        i *= 2;                 //i is set to its left child
    }
    
    //Move the last element into the created vacancy:
    if (nNodes > 1)
    {
        buf[iParent] = buf[nNodes];
    }
    
    nNodes--;
    
    return true;
}

/**
    \brief This function is responsible for assigning the heap passed in as a parameter
    to the correct member variable heap within the Stock object. Since we have two heaps, 
    this function allows for a way to differeniate between the two heaps. It's mainly used
    for the readData() function.
    
    \param heap The heap that needs to be equated to one of the member variable heaps.
    \param heapType This tells us if the heap being passed in is a sell heap or a buy heap.
*/
void Stock::insertHeap(Heap heap, string heapType)
{
    if(heapType == "sell")
    {
        sellHeap = heap;
    }
    else if(heapType == "buy")
    {
        buyHeap = heap;
    }
}

/**
    \brief This function simply sets all the non-heap member variables of the Stock class
    to the appropriate value as passed in by parameter.
    
    \param pCompany This is the company the Stock object represents.
    \param pHiSale This is the highest sale price.
    \param pLowSale This is the lowest sale price.
    \param pLastSale This is the last sale price.
    \param pCurrentBid This is the root node's price amount of the buy heap.
    \param pBidSize This is the root node's share amount of the buy heap.
    \param pCurrentAsk This is the root node's price amount of the sell heap.
    \param pAskSize This is the root node's share amount of the sell heap.
*/
void Stock::setData(string pCompany,  string pHiSale, string pLowSale, string pLastSale, string pCurrentBid, string pBidSize, string pCurrentAsk, string pAskSize)
{
    company = pCompany;
    hiSale = stof(pHiSale);
    lowSale = stof(pLowSale);
    lastSale = stof(pLastSale);
    currentBid = stof(pCurrentBid);
    bidSize = stoi(pBidSize);
    currentAsk = stof(pCurrentAsk);
    askSize = stoi(pAskSize); 
}
