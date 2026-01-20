#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <map>
#include <string>

#define CONFIG_KEY_EDITOR_SHOW_LINE_NUMBERS "editor.showLineNumbers"
#define CONFIG_KEY_EDITOR_WORD_WRAP "editor.wordWrap"

#define CONFIG_VALUE_BOOL_TRUE "true"
#define CONFIG_VALUE_BOOL_FALSE "false"

using namespace std;

namespace Ez2note {

class Config {
   public:
    Config();
    bool getBool(const string& key);

   private:
    map<string, string> kv;
};

}  // namespace Ez2note

#endif  // CONFIG_HPP
