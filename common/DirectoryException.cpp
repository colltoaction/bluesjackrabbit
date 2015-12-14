#include "DirectoryException.h"

DirectoryException::DirectoryException(const std::string& what_arg)
    : std::logic_error(what_arg) {
}
