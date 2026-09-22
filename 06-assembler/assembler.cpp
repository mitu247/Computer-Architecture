#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
using std::string, std::vector;

FILE *log_file, *hex_file;
std::ifstream in_file("in.txt");

void tokenize(const string& str, vector<string>& tokenList) {
    tokenList.clear();
    string curr = "";
    for(int i=0; i<str.length(); i++) {
        if(str[i]==' ' || str[i]==',' || str[i]=='(' || str[i]==')') {
            if(curr.length()) tokenList.push_back(curr);
            curr = "";
        }
        else curr += str[i];
    }
    if(curr.length()) tokenList.push_back(curr);
}

inline uint8_t convert_register(string reg) {
    if(reg == "$zero") return 0;
    if(reg == "$sp") return 6;
    return reg[2] - '0' + 1;
}

uint8_t get_opcode(string op) {
    if(op == "bneq") return 0;  // O
    if(op == "andi") return 1;  // F
    if(op == "j") return 2;     // P
    if(op == "srl") return 3;   // J
    if(op == "lw") return 4;    // L
    if(op == "ori") return 5;   // H
    if(op == "nor") return 6;   // K
    if(op == "or") return 7;    // G
    if(op == "addi") return 8;  // B
    if(op == "subi") return 9;  // D
    if(op == "sub") return 10;  // C
    if(op == "sw") return 11;   // M
    if(op == "add") return 12;  // A
    if(op == "and") return 13;  // E
    if(op == "sll") return 14;  // I
    if(op == "beq") return 15;  // N
    return -1;
}

inline bool is_r_format(string op) {
    return op=="add" || op=="sub" || op=="and" || op=="or" || op=="nor";
}

inline bool is_s_format(string op) {
    return op=="sll" || op=="srl";
}

inline bool is_i_format(string op) {
    return op=="addi" || op=="subi" || op=="andi" || op=="ori" || op=="lw" || op=="sw" || op=="beq" || op=="bneq";
}

inline bool is_memory_op(string op) {
    return op=="lw" || op=="sw";
}

void assemble(string instruction) {
    fprintf(log_file, "%s\n", instruction.c_str());
    uint16_t hexcode = 0;
    vector<string> tokenList;
    tokenize(instruction, tokenList);
    string operation = tokenList[0];
    uint8_t opcode = get_opcode(operation);

    if(is_r_format(operation)) {
        uint8_t src_reg_1 = convert_register(tokenList[2]);
        uint8_t src_reg_2 = convert_register(tokenList[3]);
        uint8_t dest_reg = convert_register(tokenList[1]);
        hexcode = (opcode<<12) | (src_reg_1<<8) | (src_reg_2<<4) | dest_reg;
        fprintf(log_file, "%u %u %u %u\n", opcode, src_reg_1, src_reg_2, dest_reg);
        fprintf(hex_file, "0x%04x", hexcode);
    }

    else if(is_memory_op(operation)) {
        uint8_t src_reg_1 = convert_register(tokenList[3]);
        uint8_t dest_reg = convert_register(tokenList[1]);
        uint8_t immediate = std::stoi(tokenList[2]);
        immediate = immediate & 0x0f;
        hexcode = (opcode<<12) | (src_reg_1<<8) | (dest_reg<<4) | immediate;
        fprintf(log_file, "%u %u %u %u\n", opcode, src_reg_1, dest_reg, immediate);
        fprintf(hex_file, "0x%04x", hexcode);
    }

    else if(is_i_format(operation) || is_s_format(operation)) {
        uint8_t src_reg_1 = convert_register(tokenList[2]);
        uint8_t dest_reg = convert_register(tokenList[1]);
        uint8_t immediate = std::stoi(tokenList[3]);
        immediate = immediate & 0x0f;
        hexcode = (opcode<<12) | (src_reg_1<<8) | (dest_reg<<4) | immediate;
        fprintf(log_file, "%u %u %u %u\n", opcode, src_reg_1, dest_reg, immediate);
        fprintf(hex_file, "0x%04x", hexcode);
    }

    else {
        uint16_t address = std::stoi(tokenList[1]);
        hexcode = (opcode<<12) | (address<<4);
        fprintf(log_file, "%u %u\n", opcode, address);
        fprintf(hex_file, "0x%04x", hexcode);
    }

    // fflush(log_file);
    // fflush(hex_file);
}

int main() {
    log_file = fopen("log.txt", "w");
    hex_file = fopen("hex.txt", "w");
    string input;
    bool flag = false;
    while(std::getline(in_file, input)){
        if(!input.length()) continue;
        if(flag) fprintf(hex_file, ", ");
        assemble(input);
        flag = true;
    }
    fclose(log_file);
    fclose(hex_file);
}