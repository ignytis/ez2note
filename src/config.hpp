#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <map>
#include <string>

using namespace std;

namespace Ez2note
{

class Config
{
public:
    Config();
    bool getBool(const string &key);

private:
    map<string, string> kv;
};

}

#endif // CONFIG_HPP
