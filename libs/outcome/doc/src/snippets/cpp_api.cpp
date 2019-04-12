/* Example of Outcome used with C APIs
(C) 2017-2019 Niall Douglas <http://www.nedproductions.biz/> (149 commits)


Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#include <cstring>  // for memcpy
#include <string>

#include "../../../include/boost/outcome/experimental/status-code/system_code_from_exception.hpp"
#include "../../../include/boost/outcome/experimental/status_result.hpp"

//! [function]
namespace outcome_e = BOOST_OUTCOME_V2_NAMESPACE::experimental;

// Fill the supplied buffer with the integer v converted to a string,
// returning length of string minus null terminator
outcome_e::status_result<size_t> to_string(char *buffer, size_t bufferlen, int v) noexcept
{
  try
  {
    // Could throw an exception!
    std::string temp(std::to_string(v));

    // Will this string exceed the supplied buffer?
    if(temp.size() + 1 > bufferlen)
      return outcome_e::errc::no_buffer_space;

    // Copy the string into the supplied buffer, and return length of string
    memcpy(buffer, temp.data(), temp.size() + 1);
    return temp.size();
  }
  catch(...)
  {
    // This is the <system_error2> analogue of Standard Outcome's
    // error_from_exception() utility function. It consumes an exception
    // ptr (defaulted to current exception), and tries to match it to a
    // standard C++ library exception type, returning a system_code
    // with an appropriate code domain (generic_code, posix_code,
    // win32_code).
    //
    // Note that using this function requires including
    // <boost/outcome/experimental/status-code/system_code_from_exception.hpp>
    // It is NOT included by Experimental Outcome by default.
    return outcome_e::system_code_from_exception();
  }
}
//! [function]

int main()
{
  return 0;
}
