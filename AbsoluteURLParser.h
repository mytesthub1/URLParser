///////////////////////////////////////////////////////////////////////////////
// Absolute URL structure:                                                   //
// <scheme> : [// <authority>] [/ <path>] [? <query>] [# <fragment>]         //
//                                                                           //
// Authority structure:                                                      //
// [userinfo @] host                                                         //
//                                                                           //
// Userinfo structure:                                                       //
// username [: password]                                                     //
//                                                                           //
// Host structure:                                                           //
// hostname [: port]                                                         //
//                                                                           //
// Query structure:                                                          //
// <argument> = <value> & <argument> = <value> & .... & <argument> = <value> //
///////////////////////////////////////////////////////////////////////////////
#ifndef AbsoluteURLParser_h
#define AbsoluteURLParser_h

#include <string>
#include <map>
#include <regex>


class AbsoluteURLParser
{
private:
    std::string _fullURL;
    bool _correctURL;
    std::string _message;

    std::string _sheme;
    std::string _authority;
    std::string _authority_userinfo;
    std::string _authority_userinfo_login;
    std::string _authority_userinfo_password;
    std::string _authority_host;
    std::string _authority_host_hostname;
    int         _authority_host_port;
    std::string _path;
    std::string _query;
    std::map<std::string, std::string> _query_map;
    std::string _fragment;

    bool _parseAuthority();
    bool _parseUserinfo();
    bool _parseHost();
    bool _parseQuery();
    bool _parseNextPair(const std::string &pair);
public:
    AbsoluteURLParser(const std::string &initURL);
    bool IsCorrect() const {return _correctURL;}
    const std::string& GetError() const {return _message;}

    // URL
    const std::string& GetFullURL() const {return _fullURL;}

    // First level
    const std::string& GetSheme()    const {return _sheme;     }
    const std::string& GetAutority() const {return _authority; }
    const std::string& GetPath()     const {return _path;      }
    const std::string& GetQuery()    const {return _query;     }
    const std::string& GetFragment() const {return _fragment;  }

    // Second level
    const std::string&                        GetUserinfo() const {return _authority_userinfo;  }
    const std::string&                        GetHost()     const {return _authority_host;      }
    const std::map<std::string, std::string>& GetQueryMap() const {return _query_map;           }

    // Third level
    const std::string& GetLogin()    const {return _authority_userinfo_login;    }
    const std::string& GetPassword() const {return _authority_userinfo_password; }
    const std::string& GetHostname() const {return _authority_host_hostname;     }
    const int         GetPort()     const {return _authority_host_port;         }

};

#endif /* AbsoluteURLParser_h */