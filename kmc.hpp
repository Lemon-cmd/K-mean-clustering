#ifndef KMC_HPP
#define KMC_HPP
#include "pD.hpp"
#include "heap.hpp"
#include <algorithm>
#include <math.h>
#include <map>

class KMC
{
    /* K-MEAN CLUSTER ALGORITHM */
    private:
        struct metadata
        {
            /* metadata structure to use to describe each feature */
            double mean;            // feature's mean
            double minimum;         // feature's min
            double maximum;         // feature's max
        };

        struct centroid_data
        {
            /* centroid metadata */
            vector <vector <double> > entries;      // vector that holds entries of the centroid
            vector <double> means;                  // vector that holds current means of each column in centroid
            int size = 0;                           // entries size

            void display()
            {
                /* A method for displaying entries of the centroid */
                for (auto &row : entries)
                {
                    for (auto &col : row)
                    {
                        cout << col << " ";
                    }
                    cout << "\n";
                }
            }
        };

        int k;                                      // K-num clusters

        vector <vector <double> > data;             // data vector    
        int data_size;                              // data vector size

        map <int, metadata*> features;              // features map; holds col # and each feature metadata
        map <int, centroid_data*> centroids;        // centroids map; holds centroid # and each centroid data

        void setMeans()
        {
            /* A method for recalculating the mean of individual centroid */
            for (auto &center : centroids)
            {
                //centroid's entries size is 0, keep its mean the same
                if (center.second->size != 0)
                {
                    //new means vector
                    vector <double> new_means;
                    for (int col = 0; col < center.second->entries[0].size(); col ++)
                    {
                        /* Calculate mean of each feature */
                        double mean = 0.0;
                        for (auto &row : center.second->entries)
                        {
                            mean += row[col];
                        }

                        mean = mean / double(center.second->size);              //set the mean
                        new_means.push_back(mean);                              //push mean onto new_means vector
                    }
                    //set means vector equals to new means
                    center.second->means = new_means;
                }
            }
        }

        void clearEntries()
        {
            /* Clear each centroid's centries */
            for (auto &center : centroids)
            {
                //clear entries
                center.second->entries.clear();
                //reset entries size to 0
                center.second->size = 0;
            }
        }

        void setEntries()
        {
            /* Set new entries for each centroid */
            for (auto &row : data)
            {
                Heap heap = Heap();                                             //min heap; emptied out for new row
                for (auto &center : centroids)
                {
                    Dist* target = new Dist();                                  //new dist struct
                    target->num = center.first;                                 //set centroid's ID
                    target->distance = euclideanD(center.second->means, row);   //set distance
                    heap.insert(target);                                        //insert Dist onto min heap
                }
                Dist* item = heap.pop();                                     //get lowest distance
                centroids[item->num]->entries.push_back(row);               //push the new entry into the appropriate centroid
                centroids[item->num]->size += 1;                            //increment entries size
            }
        }

        const double euclideanD(const vector <double> &means, const vector <double> &target)
        {
            /* Euclidean Distance Method */
            double distance = 0.0;

            for (int col = 0; col < means.size(); col ++ )
            {
                //summation of (xi - yi)^2
                distance += pow(means[col] - target[col], 2);
            }
            //sqrt of summation
            return sqrt(distance);
        }

        void initCentroids()
        {
            /* initalize K centroids */
            for (int i = 0; i < k; i ++)
            {
                //set centroid data
                centroid_data* item = new centroid_data();
                //set X equals to Feature map
                centroids[i] = item;               
            }
            
            //initializes means vector for each feature based on its min and max
            for (auto &center: centroids)
            {
                for (auto &x : features)
                {
                    //random range from min + 1  to max - 1; -+ 1 to avoid great variance of the mean
                    //push each feature's mean onto the means vector
                    center.second->means.push_back((x.second->maximum) * ((double)rand() / (double)RAND_MAX) \
                                    + x.second->minimum);

                    //center.second->means.push_back((x.second->maximum + x.second->minimum) / 2.0);
                }
            }
            
        } 

        void getMinMax(metadata* item, const double &value)
        {
            /* Set Minimum and Maximum value of each feature */
            if (value < item->minimum)
            {
                item->minimum = value;
            }

            if (value > item->maximum)
            {
                item->maximum = value;
            }
        }

        void initFeatures()
        {
            // Set Column # and set each feature minimum and maximum onto the features map */
            for (auto &row : data)
            {
                int row_size = row.size();
                
                for (int col = 0; col < row_size; col ++)
                {
                    if (features.find(col) == features.end())
                    {
                        metadata* item = new metadata();
                        item->maximum = row[col]; item->minimum = row[col];
                        features[col] = item;
                    }
                    else
                    {
                        //get min and max
                        getMinMax(features[col], row[col]);
                    }
                }
            }

        }

    public: 
        void display()
        {
            /* Display data method */
            for (auto &row : data)
            {
                for (auto &col : row)
                {
                    cout << col << " ";
                }
                cout << "\n";
            }
        }   

        void setData(const vector <vector <double> > &target)
        {
            /* load data method */
            data = target;
            data_size = data.size();
        }

        void clean(vector <int> &ignores)
        {
            /* Method for cleaning data; parameter is a vector that holds data's COLUMN to get rid of */
            
            vector <vector <double> > new_data;                        // a vector that holds cleaned data

            for (auto &row : data)
            {
                vector <double> current_row;               // a vector that holds current row's items

                for (int col = 0; col < row.size(); col ++)
                {   
                    // if col is not in the vector ignores
                    if (find(ignores.begin(), ignores.end(), col) == ignores.end())
                    {
                        //append to temp_row
                        current_row.push_back(row[col]);       
                    }
                }
                //push current row onto new_data
                new_data.push_back(current_row);
            }
            //set data equals to new data
            data = new_data;
        }

        void cluster(const int &kn, int iterations)
        {
            /* KMC Method */

            k = kn;                             //set K numbers
            initFeatures();                     //initialize features map
            initCentroids();                    //initalize K-num of centroids and its starting mean
            int count = 0;                      //count value
        
            while (count < iterations)         
            {
                setEntries();                   //set new entries onto centroids
                setMeans();                     //set new means onto centroids
                if (count != iterations - 1)    //if the loop is not at its last iteration
                    clearEntries();             //clear entries for the next iteration

                count ++;                       //increment count
            }
           
            /* Display each cluster! */
            for (auto &center : centroids)
            {
                cout << "CENTER #: " << center.first << endl;
                center.second->display();
                cout << "\n";
            }
            
        }
};

#endif 