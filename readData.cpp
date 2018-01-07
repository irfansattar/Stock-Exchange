#include "lab.h"

void readData(vector<Stock> &stockMarket)
{
    //Pass in vector (by reference) to hold data, each index has stock object which itself has heap objects
    //and thus we hold all the data
    //Create a stock and heap object and add it into our vector
    //
    //Sample data.txt line:
    //company|BUYHEAP(MAXHEAP) Amount,Shares,Name Amount,Shares,Name Amount,Shares,Name|SELLHEAP(MINHEAP) Amount,Shares,Name Amount,Shares,Name|DATA Hi:Amount Low:Amount Last:Amount Bid:Amount BidSize:Amount Ask:Amount AskSize:Amount
    
    //cout << "Test 1" << endl;
    
    ifstream ifs("/home/debian/cs-124/final/data.txt");
    if(!ifs)
    {
        cout << "ERROR - File failed to open." << endl;
    }
    
    string line;
    while(getline(ifs, line))
    {
        //cout << "Test 2" << endl;
        string heap, order, tempString;
        string company, hiSale, lowSale, lastSale, currentBid, bidSize, currentAsk, askSize;
        Heap tempBuyHeap;
        Heap tempSellHeap;
        Stock tempStock;
        
        //cout << "Test 3" << endl;
        
        stringstream ss(line);
        
        getline(ss, company, '|');
        
        //cout << "Test 4" << endl;
        
        for(int i = 0; i < 2; i++)
        {
            //cout << "Test 5" << endl;
            
            getline(ss, heap, '|');
            
            if (i == 0)
            {
                tempBuyHeap.setType("buy");
            }
            else if (i == 1)
            {
                tempSellHeap.setType("sell");
            }
            
            //cout << "Test 6" << endl;
            
            stringstream ssHeap(heap);
            while(getline(ssHeap, order, ' '))
            {
                //cout << "Test 6.1" << endl;
                Order tempOrder;
                string temp;
                
                //cout << "Test 6.2" << endl;
                
                stringstream ssOrder(order);
                getline(ssOrder, temp, ',');
                tempOrder.price = stof(temp);
                getline(ssOrder, temp, ',');
                tempOrder.shares = stoi(temp);
                getline(ssOrder, tempOrder.name);
                
                //cout << "Test 6.3" << endl;
                //cout << tempHeap.getType() << endl;
                
                //cout << tempOrder.shares << tempOrder.price << tempOrder.name << endl;
                
                if (i == 0)
                {
                    tempBuyHeap.Insert(tempOrder);
                }
                else if (i == 1)
                {
                    tempSellHeap.Insert(tempOrder);
                }
                
                //cout << "Test 7" << endl;
            }
            
            if(i == 0)
            {
                tempStock.insertHeap(tempBuyHeap, "buy"); //Store heap in tempStock before overriding for min heap
            }
            else if (i == 1)
            {
                tempStock.insertHeap(tempSellHeap, "sell"); //Store heap in tempStock before overriding for min heap
            }
        }
        
        //cout << "Test 8" << endl;
        
        while (ss)
        {
            //cout << "Test 9" << endl;
            
            getline(ss, tempString, ':');
            
            if (tempString == "Hi")
            {
                getline(ss, tempString, ' ');
                hiSale = tempString;
            }
            else if (tempString == "Low")
            {
                getline(ss, tempString, ' ');
                lowSale = tempString;
            }
            else if (tempString == "Last")
            {
                getline(ss, tempString, ' ');
                lastSale = tempString;
            }
            else if (tempString == "Bid")
            {
                getline(ss, tempString, ' ');
                currentBid = tempString;
            }
            else if (tempString == "BidSize")
            {
                getline(ss, tempString, ' ');
                bidSize = tempString;
            }
            else if (tempString == "Ask")
            {
                getline(ss, tempString, ' ');
                currentAsk = tempString;
            }
            else if (tempString == "AskSize")
            {
                getline(ss, tempString, ' ');
                askSize = tempString;
            }
        }
        
        //cout << "Test 10" << endl;
        
        tempStock.setData(company, hiSale, lowSale, lastSale, currentBid, bidSize, currentAsk, askSize);
        stockMarket.push_back(tempStock);
        
        //cout << "Test 11" << endl;
    }
    
    //cout << "Finished getting data." << endl;
    ifs.close();
}
