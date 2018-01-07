#include "lab.h"

void transaction(Url url, vector<Stock>& stock, Result &result)
{
    int i = findCompany(stock, url.company);
    
    if(url.action == "Buy")
    {
        Order buy;
        buy.name = url.name;
        buy.shares = stoi(url.shares);
        if (url.price != "Market")
        {
            buy.price = stof(url.enterPrice);
        }
        result.price = buy.price;
        //use market price if the buying price is high than the lowest selling price 
        //in the sellheap
        if (url.price == "Market" && stock[i].getHeap("sell").isEmpty())
        {
            buy.price = stock[i].getLastSale();
            result.priceAdjust = true;
            result.price = buy.price;
        }
        else if(url.price == "Market" || (!stock[i].getHeap("sell").isEmpty() && buy.price > stock[i].getHeap("sell").peak().price))
        {
            buy.price = stock[i].getHeap("sell").peak().price;
            result.priceAdjust = true;
            result.price = buy.price;
        }
        
        stock[i].getHeap("buy").Insert(buy);
    }
    else if (url.action == "Sell")
    {
        Order sell;
        sell.name = url.name;
        sell.shares = stoi(url.shares);
        if (url.price != "Market")
        {
            sell.price = stof(url.enterPrice);
        }
        result.price = sell.price;
        if(url.price == "Market" && stock[i].getHeap("buy").isEmpty())
        {
            sell.price = stock[i].getLastSale();
            result.priceAdjust = true;
            result.price = sell.price;
        }
        
        else if(url.price == "Market" || (!stock[i].getHeap("buy").isEmpty() && sell.price > stock[i].getHeap("buy").peak().price))
        {
            sell.price = stock[i].getHeap("buy").peak().price;
            result.priceAdjust = true;
            result.price = sell.price;
        }
        
        stock[i].getHeap("sell").Insert(sell);
    }

    if((!stock[i].getHeap("buy").isEmpty() && !stock[i].getHeap("sell").isEmpty()) && stock[i].getHeap("buy").peak().price == stock[i].getHeap("sell").peak().price)
    {
        Order buy, sell;
        //Remove both top nodes of buy and sell 
        stock[i].getHeap("buy").Remove(buy);
        stock[i].getHeap("sell").Remove(sell);
        //compare the share
        //if buy has larger share, push the rest buy share back
        //if sell has larger share, push the rest sell share back
        //if equal, don't push back
        if(buy.shares > sell.shares)
        {
            buy.shares -= sell.shares;
            stock[i].getHeap("buy").Insert(buy);
            stock[i].updateData(buy.price);
            
            
            if (buy.name == url.name)
            {
                result.success = true;
                result.partial = true;
                if (url.action == "Buy")
                {
                    result.shares = buy.shares;
                }
                else if (url.action == "Sell")
                {
                    result.shares = 0;
                }
            }
            else if (sell.name == url.name)
            {
                result.success = true;
                result.partial = true;
                if (url.action == "Buy")
                {
                    result.shares = buy.shares;
                }
                else if (url.action == "Sell")
                {
                    result.shares = 0;
                }
            }
            
        }
        else if(buy.shares < sell.shares)
        {
            sell.shares -= buy.shares;
            stock[i].getHeap("sell").Insert(sell);
            stock[i].updateData(sell.price);
            result.partial = true;
            
            if (buy.name == url.name)
            {
                result.success = true;
                result.partial = true;
                if (url.action == "Buy")
                {
                    result.shares = 0;
                }
                else if (url.action == "Sell")
                {
                    result.shares = sell.shares;
                }
            }
            else if (sell.name == url.name)
            {
                result.success = true;
                result.partial = true;
                if (url.action == "Buy")
                {
                    result.shares = 0;
                }
                else if (url.action == "Sell")
                {
                    result.shares = sell.shares;
                }
            }
        }
        else
        {
            stock[i].updateData(buy.price);
            result.success = true;
        }
    }
    
    stock[i].updateCurrent();
}
