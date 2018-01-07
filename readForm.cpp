#include "lab.h"

void readForm(Url &url)
{
    string s = getenv("QUERY_STRING"); //EX: s may be "option=Encode&Message=Hello+there" after this line
    string tempString;
    
    stringstream ss;
    
    ss << s;
    
    while(ss)
    {
        getline(ss, tempString, '='); //Go up till =
        
        if(tempString == "action")  //If that's an option go up till &
        {
            getline(ss, url.action, '&');
        }
        else if (tempString == "company")
        {
            getline(ss, url.company, '&');
        }
        else if (tempString == "shares")
        {
            getline(ss, url.shares, '&');
        }
        else if (tempString == "price")
        {
            getline(ss, url.price, '&');
        }
        else if (tempString == "enter_price")
        {
            getline(ss, url.enterPrice, '&');
        }
        else if (tempString == "formType")
        {
            getline(ss, url.formType, '&');
        }
        else if (tempString == "name")
        {
            getline(ss, url.name, '&');
        }
        
        //~ else if(tempString == "Message") //If that's a message, in a loop go up till + 
        //~ {                                       //to parse entire message
            //~ while(getline(ss, tempString, '+'))
            //~ {                               
                //~ if(tempString == "%2F")
                //~ {
                    //~ pMessage += "/ ";
                //~ }
                //~ else
                //~ {
                    //~ pMessage += tempString + " ";
                //~ }                
            //~ }
            //~ pMessage = pMessage.substr(0, pMessage.length() - 1);
        //~ }
    }
}
