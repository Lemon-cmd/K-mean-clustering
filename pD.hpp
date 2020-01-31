#ifndef pD_HPP
#define PD_HPP
#include <stdlib.h>  //for converting string -> double
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class pD
{
    /* Parse Data Class */
    private:
        vector <vector <double> > data; 

    public: 
        void load(const string filename)
        {
            // load file onto the target vector
            ifstream file(filename);    // grab file
            string line;                // a string for holding  current line

            // loop through the file
            while (getline(file, line))
            {
                //if the current line is not empty
                if (!line.empty())
                {
                    //split by comma, or period
                    for (int c = 0; c < line.size(); c ++)
                    {
                        if (line[c] == ',' || line[c] == ';') line[c] = ' ';
                    }
                    
                    vector<double> row;    
                    istringstream input(line);
                    
                    //split by space
                    for (string s; input >> s;)
                    {
                        row.push_back(atof(s.c_str()));  //append individual string onto the vector
                    }
                    //insert the row onto the data
                    data.push_back(row);
                }
            }
        }

        vector <vector <double> > getData()
        {
            return data;
        }
};
#endif