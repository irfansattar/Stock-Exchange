#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

/**
    \brief This struct's function is to store the data passed in from the HTML url
    into member variables so they can be easily accessed. It stores things like
    whether the user is asking for a quote or placing an order (formType), what company
    they are interested in, information on shares, price, and whether they want to
    buy/sell.
*/
struct Url
{
    string action;
    string company; 
    string shares;
    string price;
    string enterPrice;
    string formType;
    string name;
};

/**
    \brief This struct stores some key information about the status of the 
    transaction in the case that a user places an order. It stores information
    like whether the transaction went through or if it failed, whether the transaction
    ended up being a partial transaction or not, and whether the user's price was adjusted.
*/
struct Result
{
    bool success = false;
    bool partial = false;
    bool priceAdjust = false;
    int shares = 0;
    float price;
};

/**
    \brief This struct only contains key information about the user's order. That is, it
    includes their name, number of shares they want to buy/sell, and the price. This data
    would be taken from the Url struct. This struct is also the thing that our heaps are made
    of. 
*/
struct Order
{
    string name;
    int shares;
    float price;
};

class Heap
{
    public:
        Heap()
        {
            nNodes = 0;
            size = 100;
            buf = new Order[size];
        }
        Heap(string heapType)
        {
            heapType = heapType;
            nNodes = 0;
            size = 100;
        }
        ~Heap();
        void setType(string type)
        {
            heapType = type;
        }
        string getType()
        {
            return heapType;
        }
        bool isEmpty()
        {
            return bool(nNodes == 0);
        }
        bool isFull()
        {
            return bool(nNodes == size);
        }
        bool Insert(Order x);
        bool Remove(Order &x);
        Order peak()
        {
            return buf[1];
        }
        
    private:
        int size;
        string heapType;
        int nNodes;
        Order *buf;
};

/**
    \brief This class is our Stock class. It represents our companies within our program. Each
    object of this class in a company within our stock market. It contains two heaps that
    are used for managing and priortizing the orders the user's submit. One of the heaps is the
    buy heap and the other heap is the sell heap. The class also contains some other member 
    variables to hold data such as the highest/lowest sale price, the last sale price, etc.
*/
class Stock
{
    public:
        Stock() : sellHeap("sell") , buyHeap("buy") { /*EMPTY CONSTRUCTOR BODY*/}
        void setData(string company, string hiSale, string lowSale, string lastSale, string currentBid, string bidSize, string currentAsk, string askSize);
        
        /**
            \brief This function is responsible for returning the non-heap member variables
            as a string. It's used mainly for the writeData() function.
            
            \return Returns a string that contains the non-heap member variables
        */
        string getData()
        {
            return ("Hi:" + to_string(hiSale) + " Low:" + to_string(lowSale) + " Last:" + to_string(lastSale) + " Bid:" + to_string(currentBid) + " BidSize:" + to_string(bidSize) + " Ask:" + to_string(currentAsk) + " AskSize:" + to_string(askSize));
        }
        
        /**
            \brief This function is responsible for returning a string of the non-heap
            member variables with HTML formatting. It is used by the resultPage() function
            if the user requested a quote.
            
            \return Returns a string containing the non-heap member variables with 
            HTML formatting.
        */
        string getDataHTML()
        {
            return ("Company: " + company + "<br>Hi: " + to_string(hiSale) + " Low: " + to_string(lowSale) + " Last: " + to_string(lastSale) + "<br>Bid: " + to_string(currentBid) + " Bid Size: " + to_string(bidSize) + "<br>Ask: " + to_string(currentAsk) + " Ask Size: " + to_string(askSize));
        }
        
        void insertHeap(Heap heap, string heapType);
        
        /**
            \brief This function returns the company member variable.
            
            \return Returns a string containing the company member variable's value
        */
        string getCompany()
        {
            return company;
        }
        
        /**
            \brief This function is used to return one of the member heaps' address. 
            
            \param type This variable contains the type of heap that needs to be returned,
            either the buy or sell heap.
            \return Returns the appropriate heap by reference.
        */
        Heap& getHeap(string type)
        {
            if (type == "buy")
            {
                return buyHeap;
            }
            else if (type == "sell")
            {
                return sellHeap;
            }
        }
        
        /**
            \brief This function returns the lastSale member variable
            
            \return Returns the lastSale member variable
        */
        float getLastSale()
        {
            return lastSale;
        }
        
