#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <boost/algorithm/string/find.hpp>
#include <boost/convert.hpp>
#include <boost/convert/lexical_cast.hpp>

int parse_line_part1(std::string line);
int parse_line_part2(std::string line);
std::vector<int> find_numbers(std::string line);

struct boost::cnv::by_default : boost::cnv::lexical_cast {};

int main(void) {
    std::string line;
    int sum_part1 = 0, sum_part2 = 0;
    std::ifstream in("input", std::ios_base::in);

    while(getline(in, line)) {
        sum_part1 += parse_line_part1(line);
        sum_part2 += parse_line_part2(line);
    }
    std::cout << "Part 1 result: " << sum_part1 << std::endl << "Part 2 result: " << sum_part2;
    return 0;
}

int parse_line_part1(std::string line) {
    std::vector<int> numberVector;
    for (auto ch : line) {
        if(std::isdigit(ch)) numberVector.push_back(boost::convert<int>(ch).value());
    }

    return numberVector.at(0) * 10 + numberVector.back();
}

// Part 2
int parse_line_part2(std::string line) {
    std::vector<int> numbers = find_numbers(line);

    return numbers.at(0) * 10 + numbers.at(1);
}

std::vector<int> find_numbers(std::string line) {
    std::vector<std::string> numberNames = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    std::vector<int> nameVectorFirst(9);
    std::vector<int> nameVectorLast(9);
    std::vector<int> numberVector;
    boost::iterator_range<std::string::iterator> it;
    int iterations = 0, iter = 1, lowest_index = 64, highest_index = 0, first_number=0, last_number = 0;
    for (auto ch : line) {
        if(std::isdigit(ch)) numberVector.push_back(boost::convert<int>(ch).value());
    }
    for (auto i : numberNames) {
        it = boost::find_first(line, i);
        nameVectorFirst[iterations] = (it.empty()) ? -1 : std::distance(line.begin(), it.begin());
        it = boost::find_last(line, i);
        nameVectorLast[iterations] = (it.empty()) ? -1 : std::distance(line.begin(), it.begin());
        iterations++;
    }
    for (auto i : nameVectorFirst) {
        if(i != -1 && lowest_index > i) {
            lowest_index = i;
            first_number = iter;
        }
        iter++;
    }
    iter = 1;
    for (auto i : nameVectorLast) {
        if(i != -1 && highest_index < i) {
            highest_index = i;
            last_number = iter;
        }
        iter++;
    }
    std::vector<int> results(2);
    if(!numberVector.empty()) {
        for (auto i : nameVectorFirst) {
            boost::iterator_range<std::string::iterator> it = boost::find_first(line, std::to_string(numberVector.at(0)));
            int lowest_vector_index = (it.empty()) ? -1 : std::distance(line.begin(), it.begin());
            if(lowest_index < lowest_vector_index && lowest_vector_index != -1) {
                results.at(0) = first_number;
            }
            else {
                results.at(0) = numberVector.at(0);
            }
        }
        for (auto i : nameVectorLast) {
            boost::iterator_range<std::string::iterator> it = boost::find_last(line, std::to_string(numberVector.back()));
            int highest_vector_index = (it.empty()) ? -1 : std::distance(line.begin(), it.begin());
            if(highest_index > highest_vector_index && highest_vector_index != -1) {
                results.at(1) = last_number;
            }
            else {
                results.at(1) = numberVector.back();
            }
    }
    } else {
        results.at(0) = first_number;
        results.at(1) = last_number;
    }

    return results;
}
