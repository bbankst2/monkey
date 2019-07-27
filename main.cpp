#include <iostream>
#include <assert.h>
#include <string.h>
#include <vector>
#include <fstream>
#include "./header/lexer.h"
#include "./header/parser.h"
#include "./header/evaluator.h"

// from https://stackoverflow.com/a/1195690/5163915
std::string readFile2(const std::string &fileName) {
    std::ifstream ifs(fileName.c_str(), std::ios::in | std::ios::binary | std::ios::ate);

    std::ifstream::pos_type fileSize = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    std::vector<char> bytes(fileSize);
    ifs.read(bytes.data(), fileSize);

    return std::string(bytes.data(), fileSize);
}

int main(int argc, char* argv[]) {
    assert(argc > 1);
    std::string filename(argv[1]);
    std::string input = readFile2(filename);
    monkey::Lexer l;
    monkey::Parser p;
    monkey::Environment* env = new monkey::Environment();
    l.New(input);
    p.New(l);
    monkey::Program* program = p.ParseProgram();
    if (p.Errors().size()) {
        for (auto error : p.Errors()) {
            std::cout << error << std::endl;
        }
    }
    monkey::Object* o = monkey::Eval(program, env);
    std::cout << "type: " << o->Type() << std::endl;
    std::cout << o->Inspect() << std::endl;
}