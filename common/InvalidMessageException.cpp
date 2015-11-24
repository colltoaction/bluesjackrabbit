#include "InvalidMessageException.h"

InvalidMessageException::InvalidMessageException(const std::string& what_arg)
    : std::logic_error(what_arg) {
}
