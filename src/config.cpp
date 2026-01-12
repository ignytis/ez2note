#include "config.hpp"

#include <sys/stat.h>
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
        wxString wxAppHomeDir =
            wxStandardPaths::wxStandardPaths::Get().GetUserDataDir() +
            "/.ez2note";
        appHomeDir = wxAppHomeDir.ToStdString();
    }
    return appHomeDir;
}

string jsonBoolToString(json b) { return !b.is_null() && b ? "true" : "false"; }

/**
 * Returns default KV map for config
 */
map<string, string> getDefaultKv() {
    map<string, string> kv = {
        {"showLineNumbers", "false"},
        {"wordWrap", "false"},
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

    kv["showLineNumbers"] = jsonBoolToString(configJson["showLineNumbers"]);
    kv["wordWrap"] = jsonBoolToString(configJson["wordWrap"]);
}

bool Config::getBool(const string& key) {
    if (kv.find(key) == kv.end()) {
        return false;
    }
    string val = kv.at(key);
    transform(val.begin(), val.end(), val.begin(), ::tolower);
    return val == "true";
}
