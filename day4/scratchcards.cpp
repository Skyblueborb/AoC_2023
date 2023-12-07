#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/find.hpp>

#include <boost/convert.hpp>
#include <boost/convert/lexical_cast.hpp>

int parse_line(std::string line);
std::vector<std::string> split (const std::string &s, char delim);
bool is_number(std::string s);

struct boost::cnv::by_default : boost::cnv::lexical_cast {};

int main (void) {
    std::string line;
    int sum_of_points = 0;
    std::ifstream in("input", std::ios_base::in);
    while (getline(in, line)) {
        sum_of_points += parse_line(line);
    };
    std::cout << "Part 1 results: " << sum_of_points;
    return 0;
}

int parse_line(std::string line) {
    // Ignore card no.
    int points = 0;
    std::string delimiter = ":";
    line.erase(0, line.find(delimiter) + 2);
    boost::algorithm::trim(line);

    std::vector<std::string> v = split(line, '|');
    std::vector<int> winning_numbers, picked_numbers;
    std::vector<std::string> v2 = split(v.at(0), ' ');
    for (auto j : v2) {
        winning_numbers.push_back(boost::convert<int>(j).value());
    }
    std::vector<std::string> v3 = split(v.at(1), ' ');
    for (auto j : v3) {
        picked_numbers.push_back(boost::convert<int>(j).value());
    }

    for (auto j : picked_numbers) {
        if(std::find(winning_numbers.begin(), winning_numbers.end(), j) != winning_numbers.end()) {
            if(points == 0) points++;
            else points*=2;
        };
    }

    return points;
}

std::vector<std::string> split (const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, delim)) {
        boost::algorithm::trim(item);
        if(!item.empty()) result.push_back(item);
    }

    return result;
}

bool is_number(std::string s) {
    for (auto i : s) if(!std::isdigit(i)) return false;
    return true;
}
