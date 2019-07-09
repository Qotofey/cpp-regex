#include <stdio.h>
#include <iostream>
#include <thread>
#include <boost/regex.hpp>
#include "include/textcalc.hpp"

//$ echo "20 100" | ./bin/calc "(X + 10 * 1) * lg(Y)"

int main(int argc, char **argv) {
  if (argc != 2) { 
    std::cerr << "Ошибка: должен быть один аргумент!" << std::endl;
    return 1;
  }

  double x, y, z;
  std::cin >> x >> y >> z;

  // std::string text = "X * 12 / Y * (Y + X) * Z - lg(X+(X - 1 * Z))";
  // std::string text = "(X + 10) * lg(Y)";
  std::string text = argv[1];
  
  text = boost::regex_replace(text, boost::regex("(X|x)"), std::to_string(x));
  text = boost::regex_replace(text, boost::regex("(Y|y)"), std::to_string(y));
  text = boost::regex_replace(text, boost::regex("(Z|z)"), std::to_string(z));

  auto execThread = std::thread(TextCalc::Do, std::ref(text));
  execThread.join();

  std::cout << text << std::endl;
  // fprintf(stdout, "X = %f\n", x);
  // fprintf(stdout, "Y = %f\n", y);
  // fprintf(stdout, "Z = %f\n", z);

  return 0;
}

