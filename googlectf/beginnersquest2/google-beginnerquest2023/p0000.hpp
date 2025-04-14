#pragma once
#ifndef p0000_HPP
#define p0000_HPP

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <map>

/* Caesar Cipher Solver */
inline std::string caesar(const std::string& str, int shift) {
  std::string result{};

  // substitution
  for (auto ch : str) {
    if (isalpha(ch)) {
      auto base = islower(ch) ? 'a' : 'A';
      ch = static_cast<char>((ch - base + shift) % 26 + base);
    }
    result += ch;
  }

  return result;
}

/* Brute force Caesar */
inline void brutus(const std::string& str) {
  for (int i = 1; i <= 25; ++i) {
    std::string decrypted = caesar(str, i);
    std::cout << std::left << "shift " << std::setw(3) << i << ": " << decrypted << '\n';
  }
}

/* Sequence Caesar - Multiple shifts based on key */
inline std::string seqCaesar(const std::string& cipher, const std::vector<int>& key) {
  std::size_t keyIndex{};
  std::size_t keySize = key.size();

  std::string result{};

  for (auto ch : cipher) {
    if (isalpha(ch)) {
      if (keyIndex >= keySize) {
        keyIndex = 0;
      }

      auto base = islower(ch) ? 'a' : 'A';
      ch = static_cast<char>((ch - base + key[keyIndex++]) % 26 + base);
    }
    result += ch;
  }

  return result;
}

/* Mapped Caesar */
inline std::string mapCaesar(const std::string& cipher, const std::map<char, char> key) {
  std::string result{};

  for (auto ch : cipher) {
    if (key.find(ch) != key.end()) {
      result += key.at(ch);
    }
    else {
      result += ch;
    }
  }
  return result;
}

/* Brute Force Tranposition */
inline void replaceSpecialSequence(std::string& input) {
  const std::string specialSequence = "␣"; // Define the special sequence
  size_t pos = 0;
  while ((pos = input.find(specialSequence, pos)) != std::string::npos) {
    input.replace(pos, specialSequence.length(), "_"); // Replace with underscore
    pos += 1; // Move past the underscore
  }
}

inline void print2DVector(const std::vector<std::vector<char>>& vec) {
  for (const auto& row : vec) {
    std::cout << "{";
    for (size_t i = 0; i < row.size(); ++i) {
      std::cout << row[i];
      if (i < row.size() - 1) {
        std::cout << ",";
      }
    }
    std::cout << "}" << std::endl; // Print each row on a new line
  }
}

inline std::vector<std::vector<char>> rearrangeColumns(const std::vector<std::vector<char>>& matrix) {
  const std::vector<int> newOrder = { 2, 0, 3, 5, 1, 4 };
  std::vector<std::vector<char>> rearranged(matrix.size(), std::vector<char>(matrix[0].size(), ' '));

  for (size_t row = 0; row < matrix.size(); ++row) {
    for (size_t col = 0; col < matrix[0].size(); ++col) {
      rearranged[row][col] = matrix[row][newOrder[col]];
    }
  }

  return rearranged;
}

inline std::string buildStringFrom2DArray(const std::vector<std::vector<char>>& matrix) {
  std::string result;
  for (const auto& row : matrix) {
    for (char ch : row) {
      if (ch != ' ') { // Skip spaces if you don't want them in the final string
        result += ch;
      }
    }
  }
  return result;
}

inline void transpositionIteration(std::string input) {
  replaceSpecialSequence(input); // Replace special sequences in the input
  std::vector<std::vector<char>> result{};
  size_t numColumns = 1;
  while (true) {
    size_t numRows = (input.length() + numColumns - 1) / numColumns; // Ceiling division
    std::vector<std::vector<char>> matrix(numRows, std::vector<char>(numColumns, ' ')); // Fill with spaces for alignment

    for (size_t i = 0; i < input.size(); ++i) {
      size_t row = i % numRows;
      size_t col = i / numRows;
      matrix[row][col] = input[i];
    }

    print2DVector(matrix);

    char choice;
    std::cout << "Continue with the next iteration? (y/n): ";
    std::cin >> choice;
    if (choice != 'y') {
      result = matrix;
      break;
    }

    ++numColumns;
  }

  result = rearrangeColumns(result);
  print2DVector(result);
  std::cout << buildStringFrom2DArray(result);
}

#endif //p0000_HPP