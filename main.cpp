#include "lab.h"

/**
    \brief This function is the main function. It first calls the readForm() function to 
    parse the HTML url input. Then, it calls the readData() function to read the data from the 
    text file. Then, it processes the user's request, saves the programs data to the file and 
    finally calls the resultPage() function to display the results webpage.
    
    \param pOption This variable, which is passed in by reference, will hold the
    option the user chose, whether encode or decode.
    \param pMessage This variable, which is also passed in by reference, will hold
    the user's message.
*/
int main()
{
    Url url; //Struct that will contain parsed url data   
    Result result; //Struct that contains the transaction status  
    readForm(url); //Populating the struct with the HTML URL data
    string quote;
    
    vector<Stock> stockMarket;
    
    //cout << "Test 1" << endl;
    readData(stockMarket);
    if (url.formType == "Quote")
    {
        quote = stockMarket[findCompany(stockMarket, url.company)].getDataHTML();
    }
    else if (url.formType == "Order")
    {
        transaction(url, stockMarket, result);
    }
    
    //cout << "Test 2" << endl;
    writeData(stockMarket);
    //cout << "Test 3" << endl;
    resultPage(url, result, quote);
    
    /*cout << "Name: " << url.name << endl;
    cout << "Action: " << url.action << endl;
    cout << "Company: " << url.company << endl;
    cout << "Shares: " << url.shares << endl;
    cout << "Price: " << url.price << endl;
    cout << "Enter Price: " << url.enterPrice << endl;
    cout << "Form Type: " << url.formType << endl;
    */
}
