#ifndef MODEL_EXEPTIONS_H
#define MODEL_EXEPTIONS_H

#include <exception>
#include <string>

namespace model {

class EBadOperation : public std::exception
{
public:
    explicit EBadOperation(const std::string &msg) : msg_(msg){}
    const char * what() const _GLIBCXX_USE_NOEXCEPT override
    {
        return msg_.c_str();
    }

private:
    std::string msg_;
};

} //namespace model

#endif // MODEL_EXEPTIONS_H
