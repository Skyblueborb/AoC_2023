#include <cctype>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/find.hpp>

#include <boost/convert.hpp>
#include <boost/convert/lexical_cast.hpp>

int solve_part1(std::string time, std::string distance);
int solve_part2(std::string time, std::string distance);
std::vector<std::string> split (const std::string &s, char delim);

struct boost::cnv::by_default : boost::cnv::lexical_cast {};

int main (void) {
    std::string time;
    std::string distance;
    int sum_of_points = 0;
    std::ifstream in("input", std::ios_base::in);
    getline(in, time);
    getline(in, distance);
    std::cout << "Part 1 result: " << solve_part1(time, distance) << std::endl;
    std::cout << "Part 2 result: " << solve_part2(time, distance);
    return 0;
}

int solve_part1(std::string time, std::string distance) {
    std::string delimiter = ":";
    time.erase(0, time.find(delimiter) + 2);
    distance.erase(0, distance.find(delimiter) + 2);
    boost::algorithm::trim(time);
    boost::algorithm::trim(distance);

    std::vector<std::string> v = split(time, ' ');
    std::vector<std::string> v2 = split(distance, ' ');
    // convert to ints
    std::vector<int> timeAllowed;
    std::vector<int> distanceRecords;
    for (auto i : v) timeAllowed.push_back(boost::convert<int>(i).value());
    for (auto i : v2) distanceRecords.push_back(boost::convert<int>(i).value());
    int finalDistance = 0, permutations = 0, final_score = 0;
    for (int k = 0; k < timeAllowed.size(); k++) {
        // i - distancePerMs
        for (int i = 0; i < timeAllowed.at(k); i++) {
            finalDistance=i*(timeAllowed.at(k) - i);
            if(finalDistance > distanceRecords.at(k)) permutations++;
            finalDistance = 0;
        }
        if (final_score == 0) {
            final_score = permutations;
        } else {
            final_score *= permutations;
        }
        permutations = 0;
    }
    return final_score;
}

int solve_part2(std::string time, std::string distance) {
    std::string delimiter = ":";
    time.erase(0, time.find(delimiter) + 2);
    distance.erase(0, distance.find(delimiter) + 2);
    boost::algorithm::trim(time);
    boost::algorithm::trim(distance);

    std::vector<std::string> v = split(time, ' ');
    std::vector<std::string> v2 = split(distance, ' ');
    // convert to int
    u_int64_t timeAllowed, distanceRecord;
    std::string buffer = "";
    for (auto i : v) buffer += i;
    timeAllowed = boost::convert<int>(buffer).value();
    buffer = "";
    for (auto i : v2) buffer += i;
    distanceRecord = boost::convert<u_int64_t>(buffer).value();
    u_int64_t finalDistance = 0, permutations = 0;
    // i - distancePerMs
    for (u_int64_t i = 0; i < timeAllowed; i++, finalDistance = 0) {
        finalDistance=i*(timeAllowed-i);
        if(finalDistance > distanceRecord) permutations++;
    }
    return permutations;
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
