#include "lab.h"

void writeData(vector<Stock> &stockMarket)
{
    //Go through each index of the vector; at each index, there is a Stock
    //object; write all the information stored in all the member variables
    //into the file, all the quote related data and the two heaps using 
    //the following format:
    //company|BUYHEAP(MAXHEAP) Amount,Shares,Name Amount,Shares,Name Amount,Shares,Name|SELLHEAP(MINHEAP) Amount,Shares,Name Amount,Shares,Name|DATA Hi:Amount Low:Amount Last:Amount Bid:Amount BidSize:Amount Ask:Amount AskSize:Amount
    
    ofstream ofs("/home/debian/cs-124/final/data.txt");
    for (int i = 0; i < stockMarket.size(); i++)
    {
        ofs << stockMarket[i].getCompany() << "|";
        
        //DOES IT MATTER WHAT ORDER WE WRITE THE HEAP TO THE FILE?
        //SINCE WHEN WE READ IT BACK IN AND INSERT WOULDN'T IT REHEAP ANYWAYS?
        Heap heap = stockMarket[i].getHeap("buy");        
        Order order;
        long pos;
        
        if (!heap.isEmpty())
        {
            while(heap.Remove(order))
            {
                ofs << order.price << "," << order.shares << "," << order.name << " ";
            }
            
            pos = ofs.tellp();
            ofs.seekp(pos-1);
            ofs << "|";
        }
        else
        {
            ofs << "|";
        }
                
        heap = stockMarket[i].getHeap("sell");
        
        if (!heap.isEmpty())
        {
            while(heap.Remove(order))
            {
                ofs << order.price << "," << order.shares << "," << order.name << " ";
            }
            
            pos = ofs.tellp();
            ofs.seekp(pos-1);
            ofs << "|";
        }
        else
        {
            ofs << "|";
        }
        
        ofs << fixed << setprecision(2) << stockMarket[i].getData();
        ofs << '\n';
    }
        
    ofs.close();
}
