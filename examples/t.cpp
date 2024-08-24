/*
g++ t.cpp -std=c++17 -I../include -O3 -o t -DDEBUG
*/
#include <algorithm>
#include <bitset>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "pgm/pgm_index_dynamic.hpp"

class IOProcessor {
 public:
  void process(std::vector<std::string>& inV, const std::string FileName) {
    std::fstream fileIn;
    fileIn.open(FileName, std::ios::in);
    std::string inStr;
    while (std::getline(fileIn, inStr)) {
      inV.emplace_back(inStr);
    }
    fileIn.close();
  }

  void testLoad(const std::vector<std::string>& InV,
                const std::string FileName) {
    const size_t VSize = InV.size();
    if (VSize == 0) exit(1);
    std::fstream file;
    file.open(FileName, std::ios::out);
    for (size_t i = 0; i < VSize; ++i) {
      file << "id_" << i << ": " << InV[i] << "\n";
    }
    file.close();
  }

  uint64_t stringToBinary64(std::string& str) {
    std::string binaryString;

    // 移除字串中的 '/'
    str.erase(std::remove(str.begin(), str.end(), '/'), str.end());

    // 將字串轉換為二進制表示
    for (char c : str) {
      std::bitset<8> bits(static_cast<unsigned long long>(c));
      binaryString += bits.to_string();
    }

    // 如果不足64位，右邊補0
    if (binaryString.size() < 64) {
      binaryString.append(64 - binaryString.size(), '0');
    }

    // 提取前64個位元並轉換為uint64_t
    std::bitset<64> first64Bits(binaryString);
    return first64Bits.to_ullong();
  }

  void testStr2Uint(const std::vector<uint64_t>& InV,
                    const std::string FileName) {
    const size_t VSize = InV.size();
    if (VSize == 0) exit(1);
    std::fstream file;
    file.open(FileName, std::ios::out);
    for (size_t i = 0; i < VSize; ++i) {
      file << "id_" << i << ": " << static_cast<uint64_t>(InV[i]) << "\n";
    }
    file.close();
  }
};

int main() {
  const std::string FileName = "NDN_Dataset_10K.txt";
  std::vector<std::string> rules;
  std::vector<uint64_t> trainDatas;
  IOProcessor ioprocessor;
  ioprocessor.process(rules, FileName);

#ifdef DEBUG
  ioprocessor.testLoad(rules, "rulesLoad_debug.txt");
#endif

  for (auto& it : rules) {
    uint64_t result = ioprocessor.stringToBinary64(it);
    trainDatas.emplace_back(result);
  }

#ifdef DEBUG
  ioprocessor.testStr2Uint(trainDatas, "str2Uint_debug.txt");
#endif

  std::sort(trainDatas.begin(), trainDatas.end());

#ifdef DEBUG
  ioprocessor.testStr2Uint(trainDatas, "sort_debug.txt");
#endif

  // Construct the PGM-index
  const int epsilon = 2;  // space-time trade-off parameter
  pgm::PGMIndex<uint64_t, epsilon> index(trainDatas);

  // Query the PGM-index
  std::fstream file;
  file.open("result.txt", std::ios::out);
  for (const auto& It : trainDatas) {
    auto range = index.search(It);
    auto lo = trainDatas.begin() + range.lo;
    auto hi = trainDatas.begin() + range.hi;
    file << *(std::lower_bound(lo, hi, It)) << "\n";
    file << range.pos << "\n";
  }
  file.close();

  std::cout << "pgm epsilon_value: " << index.epsilon_value << "\n";
  std::cout << "pgm height: " << index.height() << "\n";
  std::cout << "pgm segments_count: " << index.segments_count() << "\n";
  std::cout << "pgm size_in_bytes: " << index.size_in_bytes() << "\n";

  return 0;
}

/*
    const auto It = 44444444;
    auto range = index.search(It);
    auto lo = trainDatas.begin() + range.lo;
    auto hi = trainDatas.begin() + range.hi;
    std::cout << *std::lower_bound(lo, hi, It) << "\n";
    std::cout << "range pos: " << range.pos << "\n";
    std::cout << "range lo id: " << range.lo << "\n";
    std::cout << "range lo val: " << *lo << "\n";
    std::cout << "range hi id: " << range.hi << "\n";
    std::cout << "range hi val: " << *hi << "\n";
*/
