#ifndef EXTERNAL_FUNCTIONS_H
#define EXTERNAL_FUNCTIONS_H

#include <QString>
#include<QVector>

struct segment {
    QString name;//name of the segment
    QString parent;//the name of the process that the segment Belongs to
    bool hole; // true if this segment is a hole (free space)
    int address;
    int size;

    segment(int ad, int s) {
        //constructor to use at adding a new hole
        address = ad;
        size = s;
        hole = true;

    }
    segment(QString n, QString p, int ad, int s) {
        //constructor to use at adding new data segmant
        name = n;
        parent = p;
        address = ad;
        size = s;
        hole = false;
    }
};




void add_holes(QVector<segment>&v, QVector<int> adress, QVector<int> size, int total);
bool first_fit_alloc(QVector<segment>&v, QVector<QString>names, QVector<int>size, QString parent);
bool best_fit_alloc(QVector<segment>&v, QVector<QString>names, QVector<int>size, QString parent);
void de_alloc(QVector<segment>&v, QString proc);
QVector<segment> seg_table(QVector<segment>&v, QString proc);



#endif // EXTERNAL_FUNCTIONS_H
