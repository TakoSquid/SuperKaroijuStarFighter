#include "squid/tools/print.hpp"

namespace squid
{
void printAt(int t_x, int t_y, const std::string &t_text)
{
    printf("\x1b[%d;%dH%s\n", t_y, t_x, t_text.c_str());
}

void print(const std::string &t_text)
{
    printf("%s\n", t_text.c_str());
}
} // namespace squid