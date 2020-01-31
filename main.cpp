#include "kmc.hpp"

int main()
{
    pD parse = pD();
    parse.load("data/seeds_dataset.txt");
    
    KMC kmc = KMC();
    //vector <int> ignores = {0,1}; //ignore  columns

    kmc.setData(parse.getData());
    //kmc.clean(ignores);
    kmc.cluster(5, 10);

}
