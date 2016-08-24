#ifndef AI_EXEPTIONS_H
#define AI_EXEPTIONS_H
#include <exception>
#include <string>

namespace ai {
class EWrongParameter : public std::exception
{
public:
    explicit EWrongParameter(const std::string &msg) : msg_(msg){}
    const char * what() const _GLIBCXX_USE_NOEXCEPT override
    {
        return msg_.c_str();
    }

private:
    std::string msg_;
};

} //namespace ai
#endif // AI_EXEPTIONS_H
