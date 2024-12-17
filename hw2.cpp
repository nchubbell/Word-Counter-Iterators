
/*
 Name: Nathan Hubbell
 Email: nchubbell@crimson.ua.edu
 Course Section: Fall 2024 CS 201
 Homework #: 2
 To Compile: g++ -std=c++20 hw2.cpp ST.hpp
 To Run: ./a input.txt
*/

#include <iostream>
#include <vector>
#include <regex>
#include <fstream>
#include <chrono>
#include <thread>
#include <chrono>

#include "ST.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
    ifstream inputFile(argv[1]);
    std::string text;
    std::vector<std::string> tokens;
    // open input file for reading, creates a text string to hold each word, creates a vector token to store every word as an element
    const std::regex delim("\\s+"); 

    ST<string, int> words; // declare the class

    while (inputFile >> text) { 
        auto begin = std::sregex_token_iterator(text.begin(), text.end(), delim, -1);
        auto end = std::sregex_token_iterator();
        for (std::sregex_token_iterator word = begin; word != end; word++) {
            string cur = *word;
            words[cur]++; // enters the word into the class and counts each character 

        }
    }

    vector<pair<string, int>> wordValues = words.toVector(); // turns the class into a vector to use for sorting 

    // sorts the vector by value and then if values are the same, by key to put it in alphabetical order
    sort(wordValues.begin(), wordValues.end(), [](const auto& a, const auto& b) { 
        return a.second > b.second || (a.second == b.second && a.first < b.first);
    });

    // loop outputs the vector by the same display order as the display function in the class
    for (const auto& temp : wordValues) {
        cout << temp.first << ": " << temp.second << endl; 
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl; // outputs time taken to run



    // close file
    inputFile.close();
    return 0;
}