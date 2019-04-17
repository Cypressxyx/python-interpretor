#include <iostream>
#include <vector>
#include <sys/time.h>
#include <sys/resource.h>

#include "Token.hpp"
#include "Parser.hpp"
#include "Debug.hpp"

#include "./lex/Lexer.hpp"
#include "./statements/Statement.hpp"

long getMemoryUsage() 
{
  struct rusage usage;
  if(0 == getrusage(RUSAGE_SELF, &usage))
    return usage.ru_maxrss; // bytes
  else
    return 0;
}

int main(int argc, char *argv[]) {

    if( argc != 2) {
        std::cout << "usage: " << argv[0] << " nameOfAnInputFile\n";
        exit(1);
    }

    std::ifstream inputStream;

    inputStream.open(argv[1], std::ios::in);
    if( ! inputStream.is_open() ) {
        std::cout << "Unable top open " << argv[1] << ". Terminating...";
        perror("Error when attempting to open the input file.");
        exit(2);
    }




    SymTab symTab;
    Lexer lex = Lexer(inputStream);

    // auto tok = lex.getToken();

    // while ( !tok->eof() ) {
    //   tok->print();
    //   tok = lex.getToken();
    //   std::cout << std::endl;
    // }
    Parser parser(lex);
    // std::unique_ptr<GroupedStatements> stmts =  parser.file_input();
    auto stmts = parser.file_input();

    // stmts->evaluate(symTab);
    // std::cout << "Evaluate Done - Dumping Tree" << std::endl;
//    std::cout << getMemoryUsage() << std::endl;
    stmts->dumpAST("");

    return 0;
}
