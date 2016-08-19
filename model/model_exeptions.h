#ifndef MODEL_EXEPTIONS_H
#define MODEL_EXEPTIONS_H

#include <exception>
#include <QString>
namespace model {

class EBadOperation : public std::exception
{
public:
    explicit EBadOperation(const QString &msg) : msg_(msg){}
    const char * what() {
        return msg_.toStdString().c_str();
    }

private:
    QString msg_;
};

} //namespace model

#endif // MODEL_EXEPTIONS_H
