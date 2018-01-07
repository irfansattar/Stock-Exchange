#include "lab.h"

void resultPage(Url url, Result result, string quote)
{    
    cout << "<html>"
    "    <head>"
    "            <title>Stock Exchange Lab</title>  <!--Tab title -->"
    "            <link href=\"https://fonts.googleapis.com/css?family=Open+Sans\" rel=\"stylesheet\">"
    "            <script>"
    "                function goBack(){"
    "                    window.history.back()"
    "                 }"
    "            </script>"
    "            <style type=\"text/css\">         "         /*CSS to make the HTML form look pretty */
    "                body{"
    "                    background-image: url(/cs-124/final/rick-tap-110126.jpg);"
    "                    background-size: cover;"
    "                    background-repeat: no-repeat;"
    "                }"

    "                input{"
    "                    padding: 10px 10px;"
    "                    color: #2c3e50;"
    "                }"

    "                input[type=submit]{"
    "                    font-family: 'Open Sans', Century Gothic, Helvetica, Geneva, sans-serif;"
    "                    font-size: 1.5vw;"
    "                }"
                    
    "                div{"
    "                    background-color: rgba(189, 195, 199, .9);"
    "                    display: inherit;"
    "                    margin: auto;"
    "                    width: 40%;"
    "                    padding: 13px;"
    "                    border-radius: 5px;"
    "                    font-size: 20px;"
    "                    font-size: 2vw;"
    "                    font-family: 'Open Sans', Century Gothic, Helvetica, Geneva, sans-serif;"
    "                }"
                    
    "                img{"
    "                    max-width:100%;"
    "                }"
                    
    "                table{"
    "                    width: auto; "
    "                    table-layout: fixed;"
    "                }"
                    
    "                .tableH{"
    "                    background-color: rgba(60,136,126,0.6);"
    "                    border: 1px solid rgba(60,136,126,1);"
    "                    padding: 15px 30px;"
    "                    text-align: center;"
    "                }"

    "                th, .dblue{"
    "                    background-color: rgba(34,68,85,0.5);"
    "                    padding: 15px 30px; "
    "                    text-align: center; "
    "                    font-weight: 500; "
    "                    font-size: 12px;"
    "                    color: #fff; "
    "                    text-transform: uppercase; "
    "                }"
                            
    "                .dblue{ "
    "                    padding: 8px;            "
    "                    border: 1px solid rgba(34,68,85,0.7);"
    "                } "

    "                .lblue{"
    "                    background-color: rgba(119,170,170,0.5); "
    "                    height:3px; "
    "                    overflow-x:auto; "
    "                    margin-top: 0px; "
    "                    border: 1px solid rgba(85,119,136,0.7);"
    "                    padding: 8px;"
    "                    text-align: center; "
    "                    vertical-align: middle; "
    "                    font-weight: 300;"
    "                    font-size: 15px; "
    "                    color: #37474f;"
    "                    border-bottom: solid 1px rgba(85,119,136,0.7); "
    "                } "

    "                td{ "
    "                    height:3px; "
    "                    overflow-x:auto; "
    "                    margin-top: 0px;"
    "                    padding: 8px; "
    "                    text-align: center; "
    "                    vertical-align: middle; "
    "                    font-weight: 300; "
    "                    font-size: 15px; "
    "                }"
                    
    "                hr{"
    "                    border: 0;"
    "                    height: 1px;"
    "                    background-image: -webkit-linear-gradient(left, rgba(189, 195, 199, .6), #8c8b8b, rgba(189, 195, 199, .6));"
    "                    background-image: -moz-linear-gradient(left, rgba(189, 195, 199, .6), #8c8b8b, rgba(189, 195, 199, .6));"
    "                    background-image: -ms-linear-gradient(left, rgba(189, 195, 199, .6), #8c8b8b, rgba(189, 195, 199, .6));"
    "                    background-image: -o-linear-gradient(left, rgba(189, 195, 199, .6), #8c8b8b, rgba(189, 195, 199, .6));"
    "                }"
    "            </style>"
    "        </head>"

    "        <body>    "
    "            <div>  <!--HTML Form -->"
    "            <form action=\"/cs-124/final/stockOriginal.html\" method=\"GET\">  <!--Forward user's input to the cgi file -->"
    "                <center>"
    "                   <p style=\"font-size: 2.7vw; padding-bottom: 0.5%\">Stock Exchange Lab</p>";
    
    if (url.formType == "Quote")
    {
        cout << "<p style=\"font-size: 2.2vw; margin-top: 3px; margin-bottom: 15px; padding-top: 0.5%\">Your requested quote information is below:</p>" << endl;
        cout << "<p style=\"font-size: 1.4vw; margin-top: 3px; margin-bottom: 15px; padding-top: 0.5%\">" << quote << "</p>";        
        
    }
    else if (url.formType == "Order")
    {
        cout << "<p style=\"font-size: 2.2vw; margin-top: 3px; margin-bottom: 15px; padding-top: 0.5%\">Your order details are below:</p>" << endl;
        
        if (result.success)
        {
            if (result.partial)
            {
                cout << "<p style=\"font-size: 1.6vw; margin-top: 3px; margin-bottom: 15px; padding-top: 0.5%\">Your transaction has been partially processed. ";
                if (url.action == "Buy")
                {
                    cout << "The number of shares you were buying was greater than those willing to be sold.</p>" << endl;
                    cout << "<p style=\"font-size: 1.4vw; margin-top: 3px; margin-bottom: 15px; padding-top: 0.5%\">You bought <b>" << (stoi(url.shares) - result.shares) << "</b> stocks of <b>" << url.company << "</b> for <b>$" << result.price << "</b>.</p>" << endl;
                    if (result.priceAdjust)
                    {
                        cout << "<p style=\"font-size: 1.2vw; margin-top: 3px; margin-bottom: 15px; padding-top: 0.5%\">NOTE - Your price was adjusted because you either picked Market or because your buying price was too high. </p>" << endl;
                    }
                    cout << "<p style=\"font-size: 1.6vw; margin-top: 3px; margin-bottom: 15px; padding-top: 0.5%\">The remaining portion of your order has been added to a queue for future processing.</p>" << endl;
                }
                else if (url.action == "Sell")
                {
                    cout << "The number of shares you were selling was greater than those willing to be bought.</p>" << endl;
                    cout << "<p style=\"font-size: 1.4vw; margin-top: 3px; margin-bottom: 15px; padding-top: 0.5%\">You sold <b>" << (stoi(url.shares) - result.shares) << "</b> stocks of <b>" << url.company << "</b> for <b>$" << result.price << "</b>.</p>" << endl;
                    if (result.priceAdjust)
                    {
                        cout << "<p style=\"font-size: 1.2vw; margin-top: 3px; margin-bottom: 15px; padding-top: 0.5%\">NOTE - Your price was adjusted because you either picked Market or because your selling price was too high. </p>" << endl;
                    }
                    cout << "<p style=\"font-size: 1.6vw; margin-top: 3px; margin-bottom: 15px; padding-top: 0.5%\">The remaining portion of your order has been added to a queue for future processing.</p>" << endl;
                }
            }
            else
            {
                cout << "<p style=\"font-size: 1.6vw; margin-top: 3px; margin-bottom: 15px; padding-top: 0.5%\">Your transaction was a success! The details are as follow:</p>" << endl;
                if (url.action == "Buy")
                {
                    cout << "<p style=\"font-size: 1.4vw; margin-top: 3px; margin-bottom: 15px; padding-top: 0.5%\">You bought <b>" << url.shares << "</b> stocks of <b>" << url.company << "</b> for <b>$" << result.price << "</b>.</p>" << endl;
                    if (result.priceAdjust)
                    {
                        cout << "<p style=\"font-size: 1.2vw; margin-top: 3px; margin-bottom: 15px; padding-top: 0.5%\">NOTE - Your price was adjusted because you either picked Market or because your buying price was too high. </p>" << endl;
                    }
                }
                else if (url.action == "Sell")
                {
                    cout << "<p style=\"font-size: 1.4vw; margin-top: 3px; margin-bottom: 15px; padding-top: 0.5%\">You sold <b>" << url.shares << "</b> stocks of <b>" << url.company << "</b> for <b>$" << result.price << "</b>.</p>" << endl;
                    if (result.priceAdjust)
                    {
                        cout << "<p style=\"font-size: 1.2vw; margin-top: 3px; margin-bottom: 15px; padding-top: 0.5%\">NOTE - Your price was adjusted because you either picked Market or because your selling price was too high. </p>" << endl;
                    }
                }                
            }
        }
        else
        {
            cout << "<p style=\"font-size: 1.6vw; margin-top: 3px; margin-bottom: 15px; padding-top: 0.5%\">Your transaction did not get processed. It has been added to a queue for future processing!</p>" << endl;
        }
        
    }
    
    
//    "                <p style=\"font-size: 2.5vw; padding-bottom: 0.5%\">Stock Exchange Lab</p>"
//    "                <table>"
//    "                    <tr><td colspan=\"4\" style=\"font-size: 1.7vw; margin-top: 3px; margin-bottom: 15px; padding-top: 0.5%\">Your Message & Translation</td></tr>"
//    "                    <tr><td class=\"tableH\" style=\"font-size: 22px;  border-collapse: collapse;\">Message</td> <td class=\"tableH\" style=\"font-size: 22px; margin-top: 3px; margin-bottom: 15px; border-collapse: collapse;\">" 
    
//    /*<< message << */"</td>";
    
//   //cout << 
//    "                    <tr><td class=\"dblue\"> Translation </td> <td class=\"lblue\">"
//    /*<< translation << */"</td>"; 
    
    
    cout <<             
//    "                    <tr><td colspan=\"4\"><hr><p style=\"font-size: 18px; margin-top: 7px;\"> Thank you! </td></tr></p>"
//    "                    <tr><td colspan=\"4\"><input class=\"button\" type=\"submit\" value=\"Return to home page\"></td></tr>"
//    "                </table>     "
    "                    <input class=\"button\" type=\"submit\" value=\"Return to home page\">"
    "                </center>"
    "            </form>"
    "            </div>"
    "        </body>"
    "        </html>";

}
