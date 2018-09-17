//Settings.h
#ifndef _SETTINGSH
#define _SETTINGSH

#include <fstream>
#include <string>
#include <map>


class Settings {
    std::ifstream file;
    std::map<std::string, std::string> savedKeys;
public:
    Settings(const std::string &filename) {
        file = std::ifstream(filename);

        if (file) {
            std::string key;
            std::string value;
            while (file) {
                std::getline(file, key, '=');
                std::getline(file, value, '\n');
                size_t q1 = value.find_first_of("\"");
                size_t q2 = value.find_last_of("\"");
                if (q1 != std::string::npos && q2 != std::string::npos && q2 > q1) {
                    value = value.substr(q1+1, q2-q1-1);
                    savedKeys[key] = value;
                }
            }
            file.close();
        }
        
        //todo errors
    };

    std::string getKey(std::string key) {
        if (savedKeys.find(key) != savedKeys.end()) return savedKeys[key];
        else return "KEY_NOT_FOUND";
    }

};


#endif
