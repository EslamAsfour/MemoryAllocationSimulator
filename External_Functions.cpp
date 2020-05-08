// ConsoleApplication23.cpp : Defines the entry point for the console application.
//
#include "External_Functions.h"
#include <QDebug>



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

int bestIndex;
bool best_fit_alloc(QVector<segment>&memory, QVector<QString>names, QVector<int>size, QString parent) {
    QVector<segment> check = memory;
    bool place_is_found = true;
    for (int i = 0; i<names.size(); i++) {
        int bestIndex = -1;
        for (int j = 0; j <memory.size(); j++) {
            if (check[j].hole == true) {
                if (check[j].size >= size[i])
                {

                    if (bestIndex == -1)
                        bestIndex = j;
                    else if (check[bestIndex].size > check[j].size)
                        bestIndex = j;
                }
            }
        }
        if (bestIndex == -1) {
            place_is_found = false;
            break;
        }
        if (check[bestIndex].size == size[i]) {
            check[bestIndex].name = names[i];
            check[bestIndex].hole = false;
            check[bestIndex].parent = parent;
            place_is_found = true;
        }
        else if (check[bestIndex].size > size[i]) {
            int it = bestIndex + 1;
            check[bestIndex].size -= size[i];

            check.insert(check.begin() + it,segment (names[i], parent, (check[bestIndex].address + check[bestIndex].size), size[i]));

            place_is_found = true;
        }
        else {
            place_is_found = false;
        }
    }

    if (place_is_found == false) {
        return false;
    }
    else if (place_is_found == true) {
        memory = check;
    }
    return true;
}


