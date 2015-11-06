#ifndef LUASCRIPT_HPP_
#define LUASCRIPT_HPP_

#include "ScriptEngine.hpp"

class LuaScript : public ScriptEngine {
private:
    int numScripts;
public:
    LuaScript() : numScripts(0) {}
    int loadscript(const char *filepath);
    double getNumber(int scriptIndex, const char *varName);
};

#endif // LUASCRIPT_HPP_
