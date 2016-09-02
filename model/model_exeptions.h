#ifndef MODEL_EXEPTIONS_H
#define MODEL_EXEPTIONS_H

#include <stdexcept>
#include <string>
#include <qglobal.h>

namespace model {

class EBadOperation : public std::exception
{
public:
    explicit EBadOperation(const std::string &msg) : msg_(msg){}
#if defined(Q_OS_DARWIN)
    const char * what() const  _NOEXCEPT override
#elif defined(Q_OS_LINUX)
    const char * what() const _GLIBCXX_USE_NOEXCEPT override
#elif defined(Q_OS_WIN)
#if defined(__MINGW32__)
    const char * what() const _GLIBCXX_USE_NOEXCEPT override
#else
    const char * what() const _NOEXCEPT override
#endif
#endif
    {
        return msg_.c_str();
    }

private:
    std::string msg_;
};

class EWrongParameter : public std::exception
{
public:
    explicit EWrongParameter(const std::string &msg) : msg_(msg){}
#if defined(Q_OS_DARWIN)
    const char * what() const  _NOEXCEPT override
#elif defined(Q_OS_LINUX)
    const char * what() const _GLIBCXX_USE_NOEXCEPT override
#elif defined(Q_OS_WIN)
#if defined(__MINGW32__)
    const char * what() const _GLIBCXX_USE_NOEXCEPT override
#else
    const char * what() const _NOEXCEPT override
#endif
#endif
    {
        return msg_.c_str();
    }

private:
    std::string msg_;
};

} //namespace model

#endif // MODEL_EXEPTIONS_H
