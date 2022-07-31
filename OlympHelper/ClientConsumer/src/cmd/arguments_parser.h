#ifndef __arguments_parser_h_
#define __arguments_parser_h_

#include <stdlib.h>
#include <vector>
#include <string>

class cmd_arguments_parser {
  private:
    std::vector <std::string> tokens;

  public:
   cmd_arguments_parser () {
       for (int i=1; i < __argc; ++i)
           this->tokens.push_back(std::string(__argv[i]));
   }

    const std::string &GetCmdOption(const std::string &option) const {
      std::vector<std::string>::const_iterator itr =
        std::find(this->tokens.begin(), this->tokens.end(), option);

      if (itr != this->tokens.end() && ++itr != this->tokens.end()){
        return *itr;
      }

      static const std::string empty_string("");
      return empty_string;
   }

   bool CmdOptionExists(const std::string &option) const {
     return
       std::find(this->tokens.begin(), this->tokens.end(), option) != this->tokens.end();
   }
};

#endif // !__arguments_parser_h_
