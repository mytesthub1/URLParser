#include <iostream>
#include <set>
#include "AbsoluteURLParser.h"

void PrintURLInfo(const AbsoluteURLParser &url);
int UrlTest();




void PhoneMatch()
{
    std::string s;

    s = "(095) 121-11-21";

    if(!std::regex_match(s, std::regex("\\(?\\d{3}\\)?\\s?\\d{3}-?\\d{2}-?\\d{2}")))
    {
        std::cout << "invalid phone" << std::endl;
    }
}


int main(int argc, char** argv)
{

    PhoneMatch();

}




int UrlTest()
{
    std::set<std::string> examples;



    examples.insert("https://LOGIN:qwer@ru.m.wikipedia.org:8080/wiki/URL/index.html?key1=val1&key2=2&key3=rt$34&key4=val4#fragid");

    /*
    examples.insert("https://nikita:qwer@ru.m.wikipedia.org:8080/wiki/URL/index.html?key1=val1&key2=val2&key3=val3&key4=val4#fragid");
    examples.insert("https://nikita@ru.m.wikipedia.org:8080/wiki/URL/index.html?key1=val1&key2=val2&key3=val3&key4=val4#fragid");
    examples.insert("https://nikita:qwer@ru.m.wikipedia.org/wiki/URL/index.html?key1=val1&key2=val2&key3=val3&key4=val4#fragid");
    examples.insert("https://ru.m.wikipedia.org:8080/wiki/URL/index.html?key1=val1&key2=val2&key3=val3&key4=val4#fragid");
    examples.insert("https://ru.m.wikipedia.org/wiki/URL/?key1=val1&key2=val2&key3=val3&key4=val4#fragid");
    examples.insert("https://ru.m.wikipedia.org/wiki/URL?key1=val1&key2=val2&key3=val3&key4=val4#fragid");
    examples.insert("https:/wiki/URL/index.html?key1=val1&key2=val2&key3=val3&key4=val4#fragid");
    examples.insert("https://ru.m.wikipedia.org/wiki/URL/index.html?key1=val1#fragid");
    examples.insert("https://ru.m.wikipedia.org/wiki/URL/index.html?key1=val1");
    examples.insert("https://ru.m.wikipedia.org/wiki/URL/index.html#fragid");
    examples.insert("https:?key1=val1&key2=val2&key3=val3&key4=val4#fragid");
    examples.insert("https://ru.m.wikipedia.org");
    examples.insert("ru.m.wikipedia.org");
    examples.insert("https:#fragid");
    examples.insert("https:");
    */
    examples.insert("");

    for(auto it : examples) {
        AbsoluteURLParser url_example(it);
        PrintURLInfo(url_example);
    }

    return 0;
}



void PrintURLInfo(const AbsoluteURLParser &url)
{
    std::cout << "\n----------" << std::endl;
    std::cout << "Full URL:     " << url.GetFullURL()   << std::endl;

    if(!url.IsCorrect())
    {
        std::cout << "URL is incorrect because " << url.GetError() << std::endl;
    } else {
        std::cout << "Sheme:        " << url.GetSheme()     << std::endl;
        std::cout << "Autority:     " << url.GetAutority()  << std::endl;
        std::cout << "  Userinfo:   " << url.GetUserinfo()  << std::endl;
        std::cout << "    Login:    " << url.GetLogin()     << std::endl;
        std::cout << "    Password: " << url.GetPassword()  << std::endl;
        std::cout << "  Host:       " << url.GetHost()      << std::endl;
        std::cout << "    Hostname: " << url.GetHostname()  << std::endl;

        std::cout << "    Port:     ";
        (url.GetPort() == -1) ? std::cout << "default" : std::cout << url.GetPort();
        std::cout << std::endl;

        std::cout << "Path:         " << url.GetPath()      << std::endl;
        std::cout << "Query:        " << url.GetQuery()     << std::endl;

        for(auto it : url.GetQueryMap())
            std::cout << "  [" << it.first << "] = " << it.second << std::endl;

        std::cout << "Fragment:     " << url.GetFragment()  << std::endl;
    }
}