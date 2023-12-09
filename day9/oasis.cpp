#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/find.hpp>

#include <boost/convert.hpp>
#include <boost/convert/lexical_cast.hpp>

int parse_line(std::string line);
int recursion(std::vector<long int> start);
bool allElementsSame (std::vector<long int> v);
std::vector<std::string> split (const std::string &s, char delim);

struct boost::cnv::by_default : boost::cnv::lexical_cast {};


int main(void) {
    std::string buf;
    int sum_of_points = 0;
    std::ifstream in("input", std::ios_base::in);
    while(getline(in, buf)) {
        sum_of_points+=parse_line(buf);
    }
    std::cout << sum_of_points;
    return 0;
}

int parse_line(std::string line) {
    boost::algorithm::trim(line);
    std::vector<std::string> v = split(line, ' ');

    std::vector<long int> startingVector;
    for (auto i : v) startingVector.push_back(boost::convert<long int>(i).value());
    return recursion(startingVector);
}

int recursion(std::vector<long int> start) {

    std::vector<long int> v;
    for (int i = 0; i < start.size() - 1; i++) {
        v.push_back(start.at(i+1) - start.at(i));
    }
    if(v.size() == 2 && (allElementsSame(v))) {
        return start.back();
    }
    if(v.size() == 1) return v.back();
    if(v.at(v.size()-2) - v.back() != 0 || v.at(v.size()-3) - v.back() != 0) {
        v.push_back(recursion(v));
        return start.back() + v.back();
    }
    return start.back() + v.back();
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

bool allElementsSame (std::vector<long int> v) {
    long int buf = v.at(0);
    for (auto i : v) if (i != buf) return false;
    return true;
}
