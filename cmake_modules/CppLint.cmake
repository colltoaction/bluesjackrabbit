# Copyright (C) 2013 Daniel Scharrer
#
# This software is provided 'as-is', without any express or implied
# warranty.  In no event will the author(s) be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.


# Copyright (C) 2014 Greg Horn
# In order to comply with the above copyright, I am noting that I took
# Daniel's script and hacked it a bit, mostly changing paths and filters

find_package(PythonInterp)

set(STYLE_FILTER)

# Select filters
set(STYLE_FILTER ${STYLE_FILTER}-,)
set(STYLE_FILTER ${STYLE_FILTER}+build/class,)
set(STYLE_FILTER ${STYLE_FILTER}+build/deprecated,)
set(STYLE_FILTER ${STYLE_FILTER}+build/include_what_you_use,)
set(STYLE_FILTER ${STYLE_FILTER}+build/namespaces,)
set(STYLE_FILTER ${STYLE_FILTER}+build/printf_format,)
set(STYLE_FILTER ${STYLE_FILTER}+readability/braces,)
set(STYLE_FILTER ${STYLE_FILTER}+readability/check,)
set(STYLE_FILTER ${STYLE_FILTER}+readability/fn_size,)
set(STYLE_FILTER ${STYLE_FILTER}+readability/function,)
set(STYLE_FILTER ${STYLE_FILTER}+readability/multiline_comment,)
set(STYLE_FILTER ${STYLE_FILTER}+readability/multiline_string,)
set(STYLE_FILTER ${STYLE_FILTER}+readability/utf8,)
set(STYLE_FILTER ${STYLE_FILTER}+runtime/arrays,)
set(STYLE_FILTER ${STYLE_FILTER}+runtime/casting,)
set(STYLE_FILTER ${STYLE_FILTER}+runtime/explicit,)
set(STYLE_FILTER ${STYLE_FILTER}+runtime/init,)
set(STYLE_FILTER ${STYLE_FILTER}+runtime/invalid_increment,)
set(STYLE_FILTER ${STYLE_FILTER}+runtime/memset,)
set(STYLE_FILTER ${STYLE_FILTER}+runtime/operator,)
set(STYLE_FILTER ${STYLE_FILTER}+runtime/printf,)
set(STYLE_FILTER ${STYLE_FILTER}+runtime/printf_format,)
set(STYLE_FILTER ${STYLE_FILTER}+runtime/rtti,)
set(STYLE_FILTER ${STYLE_FILTER}+runtime/string,)
set(STYLE_FILTER ${STYLE_FILTER}+runtime/threadsafe_fn,)
set(STYLE_FILTER ${STYLE_FILTER}+whitespace/blank_line,)
set(STYLE_FILTER ${STYLE_FILTER}+whitespace/empty_loop_body,)
set(STYLE_FILTER ${STYLE_FILTER}+whitespace/ending_newline,)
set(STYLE_FILTER ${STYLE_FILTER}+whitespace/line_length,)
set(STYLE_FILTER ${STYLE_FILTER}+whitespace/newline,)
set(STYLE_FILTER ${STYLE_FILTER}+whitespace/parens,)
set(STYLE_FILTER ${STYLE_FILTER}+whitespace/semicolon,)

# Add a target that runs cpplint.py
#
# Parameters:
# - TARGET_NAME the name of the target to add
# - SOURCES_LIST a complete list of source and include files to check
function(add_style_check_target TARGET_NAME SOURCES_LIST)

    if(NOT PYTHONINTERP_FOUND)
        return()
    endif()

    list(REMOVE_DUPLICATES SOURCES_LIST)
    list(SORT SOURCES_LIST)

    add_custom_target(${TARGET_NAME}
            COMMAND "${CMAKE_COMMAND}"
            -E chdir "${CMAKE_CURRENT_SOURCE_DIR}"
            "${PYTHON_EXECUTABLE}"
            "${CMAKE_SOURCE_DIR}/misc/cpplint.py"
            "--filter=${STYLE_FILTER}"
            "--counting=detailed"
            "--extensions=cpp,h"
            "--linelength=120"
            ${SOURCES_LIST}
            DEPENDS ${SOURCES_LIST}
            COMMENT "Linting ${TARGET_NAME}"
            VERBATIM)

endfunction()
