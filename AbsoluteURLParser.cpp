#include "AbsoluteURLParser.h"

AbsoluteURLParser::AbsoluteURLParser(const std::string &initURL)
        : _fullURL(initURL),
          _correctURL(true),
          _message(""),
          _sheme(""),
          _authority(""),
          _authority_userinfo(""),
          _authority_userinfo_login(""),
          _authority_userinfo_password(""),
          _authority_host(""),
          _authority_host_hostname(""),
          _authority_host_port(-1),
          _path(""),
          _query(""),
          _fragment("")
{
    std::string lostPart = _fullURL;
    std::smatch result;

    if ( std::regex_search(lostPart, result, std::regex("[:]") ) ) {
        _sheme = result.prefix().str();
        lostPart = result.suffix().str();
        // Available symbols are: ALPHA, DIGIT, "+", "-", "."
        if(!std::regex_match(_sheme, std::regex( "[[:alpha:][:digit:]\.\+\-]+" ) )) {
            _message = "<sheme> component is incorrect";
            _correctURL = false;
            return;
        }
    } else {
        _message = "<sheme> component is necessary";
        _correctURL = false;
        return;
    }

    if ( std::regex_search(lostPart, result, std::regex("[\#]") ) ) {
        _fragment = result.suffix();
        lostPart = result.prefix();
        if ( std::regex_search(_fragment, result, std::regex("[\#]") ) ) {
            _message = "<fragment> component is incorrect";
            _correctURL = false;
            return;
        }
    }

    if ( std::regex_search(lostPart, result, std::regex("[\?]") ) ) {
        _query = result.suffix().str();
        lostPart = result.prefix().str();
        if ( std::regex_search(_query, result, std::regex("[\?]") ) ) {
            _message = "<query> component is incorrect";
            _correctURL = false;
            return;
        }
    }

    if ( std::regex_search(lostPart, result, std::regex("[\/]{2}") ) ) {
        lostPart = result.suffix().str();
        if ( std::regex_search(lostPart, result, std::regex("\/") ) ) {
            _authority = result.prefix().str();
            _path = result.suffix().str();
        } else {
            _authority = lostPart;
        }
    } else {
        if ( std::regex_search(lostPart, result, std::regex("[\/]") ) ) {
            _path = result.suffix().str();
            lostPart = result.prefix().str();
            if(lostPart.size() != 0) {
                _message = "incorrect URL";
                _correctURL = false;
                return;
            }
        }
    }

    if(_authority.size() != 0)
        if(!_parseAuthority()) {
            _message = "<authority> component is incorrect";
            _correctURL = false;
            return;
        }

    if(_query.size() != 0)
        if(!_parseQuery()) {
            _message = "<query> component is incorrect";
            _correctURL = false;
            return;
        }
}

bool AbsoluteURLParser::_parseAuthority()
{
    std::smatch result;
    if ( std::regex_search(_authority, result, std::regex("[@]") ) ) {
        _authority_userinfo = result.prefix().str();
        _authority_host = result.suffix().str();
        if(_authority_host.size() == 0) return false;
        if( std::regex_search(_authority_host, result, std::regex("[@]") ) ) return false;
    } else {
        _authority_host = _authority;
    }

    if(!_parseHost()) return false;

    if(_authority_userinfo.size() != 0)
        return _parseUserinfo();
    return true;
}

bool AbsoluteURLParser::_parseUserinfo()
{
    std::smatch result;
    if ( std::regex_search(_authority_userinfo, result, std::regex("[:]") ) ) {
        _authority_userinfo_login = result.prefix().str();
        _authority_userinfo_password = result.suffix().str();
        if(_authority_userinfo_login.size() == 0) return false;
        if( std::regex_search(_authority_userinfo_password, result, std::regex("[:]")) ) return false;
    } else {
        _authority_userinfo_login = _authority_userinfo;
    }
    return true;
}

bool AbsoluteURLParser::_parseHost()
{
    std::smatch result;
    std::string lostPart;
    if ( std::regex_search(_authority_host, result, std::regex("[:]") ) ) {
        _authority_host_hostname = result.prefix().str();
        lostPart = result.suffix().str();
        if(_authority_host_hostname.size() == 0) return false;
        if( !std::regex_search(lostPart, result, std::regex("[[:digit:]]+") ) ) return false;
        if(result.prefix().str().size() != 0 || result.suffix().str().size() != 0) return false;
        _authority_host_port = std::stoi(result[0].str());
    } else {
        _authority_host_hostname = _authority_host;
    }
    return true;
}

bool AbsoluteURLParser::_parseQuery()
{
    std::smatch result;
    std::string next_pair;
    std::string lostPart(_query);

    while ( std::regex_search(lostPart, result, std::regex("[&]") ) ) {
        next_pair = result.prefix().str();
        lostPart = result.suffix().str();
        if(!_parseNextPair(next_pair)) return false;
    }
    if(!_parseNextPair(lostPart)) return false;
    return true;
}

bool AbsoluteURLParser::_parseNextPair(const std::string &pair)
{
    if(!std::regex_match(pair, std::regex("[[:w:]]+=[\\w$]+")))
        return false;

    std::smatch result;
    std::regex_search(pair, result, std::regex("=") );

    if(_query_map.count(result.prefix().str()) > 0 )
        return false;
    _query_map[result.prefix().str()] = result.suffix().str();

    return true;
}