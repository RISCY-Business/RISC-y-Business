#include "bits/stdc++.h"
#include "iostream"
#include "sstream"
#include "string"
#include <map>
#include <vector>
#include "limits"
#include <stdexcept>
//------------------------------------------INSTRUCTION-MAP------------------------------------------//
typedef enum { R_TYPE, I_TYPE, S_TYPE, B_TYPE, U_TYPE, J_TYPE } InstructionType;

struct InstructionEncoding {
  InstructionType type;
  bool opcode[7];
  bool funct3[3];
  bool funct7[7];
};

std::map<std::string, InstructionEncoding> instruction_map = {
    // R-type
    {"add", {R_TYPE, {0, 1, 1, 0, 0, 1, 1}, {0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}}},
    {"sub", {R_TYPE, {0, 1, 1, 0, 0, 1, 1}, {0, 0, 0}, {0, 1, 0, 0, 0, 0, 0}}},
    {"sll", {R_TYPE, {0, 1, 1, 0, 0, 1, 1}, {0, 0, 1}, {0, 0, 0, 0, 0, 0, 0}}},
    {"slt", {R_TYPE, {0, 1, 1, 0, 0, 1, 1}, {0, 1, 0}, {0, 0, 0, 0, 0, 0, 0}}},
    {"sltu", {R_TYPE, {0, 1, 1, 0, 0, 1, 1}, {0, 1, 1}, {0, 0, 0, 0, 0, 0, 0}}},
    {"xor", {R_TYPE, {0, 1, 1, 0, 0, 1, 1}, {1, 0, 0}, {0, 0, 0, 0, 0, 0, 0}}},
    {"srl", {R_TYPE, {0, 1, 1, 0, 0, 1, 1}, {1, 0, 1}, {0, 0, 0, 0, 0, 0, 0}}},
    {"or", {R_TYPE, {0, 1, 1, 0, 0, 1, 1}, {1, 1, 0}, {0, 0, 0, 0, 0, 0, 0}}},
    {"and", {R_TYPE, {0, 1, 1, 0, 0, 1, 1}, {1, 1, 1}, {0, 0, 0, 0, 0, 0, 0}}},
    // I-type
    {"jalr", {I_TYPE, {1, 1, 0, 0, 1, 1, 1}, {0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}}},
    {"lw", {I_TYPE, {0, 0, 0, 0, 0, 1, 1}, {0, 1, 0}, {0, 0, 0, 0, 0, 0, 0}}},
    {"addi", {I_TYPE, {0, 0, 1, 0, 0, 1, 1}, {0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}}},
    {"sltiu",
     {I_TYPE, {0, 0, 1, 0, 0, 1, 1}, {0, 1, 1}, {0, 0, 0, 0, 0, 0, 0}}},
    // S-type
    {"sw", {S_TYPE, {0, 1, 0, 0, 0, 1, 1}, {0, 1, 0}, {0, 0, 0, 0, 0, 0, 0}}},
    // B-type
    {"beq", {B_TYPE, {1, 1, 0, 0, 0, 1, 1}, {0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}}},
    {"bne", {B_TYPE, {1, 1, 0, 0, 0, 1, 1}, {0, 0, 1}, {0, 0, 0, 0, 0, 0, 0}}},
    {"blt", {B_TYPE, {1, 1, 0, 0, 0, 1, 1}, {1, 0, 0}, {0, 0, 0, 0, 0, 0, 0}}},
    {"bge", {B_TYPE, {1, 1, 0, 0, 0, 1, 1}, {1, 0, 1}, {0, 0, 0, 0, 0, 0, 0}}},
    {"bltu", {B_TYPE, {1, 1, 0, 0, 0, 1, 1}, {1, 1, 0}, {0, 0, 0, 0, 0, 0, 0}}},
    {"bgeu", {B_TYPE, {1, 1, 0, 0, 0, 1, 1}, {1, 1, 1}, {0, 0, 0, 0, 0, 0, 0}}},
    // U-type
    {"lui", {U_TYPE, {0, 1, 1, 0, 1, 1, 1}, {0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}}},
    {"auipc",
     {U_TYPE, {0, 0, 1, 0, 1, 1, 1}, {0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}}},
    // J-type
    {"jal", {J_TYPE, {1, 1, 0, 1, 1, 1, 1}, {0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}}},
};
//--------------------------------------------------------------------------------------------------//

