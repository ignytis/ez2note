#include "config.hpp"

#include <sys/stat.h>
#include <wx/debug.h>
#include <wx/stdpaths.h>

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

using namespace std;
using namespace Ez2note;

string getAppHomeDir() {
    string appHomeDir;
    char* cAppHomeDir;
    cAppHomeDir = getenv("EZ2NOTE_HOME");
    if (cAppHomeDir) {
        appHomeDir = string(cAppHomeDir);
    } else {
        appHomeDir = wxStandardPaths::wxStandardPaths::Get().GetUserDataDir().ToStdString();
    }
    return appHomeDir;
}

string jsonBoolToString(json b) { return !b.is_null() && b ? CONFIG_VALUE_BOOL_TRUE : CONFIG_VALUE_BOOL_FALSE; }

/**
 * Returns default KV map for config
 */
map<string, string> getDefaultKv() {
    map<string, string> kv = {
        {CONFIG_KEY_EDITOR_SHOW_LINE_NUMBERS, CONFIG_VALUE_BOOL_FALSE},
        {CONFIG_KEY_EDITOR_WORD_WRAP, CONFIG_VALUE_BOOL_FALSE},
    };
    return kv;
}

Config::Config() : kv(getDefaultKv()) {
    string configFilePath = getAppHomeDir() + "/config.json";

    struct stat fileInfo;
    json configJson = json::object();
    if (stat(configFilePath.c_str(), &fileInfo) == 0) {
        ifstream configFile(configFilePath);
        configFile >> configJson;
        configFile.close();
    }

    kv[CONFIG_KEY_EDITOR_SHOW_LINE_NUMBERS] = jsonBoolToString(configJson[CONFIG_KEY_EDITOR_SHOW_LINE_NUMBERS]);
    kv[CONFIG_KEY_EDITOR_WORD_WRAP] = jsonBoolToString(configJson[CONFIG_KEY_EDITOR_WORD_WRAP]);
}

bool Config::getBool(const string& key) {
    if (kv.find(key) == kv.end()) {
        return false;
    }
    string val = kv.at(key);
    transform(val.begin(), val.end(), val.begin(), ::tolower);
    return val == CONFIG_VALUE_BOOL_TRUE;
}
