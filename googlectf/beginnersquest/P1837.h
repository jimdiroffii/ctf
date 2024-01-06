/***
 * Google CTF - Beginner's Quest
 * Functions for solving Problem Set 1837
 *
 * By: jimdiroffii
 *
 * CTF: https://capturetheflag.withgoogle.com/beginners-quest
 *
 * A collection of functions and solutions to the Beginner's Quest problems
 * 
 * International Morse Code: https://www.itu.int/dms_pubrec/itu-r/rec/m/R-REC-M.1677-1-200910-I!!PDF-E.pdf
 * 
 */

#pragma once
#ifndef P1837_H
#define P1837_H

#include <map>
#include <string>
#include <vector>
#include <sstream>

/***
 * Morse Code Decoding Maps
 *
 * `L` and `0` are weird, L has a long dah, and 0 has a very long dah
 * I just put four question marks for now
 * 
 * Also note that some of the character sequences have spaces within them
 * 
 * There are also some codes for puncuation
 * 
 * Spacing and length of the signals
 * 1 A dash is equal to three dots.
 * 2 The space between the signals forming the same letter is equal to one dot.
 * 3 The space between two letters is equal to three dots.
 * 4 The space between two words is equal to seven dots.
 */
const std::map<std::string, char> americanMorseCodeDecode = {
  {".-", 'A'},    {"-...", 'B'},  {".. .", 'C'},  {"-..", 'D'},
  {".", 'E'},     {".-.", 'F'},  {"--.", 'G'},   {"....", 'H'},
  {"..", 'I'},    {"-.-.", 'J'},  {"-.-", 'K'},   {"⸺", 'L'},
  {"--", 'M'},    {"-.", 'N'},    {". .", 'O'},   {".....", 'P'},
  {"..-.", 'Q'},  {". ..", 'R'},   {"...", 'S'},   {"-", 'T'},
  {"..-", 'U'},   {"...-", 'V'},  {".--", 'W'},   {".-..", 'X'},
  {".. ..", 'Y'},  {"... .", 'Z'},  {".--.", '1'},  {"..-..", '2'},
  {"...-.", '3'},  {"....-", '4'},  {"---", '5'},  {"......", '6'},
  {"--..", '7'},  {"-....", '8'},  {"-..-", '9'},  {"⸻", '0'},
  {"..--..", '.'}, {".-.-", ','}, {"-.- . .", ':'}, {"-..-.", '?'},
  {"..-. .-..", '\''}, {"... .-..", '-'}, {"..- -", '/'}, {"..... -.", '('},
  {"..... .. ..", ')'}, {"..-. -.", '"'}, {". ...", '&'}, {"---.", '!'},
  {"... ..", ';'}
};

const std::map<std::string, char> internationalMorseCodeDecode = {
  {".-", 'A'},    {"-...", 'B'},  {"-.-.", 'C'},  {"-..", 'D'},
  {".", 'E'},     {"..-.", 'F'},  {"--.", 'G'},   {"....", 'H'},
  {"..", 'I'},    {".---", 'J'},  {"-.-", 'K'},   {".-..", 'L'},
  {"--", 'M'},    {"-.", 'N'},    {"---", 'O'},   {".--.", 'P'},
  {"--.-", 'Q'},  {".-.", 'R'},   {"...", 'S'},   {"-", 'T'},
  {"..-", 'U'},   {"...-", 'V'},  {".--", 'W'},   {"-..-", 'X'},
  {"-.--", 'Y'},  {"--..", 'Z'}, {".----", '1'}, {"..---", '2'},
  {"...--", '3'}, {"....-", '4'}, {".....", '5'}, {"-....", '6'},
  {"--...", '7'}, {"---..", '8'}, {"----.", '9'}, {"-----", '0'},
  {".-.-.-", '.'}, {"--.--", ','}, {"---...", ':'}, {"..--..", '?'},
  {".----.", '\''}, {"-....-", '-'}, {"-..-.", '/'}, {"-.--.", '('}, 
  {"-.--.-", ')'}, {".-..-.", '"'}, {"-...-", '='}, {".-.-.", '+'}
};

std::string decodeMorse(const std::string& code) {
  std::string result{};
  std::string token{};

  for (char ch : code) {
    if (ch == )
  }
}










#endif // P1837_H