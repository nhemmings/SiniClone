#ifndef SCRIPTENGINE_HPP
#define SCRIPTENGINE_HPP


class ScriptEngine
{
public:
    /** Default constructor */
    ScriptEngine() {}
    /** Default destructor */
    virtual ~ScriptEngine() {}

    virtual int loadscript(const char *filepath) = 0;
    virtual double getNumber(int scriptIndex, const char *varName) = 0;
protected:
private:
    /** Copy and Assignment hidden */
    ScriptEngine& operator=(const ScriptEngine& other) { return *this; }
};

#endif // SCRIPTENGINE_HPP
