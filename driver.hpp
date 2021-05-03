
#ifndef __DRIVER_HPP__
#define __DRIVER_HPP__

#include <string>
#include <cstddef>
#include <istream>

#include "parser.hpp"
#include "scanner.hpp"

namespace saltyfish{

class Driver{
public:
   Driver();
   saltyfish::Parser::symbol_type get_next_token();
   int parse();
   int parse(const std::string &filename);
   int parse(std::istream &stream);
   int parseStream(std::istream &stream);
private:
   Scanner *scanner=nullptr;
   Parser *parser=nullptr;
};

}
#endif