#include <stdexcept>
#include <string>

class NotEqualException : public std::runtime_error
{
public:
   NotEqualException(const std::string & _err): 
      std::runtime_error(_err) 
   {}
};