        /**
            \brief This function updates the highest, lowest, and last sale prices.
            
            \param a This is the price of the last sale passed in which is used for updating
            the member variables.
        */
        void updateData(float a)
        {
            lastSale = a;
            if (lastSale > hiSale)
            {
                hiSale = lastSale;
            }
            else if (lastSale < lowSale)
            {
                lowSale = lastSale;
            }
        }
        
        /**
            \brief This function is used for updating the member variables related to the
            root nodes of both heap.
        */
        void updateCurrent()
        {
            currentBid = buyHeap.peak().price;
            bidSize = buyHeap.peak().shares;
            currentAsk = sellHeap.peak().price;
            askSize = sellHeap.peak().shares;
        }
        
    private:
        float hiSale, lowSale, lastSale, currentBid, currentAsk;
        int bidSize, askSize;
        string company;
        Heap sellHeap; //min heap
        Heap buyHeap; //max heap
};

/**
    \brief This function is responsible for parsing the user's input which is
    received by the program as a STRING_QUERY. It takes the information sent by 
    the browser and parses out each piece of relavent data and stores it in our Url struct
    so the data can be used later in our program.
    
    \param url This member variable is the Url struct that our data will be stored it. It is
    also passed in by reference.
*/
void readForm(Url &url);

/**
    \brief This function is responsible for reading the data stored in the data.txt
    text file. That file stores the data between program executions since all data is
    lost once the program ends. Thus, it's stored in the data.txt file. Therefore, this 
    function's purpose is to read the data back into the program from the data file at the start
    of the program. Each line of the file represents a Stock object. There are four different
    sections in each line, each of which are seperated by the '|' symbol. The function parses
    up until a '|' symbol and stores the data it read into the appropriate variable. Certain
    sections are further parsed to seperate groups of data. For example, the two heaps contain
    Order structs in them. Each of these are seperated by a space. Therefore, the function would
    also have to parse within the heaps, separating the multiple Order structs. Therefore, this
    function parses on multiple levels to seperate and read all the relavent data back into
    the program.
    
    \param stockMarket This is a vector that is supposed to contain our multiple Stock objects
    (each of which represents a company). This vector is also passed in by reference. This is
    where all the parsed data will be stored in.
*/
void readData(vector<Stock> &stockMarket);

/**
    \brief This function is responsible for storing all the data within our program. Once our 
    program ends, all the data it uses will be lost so unless it is stored in a text file, 
    the next time the program runs, it will start from scratch and this is not something we
    want. Therefore, this function is responsible for writing all the data within our program
    to a text file. When doing so, it simply goes through each Stock object within the vector
    that is passed in as a parameter and writes its member variables. This means it writes things
    like the company name, the highest/lowest/last sale price, the various Order structs stored
    within our heaps, etc to the file.
    
    \param stockMarket This is the vector of data we need to write to the file so it can be
    stored for future program executions.
*/
void writeData(vector<Stock> &stockMarket);

/**
    \brief This function is responsible for handling a transaction. If the user decides to
    place an order, this is the function that gets called. It takes in the user's inputed data and
    the stock market that contains all our different companies and walks through the apporpiate
    course of action. It first takes the user's data and creates an Order struct which it inputs
    into the correct heap of the correct company in question. Then, it determines if a transaction
    is possible based on if the price member of the Order struct of the root nodes of the heaps match.
    If this happens, it then looks at the shares to seperate a partial sale from a perfect sale
    and processes the transaction. The status of the transaction, things like if it was a success,
    if the sale was a partial sale, etc are also stored in another struct that was passed in
    as a parameter.
    
    \param url This struct contains the parsed user input which was received from the
    HTML page url.
    \param stock This is our stock vector that contains the Stock objects of all the different
    companies. 
    \param result This is the struct the transaction status information will be stored in.
*/
void transaction(Url url, vector<Stock>& stock, Result &result);

/**
    \brief This function simply finds and returns the index at which one of the companies
    in the vector is located.
    
    \param stock This is the vector which the function will loop through to find the company
    in question.
    \param company This is the company being searched for.
*/
int findCompany(vector<Stock> stock, string company);

/**
    \brief This function is responsible for printing out the HTML code to display the 
    results webpage. It displays the correct result based on what the user initially inputed.
    It looks at the initial input and determines whether to display text related to quotes
    or a transaction and then finds that info from the other parameters passed in and displays
    said info correctly.
    
    \param url This is the user's input stored in a Url struct
    \param result This is the Result struct that contains info on the transaction status
    from the transaction function
    \param quote This variable contains a string with the quote data in case the user asked
    for a quote instead of submitting an order
*/
void resultPage(Url url, Result result, string quote);