//------------------------------------------REGISTER-MAP------------------------------------------//

struct RegisterEncoding {
  std::string name;
  bool address[5];
  char saver_status;
  // 0 -Caller
  // 1 -Callee
  // 2 -None
};

std::map<std::string, RegisterEncoding> register_map = {

    {"zero", {"x0", {0, 0, 0, 0, 0}, 2}}, {"ra", {"x1", {0, 0, 0, 0, 1}, 0}},
    {"sp", {"x2", {0, 0, 0, 1, 0}, 1}},   {"gp", {"x3", {0, 0, 0, 1, 1}, 2}},
    {"tp", {"x4", {0, 0, 1, 0, 0}, 2}},   {"t0", {"x5", {0, 0, 1, 0, 1}, 0}},
    {"t1", {"x6", {0, 0, 1, 1, 0}, 0}},   {"t2", {"x7", {0, 0, 1, 1, 1}, 0}},
    {"s0", {"x8", {0, 1, 0, 0, 0}, 1}},   {"fp", {"x8", {0, 1, 0, 0, 0}, 1}},
    {"s1", {"x9", {0, 1, 0, 0, 1}, 1}},   {"a0", {"x10", {0, 1, 0, 1, 0}, 0}},
    {"a1", {"x11", {0, 1, 0, 1, 1}, 0}},  {"a2", {"x12", {0, 1, 1, 0, 0}, 0}},
    {"a3", {"x13", {0, 1, 1, 0, 1}, 0}},  {"a4", {"x14", {0, 1, 1, 1, 0}, 0}},
    {"a5", {"x15", {0, 1, 1, 1, 1}, 0}},  {"a6", {"x16", {1, 0, 0, 0, 0}, 0}},
    {"a7", {"x17", {1, 0, 0, 0, 1}, 0}},  {"s2", {"x18", {1, 0, 0, 1, 0}, 0}},
    {"s3", {"x19", {1, 0, 0, 1, 1}, 0}},  {"s4", {"x20", {1, 0, 1, 0, 0}, 0}},
    {"s5", {"x21", {1, 0, 1, 0, 1}, 0}},  {"s6", {"x22", {1, 0, 1, 1, 0}, 0}},
    {"s7", {"x23", {1, 0, 1, 1, 1}, 0}},  {"s8", {"x24", {1, 1, 0, 0, 0}, 0}},
    {"s9", {"x25", {1, 1, 0, 0, 1}, 0}},  {"s10", {"x26", {1, 1, 0, 1, 0}, 0}},
    {"s11", {"x27", {1, 1, 0, 1, 1}, 0}}, {"t3", {"x28", {1, 1, 1, 0, 0}, 0}},
    {"t4", {"x29", {1, 1, 1, 0, 1}, 0}},  {"t5", {"x30", {1, 1, 1, 1, 0}, 0}},
    {"t6", {"x31", {1, 1, 1, 1, 1}, 0}},
};

//--------------------------------------------------------------------------------------------------//
//------------------------------------------IMM------------------------------------------//

std::vector<bool> int_to_signed_bin_array(int a, int n) {
    // Check if the number is within the range
    int max_positive = (1 << (n - 1)) - 1;
    int min_negative = -(1 << (n - 1));

    if (a > max_positive || a < min_negative) {
        // Handle the error case
        throw std::out_of_range("Number out of range for the given bit size");
    }

    std::vector<bool> bin_array(n);
    uint32_t value = (a < 0) ? static_cast<uint32_t>(-a) : static_cast<uint32_t>(a);

    // Handle negative numbers using two's complement
    if (a < 0) {
        value = ~value + 1;
    }

    for (int i = 0; i < n; i++) {
        bin_array[i] = (value & (1 << (n - 1 - i))) ? 1 : 0;
    }

    return bin_array;
}

