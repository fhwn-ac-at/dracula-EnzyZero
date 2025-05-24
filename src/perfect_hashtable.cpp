/* C++ code produced by gperf version 3.1 */
/* Command-line: gperf chars.gperf  */
/* Computed positions: -k'1' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gperf@gnu.org>."
#endif

#line 1 "chars.gperf"

#include <string.h>

#define TOTAL_KEYWORDS 31
#define MIN_WORD_LENGTH 1
#define MAX_WORD_LENGTH 1
#define MIN_HASH_VALUE 0
#define MAX_HASH_VALUE 31
/* maximum key range = 32, duplicates = 0 */

class perfect_hashtable
{
private:
  static inline unsigned int hash (const char c);
public:
  static const char in_word_set (const char c);
};

inline /*ARGSUSED*/
unsigned int
perfect_hashtable::hash (const char c)
{
  static const unsigned char asso_values[] =
    {
      32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
      32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
      32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
      32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
      32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
      32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
      32, 32, 32, 32, 32, 22, 32, 32, 17, 32,
      12, 32,  7,  2, 29, 24, 19, 14, 32,  9,
       4, 31, 26, 21, 32, 32, 32, 32, 16, 32,
      32, 32, 32, 32, 32, 32, 32, 11, 32, 32,
       6,  1, 28, 32, 23, 18, 13,  8,  3, 30,
      32, 25, 20, 15, 10,  5, 32, 32, 32, 32,
       0, 32, 32, 32, 32, 32, 32, 32
    };
  return asso_values[static_cast<unsigned char>(c)];
}

const char
perfect_hashtable::in_word_set (const char c)
{
  static const char wordlist[] =
    {
      'x',
      'e',
      'I',
      'l',
      'P',
      's',
      'd',
      'H',
      'k',
      'O',
      'r',
      'a',
      'F',
      'j',
      'M',
      'q',
      'X',
      'D',
      'i',
      'L',
      'p',
      'S',
      'A',
      'h',
      'K',
      'o',
      'R',
      0,
      'f',
      'J',
      'm',
      'Q'
    };

    unsigned int key = hash (c);

    if (key <= MAX_HASH_VALUE)
        return wordlist[key];

  return 0;
}
