// ConsoleApplication23.cpp : Defines the entry point for the console application.
//
#include "External_Functions.h"




void add_holes(QVector<segment>&v, QVector<int> adress, QVector<int> size, int total) {
    /*function that takes two QVectors to put the holes in the memory QVector
    one contatins the starting addresses of each hole
    the second contating the size of each hole
    the memory QVector is the first parameter
    it has to update the memory QVector with the holes
    and add data segments to the places already taken*/
    int temp;
    int holes_no = (adress.size());
    //sorting holes according to the adress
    for (int i = 0; i<holes_no; i++) {
        for (int j = i + 1; j<holes_no; j++) {
            if (adress[j]<adress[i]) {
                temp = adress[i];
                adress[i] = adress[j];
                adress[j] = temp;
                temp = size[i];
                size[i] = size[j];
                size[j] = temp;
            }
        }
    }
    //check if the start is data
    if (adress[0] != 0)
    {

        v.push_back(segment("segment0", "parent0", 0, adress[0]));
        v.push_back(segment(adress[0], size[0]));
        for (int i = 1; i<holes_no; i++) {
            v.push_back(segment("segment0", "parent0", adress[i - 1] + size[i - 1], adress[i] - adress[i - 1] - size[i - 1]));
            v.push_back(segment(adress[i], size[i]));


        }
        //add data at the end if last hole doesn't end at the end of the memory
        if ((adress[holes_no - 1] + size[holes_no - 1])<total) {

            v.push_back(segment("segment0", "parent0", adress[holes_no - 1] + size[holes_no - 1], total - adress[holes_no - 1] - size[holes_no - 1]));

        }

    }
    //check if the start is hole
    else {

        v.push_back(segment(adress[0], size[0]));
        for (int i = 1; i<holes_no; i++) {
            v.push_back(segment("segment0", "parent0", adress[i - 1] + size[i - 1], adress[i] - adress[i - 1] - size[i - 1]));
            v.push_back(segment(adress[i], size[i]));
        }
        //add data at the end if last hole doesn't end at the end of the memory
        if ((adress[holes_no - 1] + size[holes_no - 1])<total) {

            v.push_back(segment("segment0", "parent0", adress[holes_no - 1] + size[holes_no - 1], total - adress[holes_no - 1] - size[holes_no - 1]));

        }

    }

}


