#ifndef SERVICES_HPP_
#define SERVICES_HPP_

#include "ScriptEngine.hpp"

class Services
{
private:
    static ScriptEngine* m_script;
public:
    /** Default constructor */
    Services() {}

    static ScriptEngine* getScriptEngine() { return m_script; }
    static void provideScriptEngine(ScriptEngine* script) { m_script = script; }
protected:
};

#endif // SERVICES_HPP_
