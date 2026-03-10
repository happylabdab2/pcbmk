#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <svgpp/svgpp.hpp>

using namespace svgpp;
using namespace std;

std::string trim(const std::string &s)
{
    const std::string whitespace = " \t\n\r\f\v";
    size_t start = s.find_first_not_of(whitespace);
    size_t end = s.find_last_not_of(whitespace);

    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

size_t countCharOccurrences(const std::string &str, char target)
{
    size_t count = 0;
    for (char ch : str)
    {
        if (ch == target)
        {
            ++count;
        }
    }
    return count;
}

int main(int argc, char *argv[])
{
#pragma region Argument Code
    if (argc != 3)
    {
        printf("Usage: %s [Input File] [Output File]\n", argv[0]);
        return 1;
    }

    ifstream gbrFile(argv[1]);
    ofstream svgFile(argv[2]);

    if (!gbrFile.is_open())
    {
        cout << "Error opening input file: " << argv[1] << endl;
        return 1;
    }

    if (!svgFile.is_open())
    {
        cout << "Error opening output file: " << argv[2] << endl;
        return 1;
    }
#pragma endregion

    string line;
    string sbuffer; // for multiline extended commands

    while (getline(gbrFile, line))
    {
        line = trim(line);
        if (line[0] == '%') // extended command
        {
            // convert to single line
            if (countCharOccurrences(line, '%') == 2) // single line extended command
            {
                cout << "Single line extended command: " << line << endl;
                sbuffer = line;
            }
            else // start of multiline extended command
            {
                sbuffer = line;
                while (getline(gbrFile, line))
                {
                    sbuffer += " " + line;
                    if (countCharOccurrences(line, '%') == 1)
                    {
                        cout << "Multiline extended command: " << sbuffer << endl; // now in in buffer

                        break;
                    }
                }
            }
        
        }

        else if ((line[0] == 'G' || line[0] == 'D' || line[0] == 'M') && (line.find("G04") != std::string::npos)) // check valid G code command
        {

            cout << "G code command: " << line.substr(0, 3) << endl;
            cout << "G code arg: " << trim(line.substr(3)) << endl;
        }
        #pragma region comment + error check
        if (line[0] == '#' || line[0] == '@' || line[0] == '!') // skip comments
        {
            continue;
        }
        else if (line.empty())
        {
            continue;
        }
        else
        {
            cout << "Unknown line: " << line << endl;
            throw runtime_error("Unknown line format");
            continue;
        }
        #pragma endregion

    }

    gbrFile.close();
    svgFile.close();

    return 0;
}