std::vector<bool> slice_bool_array(const std::vector<bool> &bool_array,
                                   int start_index, int end_index) {

  // Create a new vector to hold the sliced elements
  std::vector<bool> sliced_array;

  // Iterate over the desired range and copy elements to the new vector
  for (int i = start_index; i < end_index + 1; ++i) {
    sliced_array.push_back(bool_array[i]);
  }

  return sliced_array;
}
//----------------------------------------------------------------------------------------------------------//
//-----------------------------------------TOKENIZER------------------------------------------//
std::vector<std::string> tokenize(const std::string& line) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;

    // Tokenize based on spaces and colons
    while (std::getline(ss, token, ' ')) {
        // Remove leading and trailing whitespace
        token.erase(0, token.find_first_not_of(" \t\r\n"));
        token.erase(token.find_last_not_of(" \t\r\n") + 1);

        // Skip comments and blank lines
        if (token.empty() || token[0] == '#') {
            continue;
        }

        // Check if the token is a label
        if (token.back() == ':') {
            if (token.length() == 1) {
                std::cerr << "Error: Invalid label" << std::endl;
                continue;
            }
            tokens.push_back(token.substr(0, token.length() - 1));  // Add the label without the colon
            continue;  // Skip to the next token
        }

        // Tokenize based on commas
        std::stringstream subss(token);
        std::string subToken;
        std::vector<std::vector<std::vector<std::string>>> subTokens;

        while (std::getline(subss, subToken, ',')) {
            std::vector<std::vector<std::string>> subSubTokens;
            std::stringstream subSubss(subToken);
            std::string subSubToken;

            // Tokenize based on opening parentheses
            while (std::getline(subSubss, subSubToken, '(')) {
                std::vector<std::string> subSubSubTokens;
                std::stringstream subSubSubss(subSubToken);
                std::string subSubSubToken;

                // Tokenize based on closing parentheses
                while (std::getline(subSubSubss, subSubSubToken, ')')) {
                    subSubSubTokens.push_back(subSubSubToken);
                }
                subSubTokens.push_back(subSubSubTokens);
            }
            subTokens.push_back(subSubTokens);
        }

        // Flatten the nested vector structure
        for (const auto& outerToken : subTokens) {
            for (const auto& innerToken : outerToken) {
                for (const auto& subInnerToken : innerToken) {
                    tokens.push_back(subInnerToken);
                }
            }
        }
    }

    return tokens;
}


//----------------------------------------------------------------------------------------------------------//
//------------------------------------------DECODER------------------------------------------//

