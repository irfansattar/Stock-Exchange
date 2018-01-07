#include "lab.h"

int findCompany(vector<Stock> stock, string company)
{
    for (int i = 0; i < stock.size(); i++)
    {
        if(stock[i].getCompany() == company)
        {
            return i;
        }
    }
}
