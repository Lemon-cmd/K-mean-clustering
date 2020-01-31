# K-mean Clustering C++

### ***What is K-mean Clustering Algorithm?***
    KMC is a vector quantization method. 
    It seeks to partition n observations into k-numbers centroids or cluster of observations.  
    It is quite an intensive algorithm once the dataset gets huge.

### ***Provided Dataset*** 
    This code uses two datasets.
    
    First dataset is the seeds dataset that contains measurement of geometrical properties of kernels belonging to three 
    different varieties of wheat. It was obtained from https://archive.ics.uci.edu/ml/datasets/seeds 
    
    Second data contains data describing household power consumptions over a duration of four years. 
    It was obtained from https://archive.ics.uci.edu/ml/datasets/individual+household+electric+power+consumption  
    
### Please note that the second dataset is ***huge!***
    
### ***How to use the Code?***
    Simply, run the bash script to build and run the code.
    
    If you want to use a different dataset, take a look at the main.cpp file and change the supposed data file. 
    
    If your dataset contains different format, consider modifying the load method in the pD.hpp file.
    
    If you want to clean your data by taking out certain columns, simply add column # onto the ignore vector in main.cpp. This 
    vector is passed onto the clean method of kmc. 

### Remember to clean your data !

### ***How was the code implemented?*** 
    The implementation is pretty simple. 
    The Cluster method is responsible for initalizing the algorithm. Its parameters are k and iterations. 
    
    Once it is called, the features are mapped onto a hash map grabbing only column # and its minimum and maximum value. 
    The initalization of the centroids begin right after where K vectors are created and mapped onto a hash map where key value is ID # and a centroid data structure. 
    
    Centroid data structure contains the size of the centroid, its entries, and its means (a vector that holds the mean of each feature).
    
    A while loop is initated for count < iterations. Within the loop, the centroids' entry vector is set and then their means are recalculated and then their entry vector is clear. 
    The centroid's entry is not clear once count == iterations - 1. This is simply displaying the last iteration.
    
 ### ***Other Repositories that You Might be Interested In***
https://github.com/Lemon-cmd/GuassianNB       
https://github.com/Lemon-cmd/MultinominalNB     
https://github.com/Lemon-cmd/Neural-Network-Python     
https://github.com/Lemon-cmd/Neural-Network    
https://github.com/Lemon-cmd/A-star     
https://github.com/Lemon-cmd/Dijkstra      
  
   