std::vector<bool> decode(std::vector<std::string> tokens) {

  std::vector<bool> decoded(32);
  static const std::regex integer_regex("^-?\\d+$");

    if (tokens.empty()) {
        std::cerr << "Error: Empty instruction " << std::endl;
        return decoded;
    }
    if (instruction_map.find(tokens[0]) == instruction_map.end()) {
        std::cerr << "Error: Unknown instruction '" << tokens[0] << std::endl;
        return decoded;
    }
    InstructionType type = instruction_map[tokens[0]].type;

  if (type == R_TYPE) {

          if (tokens.size() != 4) {
              std::cerr << "Error: Invalid number of operands for R-type instruction '" << tokens[0] << std::endl;
              exit(0);
          }

      if (register_map.find(tokens[1]) == register_map.end() ||
          register_map.find(tokens[2]) == register_map.end() ||
          register_map.find(tokens[3]) == register_map.end()) {
          std::cerr << "Error: Invalid register operand for instruction '" << tokens[0]  << std::endl;
          exit(0);
      }


    // funct7
    for (int i = 0; i < 7; ++i) {
      decoded[i] = instruction_map[tokens[0]].funct7[i];
    }
    // rs2
    for (int i = 0; i < 5; ++i) {
      decoded[i + 7] = register_map[tokens[3]].address[i];
    }
    // rs1
    for (int i = 0; i < 5; ++i) {
      decoded[i + 12] = register_map[tokens[2]].address[i];
    }
    // funct3
    for (int i = 0; i < 3; ++i) {
      decoded[i + 17] = instruction_map[tokens[0]].funct3[i];
    }
    // rd
    for (int i = 0; i < 5; ++i) {
      decoded[i + 20] = register_map[tokens[1]].address[i];
    }
    // opcode
    for (int i = 0; i < 7; ++i) {
      decoded[i + 25] = instruction_map[tokens[0]].opcode[i];
    }

  } else if (type == I_TYPE) {

      if (tokens.size() != 4) {
          std::cerr << "Error: Invalid number of operands for I-type instruction '" << tokens[0] << std::endl;
          exit(0);
      }

      if (tokens[0]=="lw"){
          if (register_map.find(tokens[1]) == register_map.end() ||
              register_map.find(tokens[3]) == register_map.end()) {
              std::cerr << "Error: Invalid register operand for instruction '" << tokens[0]  << std::endl;
              exit(0);
          }}

     if (tokens[0]!="lw"){
        if (register_map.find(tokens[1]) == register_map.end() ||
            register_map.find(tokens[2]) == register_map.end()) {
            std::cerr << "Error: Invalid register operand for instruction '" << tokens[0]  << std::endl;
            exit(0);
        }}

     if(tokens[0]=="lw"){
      if (!std::regex_match(tokens[2], integer_regex)) {
          std::cerr << "Error: Invalid immediate value '" << tokens[3] << "' for instruction '" << tokens[0] << std::endl;
          exit(0);
      }}


     if(tokens[0]!="lw"){
      if (!std::regex_match(tokens[3], integer_regex)) {
          std::cerr << "Error: Invalid immediate value '" << tokens[3] << "' for instruction '" << tokens[0] << std::endl;
          exit(0);
      }}



    if (tokens[0] == "lw") {
      // imm
      std::vector<bool> imm = int_to_signed_bin_array(stoi(tokens[2]), 12);
      for (int i = 0; i < 12; ++i) {
        decoded[i] = imm[i];
      }
      // rs1
      for (int i = 0; i < 5; ++i) {
        decoded[i + 12] = register_map[tokens[3]].address[i];
      }
      // funct3
      for (int i = 0; i < 3; ++i) {
        decoded[i + 17] = instruction_map[tokens[0]].funct3[i];
      }
      // rd
      for (int i = 0; i < 5; ++i) {
        decoded[i + 20] = register_map[tokens[1]].address[i];
      }
      // opcode
      for (int i = 0; i < 7; ++i) {
        decoded[i + 25] = instruction_map[tokens[0]].opcode[i];
      }
    } else {
      // imm
      std::vector<bool> imm = int_to_signed_bin_array(stoi(tokens[3]), 12);
      for (int i = 0; i < 12; ++i) {
        decoded[i] = imm[i];
      }
      // rs1
      for (int i = 0; i < 5; ++i) {
        decoded[i + 12] = register_map[tokens[2]].address[i];
      }
      // funct3
      for (int i = 0; i < 3; ++i) {
        decoded[i + 17] = instruction_map[tokens[0]].funct3[i];
      }
      // rd
      for (int i = 0; i < 5; ++i) {
        decoded[i + 20] = register_map[tokens[1]].address[i];
      }
      // opcode
      for (int i = 0; i < 7; ++i) {
        decoded[i + 25] = instruction_map[tokens[0]].opcode[i];
      }
    }

  } else if (type == S_TYPE) {

      if (tokens.size() != 4) {
          std::cerr << "Error: Invalid number of operands for I-type instruction '" << tokens[0] << std::endl;
            exit(0);
      }

      if (register_map.find(tokens[1]) == register_map.end() ||
          register_map.find(tokens[3]) == register_map.end()) {
          std::cerr << "Error: Invalid register operand for instruction '" << tokens[0] << std::endl;
         exit(0);
      }

      if (!std::regex_match(tokens[2], integer_regex)) {
          std::cerr << "Error: Invalid immediate value '" << tokens[3] << "' for instruction '" << tokens[0]  << std::endl;
          exit(0);
      }


    // imm[11:5]
    std::vector<bool> imm_11_5 =
        slice_bool_array(int_to_signed_bin_array(stoi(tokens[2]), 12), 0, 6);
    for (int i = 0; i < 7; ++i) {
      decoded[i] = imm_11_5[i];
    }
    // rs2
    for (int i = 0; i < 5; ++i) {
      decoded[i + 7] = register_map[tokens[1]].address[i];
    }
    // rs1
    for (int i = 0; i < 5; ++i) {
      decoded[i + 12] = register_map[tokens[3]].address[i];
    }
    // funct3
    for (int i = 0; i < 3; ++i) {
      decoded[i + 17] = instruction_map[tokens[0]].funct3[i];
    }
    // imm[4:0]
    std::vector<bool> imm_4_0 =
        slice_bool_array(int_to_signed_bin_array(stoi(tokens[2]), 12), 7, 11);
    for (int i = 0; i < 5; ++i) {
      decoded[i + 20] = imm_4_0[i];
    }
    // opcode
    for (int i = 0; i < 7; ++i) {
      decoded[i + 25] = instruction_map[tokens[0]].opcode[i];
    }

  } else if (type == B_TYPE) {

      if (tokens.size() != 4) {
          std::cerr << "Error: Invalid number of operands for B-type instruction '" << tokens[0] <<  std::endl;
            exit(0);
      }

      if (register_map.find(tokens[1]) == register_map.end() ||
          register_map.find(tokens[2]) == register_map.end()) {
          std::cerr << "Error: Invalid register operand for instruction '" << tokens[0]  << std::endl;
            exit(0);
      }

      if (!std::regex_match(tokens[3], integer_regex)) {
          std::cerr << "Error: Invalid immediate value '" << tokens[2] << "' for instruction '" << tokens[0]<< std::endl;
            exit(0);
      }


      // imm[12]
    std::vector<bool> imm_12 =
        slice_bool_array(int_to_signed_bin_array(stoi(tokens[3]), 16), 3, 3);
    for (int i = 0; i < 1; ++i) {
      decoded[i] = imm_12[i];
    }
    // imm[10:5]
    std::vector<bool> imm_10_5 =
        slice_bool_array(int_to_signed_bin_array(stoi(tokens[3]), 16), 5, 10);
    for (int i = 0; i < 6; ++i) {
      decoded[i + 1] = imm_10_5[i];
    }
    // rs2
    for (int i = 0; i < 5; ++i) {
      decoded[i + 7] = register_map[tokens[2]].address[i];
    }
    // rs1
    for (int i = 0; i < 5; ++i) {
      decoded[i + 12] = register_map[tokens[1]].address[i];
    }
    // funct3
    for (int i = 0; i < 3; ++i) {
      decoded[i + 17] = instruction_map[tokens[0]].funct3[i];
    }
    // imm[4:1]
    std::vector<bool> imm_4_1 =
        slice_bool_array(int_to_signed_bin_array(stoi(tokens[3]), 16), 11, 14);
    for (int i = 0; i < imm_4_1.size(); ++i) {
      decoded[i + 20] = imm_4_1[i];
    }
    // imm[11]
    std::vector<bool> imm_11 =
        slice_bool_array(int_to_signed_bin_array(stoi(tokens[3]), 16), 4, 4);
    for (int i = 0; i < 1; ++i) {
      decoded[i + 24] = imm_11[i];
    }
    // opcode
    for (int i = 0; i < 7; ++i) {
      decoded[i + 25] = instruction_map[tokens[0]].opcode[i];
    }

  } else if (type == U_TYPE) {

      if (tokens.size() != 3) {
          std::cerr << "Error: Invalid number of operands for U-type instruction '" << tokens[0] << std::endl;
            exit(0);
      }

        if (register_map.find(tokens[1]) == register_map.end()) {
            std::cerr << "Error: Invalid register operand for instruction '" << tokens[0]  << std::endl;
                exit(0);
        }

        if (!std::regex_match(tokens[2], integer_regex)) {
            std::cerr << "Error: Invalid immediate value '" << tokens[2] << "' for instruction '" << tokens[0] << std::endl;
            exit(0);
        }

    // imm[31:12]
    std::vector<bool> imm_31_12 =
        slice_bool_array(int_to_signed_bin_array(stoi(tokens[2]), 32), 0, 19);
    for (int i = 0; i < 20; ++i) {
      decoded[i] = imm_31_12[i];
    }
    // rd
    for (int i = 0; i < 5; ++i) {
      decoded[i + 20] = register_map[tokens[1]].address[i];
    }
    // opcode
    for (int i = 0; i < 7; ++i) {
      decoded[i + 25] = instruction_map[tokens[0]].opcode[i];
    }

  } else if (type == J_TYPE) {
      if (tokens.size() != 3) {
          std::cerr << "Error: Invalid number of operands for J-type instruction '" << tokens[0] << std::endl;
            exit(0);
      }

        if (register_map.find(tokens[1]) == register_map.end()) {
            std::cerr << "Error: Invalid register operand for instruction '" << tokens[0]  << std::endl;
                exit(0);
        }

      if (!std::regex_match(tokens[2], integer_regex)) {
          std::cerr << "Error: Invalid immediate value '" << tokens[2] << "' for instruction '" << tokens[0]  << std::endl;
            exit(0);
      }



      // imm[20]
    std::vector<bool> imm_20 =
        slice_bool_array(int_to_signed_bin_array(stoi(tokens[2]), 21), 0, 0);
    for (int i = 0; i < 1; ++i) {
      decoded[i] = imm_20[i];
    }
    // imm[10:1]
    std::vector<bool> imm_10_1 =
        slice_bool_array(int_to_signed_bin_array(stoi(tokens[2]), 21), 10, 19);
    for (int i = 0; i < 10; ++i) {
      decoded[i + 1] = imm_10_1[i];
    }
    // imm[11]
    std::vector<bool> imm_11 =
        slice_bool_array(int_to_signed_bin_array(stoi(tokens[2]), 21), 9, 9);
    for (int i = 0; i < 1; ++i) {
      decoded[i + 11] = imm_11[i];
    }
    // imm[19:12]
    std::vector<bool> imm_19_12 =
        slice_bool_array(int_to_signed_bin_array(stoi(tokens[2]), 21), 1, 8);
    for (int i = 0; i < 8; ++i) {
      decoded[i + 12] = imm_19_12[i];
    }
    // rd
    for (int i = 0; i < 5; ++i) {
      decoded[i + 20] = register_map[tokens[1]].address[i];
    }
    // opcode
    for (int i = 0; i < 7; ++i) {
      decoded[i + 25] = instruction_map[tokens[0]].opcode[i];
    }
  } else{
      std::cout << "Invalid instruction type" << std::endl;
      exit(0);
  }

  return decoded;
}
//----------------------------------------------------------------------------------------------------------//

//-------------------------------------------FILE
// READER-------------------------------------------//
void read_file(const std::string &file_name) {
  std::ifstream file(file_name);
  std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file '" << file_name << "'" << std::endl;
        return;
    }

  while (std::getline(file, line)) {
    std::vector<std::string> tokens = tokenize(line);
    std::vector<bool> decoded = decode(tokens);
    for (int i = 0; i < 32; ++i) {
      std::cout << decoded[i];
    }
    std::cout << std::endl;
  }
  file.close();
}

//-------------------------------------------------MAIN-------------------------------------------------//

int main() {
  read_file("text.txt");
  return 0;
}
