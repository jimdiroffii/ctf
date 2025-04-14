#pragma once

#include <map>
#include <string>
#include <vector>
#include <sstream>

/*
Google CTF - 1837 - Morse Code
*/

//std::string decodeMorse(const std::string& cipher) {
void decodeMorse(const std::string& cipher) {
  const char dit = '.';
  const char dah = '-';

  const std::map<char, std::string> americanMorseCodeEncode = {
      {'A', ".-"},    {'B', "-..."},  {'C', ".-.-"},  {'D', "-.."},
      {'E', "."},     {'F', "..-."},  {'G', "--."},   {'H', "...."},
      {'I', ".."},    {'J', ".---"},  {'K', "-.-"},   {'L', ".-.."},
      {'M', "--"},    {'N', "-."},    {'O', "---"},   {'P', ".--."},
      {'Q', "--.-"},  {'R', ".-."},   {'S', "..."},   {'T', "-"},
      {'U', "..-"},   {'V', "...-"},  {'W', ".--"},   {'X', "-..-"},
      {'Y', "-.--"},  {'Z', "--.."}
  };

  std::map<std::string, char> americanMorseCodeDecode = {
    {".-", 'A'},    {"-...", 'B'},  {".-.-", 'C'},  {"-..", 'D'},
    {".", 'E'},     {"..-.", 'F'},  {"--.", 'G'},   {"....", 'H'},
    {"..", 'I'},    {".---", 'J'},  {"-.-", 'K'},   {".-..", 'L'},
    {"--", 'M'},    {"-.", 'N'},    {"---", 'O'},   {".--.", 'P'},
    {"--.-", 'Q'},  {".-.", 'R'},   {"...", 'S'},   {"-", 'T'},
    {"..-", 'U'},   {"...-", 'V'},  {".--", 'W'},   {"-..-", 'X'},
    {"-.--", 'Y'},  {"--..", 'Z'}
  };

  std::vector<std::string> letters{};
  std::string token{};
  std::string delim = " ";
  std::string delim2 = "/";
  std::size_t pos{};

  size_t last = 0; 
  size_t next = 0; 

  while ((next = cipher.find(delim, last)) != std::string::npos) { 
    token = cipher.substr(last, next - last);
    std::cout << "Token: " << token << '\n';

    bool found = false;
    if (token.find('/') != std::string::npos) {
      found = true;
      size_t last2 = 0;
      size_t next2 = 0;
      std::string token2{};
      while ((next2 = token.find(delim2, last2)) != std::string::npos) {
        token2 = token.substr(last2, next2 - last2);
        std::cout << "Token2: " << token2 << '\n';
        last2 = next2 + 1;
        letters.push_back(token2);
      }
      std::cout << "Token2: " << token.substr(last2) << '\n';
      letters.push_back(token.substr(last2));
    }

    last = next + 1; 

    if (!found) {
      letters.push_back(token);
    }
  } 
  std::cout << "Token: " << cipher.substr(last) << std::endl;
  letters.push_back(cipher.substr(last));

  for (auto &letter : letters) {
    //std::cout << letter << '\n';
    if (americanMorseCodeDecode.contains(letter)) {
      std::cout << americanMorseCodeDecode.at(letter);
    }
    else {
      std::cout << letter;
    }
  }
  /*
  while ((pos = cipher.find(delim)) != std::string::npos) {
    token = s.substr(0, pos);
    std::cout << token << '\n';

  }
  

  std::string result{};
  std::string letter{};

  for (char c : cipher) {
    if (c == ' ') { // space between letters
      continue;
    }
    else if (c == '/') { // finished word

    }
    else if (c == dit || c == dah) {
      letter += c;
    }
  }
  */
}

std::string decodeMorse2(const std::string& morseCode) {
  const std::map<std::string, char> americanMorseCodeDecode = {
    // Morse code mapping
    {".-", 'A'},    {"-...", 'B'},  {".. .", 'C'},  {"-..", 'D'},
    {".", 'E'},     {".-.", 'F'},  {"--.", 'G'},   {"....", 'H'},
    {"..", 'I'},    {".---", 'J'},  {"-.-", 'K'},   {".-..", 'L'},
    {"--", 'M'},    {"-.", 'N'},    {"---", 'O'},   {".--.", 'P'},
    {"--.-", 'Q'},  {".-.", 'R'},   {"...", 'S'},   {"-", 'T'},
    {"..-", 'U'},   {"...-", 'V'},  {".--", 'W'},   {"-..-", 'X'},
    {"-.--", 'Y'},  {"--..", 'Z'},  {".--.", '1'},  {"..-..", '2'},  
    {"...-.", '3'},  {"....-", '4'},  {"---", '5'},  {"......", '6'},  
    {"--..", '7'},  {"-....", '8'},  {"-..-", '9'},  {"-", '0'}
  };

  std::map<std::string, char> continentalMorseCode = {
    {".-", 'A'},    {"-...", 'B'},  {"-.-.", 'C'},  {"-..", 'D'},
    {".", 'E'},     {"..-.", 'F'},  {"--.", 'G'},   {"....", 'H'},
    {"..", 'I'},    {".---", 'J'},  {"-.-", 'K'},   {".-..", 'L'},
    {"--", 'M'},    {"-.", 'N'},    {"---", 'O'},   {".--.", 'P'},
    {"--.-", 'Q'},  {".-.", 'R'},   {"...", 'S'},   {"-", 'T'},
    {"..-", 'U'},   {"...-", 'V'},  {".--", 'W'},   {"-..-", 'X'},
    {"-.--", 'Y'},  {"--..", 'Z'},
    {"-----", '0'}, {".----", '1'}, {"..---", '2'}, {"...--", '3'},
    {"....-", '4'}, {".....", '5'}, {"-....", '6'}, {"--...", '7'},
    {"---..", '8'}, {"----.", '9'}
  };

  std::string result;
  std::string currentCode;

  for (char ch : morseCode) {
    if (ch == '.' || ch == '-') {
      currentCode += ch;
    }
    else {
      if (!currentCode.empty()) {
        auto it = continentalMorseCode.find(currentCode);
        if (it != continentalMorseCode.end()) {
          result += it->second;
        }
        else {
          result += currentCode;
        }
        currentCode.clear();
      }

      if (ch != ' ') {
        result += ch;
      }
      if (ch == '/') {
        result.back() = ' ';  // Replace slash with space in the result
      }
    }
  }

  // Decoding the last Morse code sequence if any
  if (!currentCode.empty()) {
    auto it = continentalMorseCode.find(currentCode);
    if (it != continentalMorseCode.end()) {
      result += it->second;
    }
    else {
      result += currentCode;
    }
  }

  return result;
}