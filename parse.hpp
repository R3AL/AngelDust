# pragma once
# include <fstream>
# include <iostream>
# include <string>
# include <sstream>
# include <vector>

namespace AD
{
    struct _func
    {
        _func() = default;
        _func(std::string f, std::vector<std::string> p) : func(f), params(p) {}
        std::string func;
        std::vector<std::string> params;
    };
    struct config
    {
        config() = default;
        config(std::string an) : appname(an) {}
        std::string appname;
        std::vector<_func> funcs;
    };

    std::vector<std::string> split(std::string str, const char delim) {
        std::vector<std::string> v;
        std::string tmp;

        for(auto i = str.begin(); i <= str.end(); ++i) 
            if(*i != delim && i != str.end()) 
                tmp += *i; 
            else 
            {
                v.push_back(tmp);
                tmp = ""; 
            }   
        return v;
    }

    void parse(const std::string& file, std::vector<config>& ret)
    {
        using namespace std;
        ifstream config(file);

        stringstream buffer;
        buffer << config.rdbuf();

        string content(buffer.str());
        config.close();

        string pname;
        {
            auto i1 = content.find_first_of('"');
            auto i2 = content.find_first_of('"', i1 + 1);
            pname = content.substr(i1 + 1, i2 - i1 - 1);
            content = content.substr(i2 + 1);
        }
        struct config tmp;
        tmp.appname = pname;

        do
        {
            string command;
            string params;
            auto i1 = content.find_first_of('"');
            auto i2 = content.find_first_of('"', i1 + 1);
            command = content.substr(i1 + 1, i2 - i1 -1);
            content = content.substr(i2 + 1);

            if(command.find(']') != string::npos)
                break;

            if(content[0] == ':')
            {
                auto i3 = content.find_first_of('"');
                auto i4 = content.find_first_of('"', i3 + 1);
                params = content.substr(i3 + 1, i4 - i3 - 1);
                content = content.substr(i4 + 1);
            }

            tmp.funcs.push_back( _func(command, split(params, ' ')) );

        }while(content.length()>0);
        ret.push_back(tmp);
    }    
} // End of AD namespace
