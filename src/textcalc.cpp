#include "../include/textcalc.hpp"

std::string FormatterMultOrDiv(const boost::smatch &m) {
    switch (m.str(2)[0]) {
    case '*':
        return std::to_string(std::stod(m[1]) * std::stod(m[3]));
    case '/':
        return std::to_string(std::stod(m[1]) / std::stod(m[3]));
    }
  return m[0];
}

std::string FormatterSumOrDiff(const boost::smatch &m) {
    switch (m.str(2)[0]) {
    case '+':
        return std::to_string(std::stod(m[1]) + std::stod(m[3]));
    case '-':
        return std::to_string(std::stod(m[1]) - std::stod(m[3]));
    }
    return m[0];
}

std::string FormatterMathFunc(const boost::smatch &m) {
    if (m[1] == "lg") {
        return std::to_string(log(std::stod(m[2])) / log(10));
    } else if (m[1] == "log") {
        return std::to_string(log(std::stod(m[2])));
    } else if (m[1] == "cos") {
        return std::to_string(cos(std::stod(m[2])));
    } else if (m[1] == "sin") {
        return std::to_string(sin(std::stod(m[2])));
    } else if (m[1] == "tan") {
        return std::to_string(tan(std::stod(m[2])));
    } else if (m[1] == "acos") {
        return std::to_string(acos(std::stod(m[2])));
    } else if (m[1] == "asin") {
        return std::to_string(asin(std::stod(m[2])));
    } else if (m[1] == "atan") {
        return std::to_string(atan(std::stod(m[2])));
    }
    return m[0];
}

void TextCalc::MultOrDiv(std::string &text) {
    boost::regex pattern("([\\-]?\\d+[\\.]?\\d*)\\s*([*/])\\s*([\\-]?\\d+[\\.]?\\d*)");
    for (;;) {
        boost::smatch match;
        if (!boost::regex_search(text, match, pattern)) { 
            return;
        } 
        text = boost::regex_replace(text, pattern, FormatterMultOrDiv);
    }
}

void TextCalc::SumOrDiff(std::string &text) {
    boost::regex pattern("([\\-]?[\\d]+[\\.]?\\d*)\\s*([+\\-])\\s*([\\-]?\\d+[\\.]?\\d*)");
    for (;;) {
        boost::smatch match;
        if (!boost::regex_search(text, match, pattern)) { 
            return;
        }
        text = boost::regex_replace(text, pattern, FormatterSumOrDiff);
    }
}

void TextCalc::MathFunc(std::string &text) {
    boost::regex pattern("(lg|cos|sin)([\\-]?[\\d]+[\\.]?[\\d]*)");
    for (;;) {
        boost::smatch match;
        if (!boost::regex_search(text, match, pattern)) { 
            return;
        }
        text = boost::regex_replace(text, pattern, FormatterMathFunc);
    }
}

void TextCalc::Do(std::string &text) {

    boost::smatch match;
    do {
        std::thread th1(TextCalc::MultOrDiv, std::ref(text));
        th1.join();

        std::thread th2(TextCalc::SumOrDiff, std::ref(text));
        th2.join();

        auto pattern = boost::regex("\\([\\s]*([\\-]?[\\d]+[\\.]?\\d*)[\\s]*\\)");
        text = boost::regex_replace(text, pattern, "$1");

        std::thread th3(TextCalc::MathFunc, std::ref(text));
        th3.join();

    } while (!boost::regex_search(text, match, boost::regex("(^[\\-]?[\\d]+[\\.]?[\\d]*$)")));
  

}