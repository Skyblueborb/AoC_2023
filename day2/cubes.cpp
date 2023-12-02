#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/find.hpp>

#include <boost/convert.hpp>
#include <boost/convert/lexical_cast.hpp>

int parse_line_part1(std::string line);
int parse_line_part2(std::string line);
std::vector<std::string> split (const std::string &s, char delim);
std::vector<int> parse_results(std::string s);
int find_game_id(std::string s);

struct boost::cnv::by_default : boost::cnv::lexical_cast {};

int main (void) {
    std::string line;
    int sum_of_powers = 0, sum_of_game_ids = 0;
    std::ifstream in("input", std::ios_base::in);
    while (getline(in, line)) {
        sum_of_game_ids += parse_line_part1(line);
        sum_of_powers += parse_line_part2(line);

    };
    std::cout << "Part 1 results: " << sum_of_game_ids << std::endl << "Part 2 results: " << sum_of_powers;
    return 0;
}

int parse_line_part1(std::string line) {
    int game_id = find_game_id(line);
    std::string delimiter = ":";
    line.erase(0, line.find(delimiter) + 2);

    std::vector<std::string> v = split(line, ';');
    int iteration = 0;
    for (auto i : v) {
        std::vector<std::string> v2 = split(i, ',');
        for (auto j : v2) {
            std::vector<int> results = parse_results(j);
            if(results[0] > 12) {
                return 0;
            }
            if(results[1] > 13) {
                return 0;
            }
            if(results[2] > 14) {
                return 0;
            }
        }
    }
    return game_id;
}

int parse_line_part2(std::string line) {
    int max_red = 0, max_green = 0, max_blue = 0;
    std::string delimiter = ":";
    line.erase(0, line.find(delimiter) + 2);

    std::vector<std::string> v = split(line, ';');
    int iteration = 0;
    for (auto i : v) {
        std::vector<std::string> v2 = split(i, ',');
        for (auto j : v2) {
            std::vector<int> results = parse_results(j);
            if(results[0] > max_red) {
                max_red=results[0];
            }
            if(results[1] > max_green) {
                max_green=results[1];
            }
            if(results[2] > max_blue) {
                max_blue=results[2];
            }
        }
    }
    return max_red*max_green*max_blue;
}

std::vector<std::string> split (const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, delim)) {
        boost::algorithm::trim(item);
        result.push_back(item);
    }

    return result;
}

std::vector<int> parse_results(std::string s) {
    // red, green, blue - index 0, 1, 2
    std::vector<int> results(3);
    std::vector<std::string> v = split(s, ' ');
    for (auto i : v) {
        if(boost::iequals(i, "red")) {
            results[0] = boost::convert<int>(v.at(0)).value();
        }
        if(boost::iequals(i, "green")) {
            results[1] = boost::convert<int>(v.at(0)).value();
        }
        if(boost::iequals(i, "blue")) {
            results[2] = boost::convert<int>(v.at(0)).value();
        }
    }
    return results;
}

int find_game_id(std::string s) {
    s.erase(s.find(':'));
    std::vector<std::string> v = split(s, ' ');
    return boost::convert<int>(v.at(1)).value();
}
