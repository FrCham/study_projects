#ifndef TRACK_H
#define TRACK_H
#include <QTime>
#include<QDataStream>
#include "item.h"

class Track : public Item
{
    QTime last_;
    int rating_;
public:
    Track();
    QString name() const;
    void setName(const QString &n);
    QTime last() const;
    void setLast(const QTime &l);
    int rating() const;
    void setRating(int r);
    QString description() const;
    void setDescription(const QString &d);

    // Item interface
public:
    Track *toTrack();

    // Item interface
public:
    void setParent(Item *par);

};

QDataStream& operator <<(QDataStream&stream, const Track& tr);
QDataStream& operator >>(QDataStream &stream, Track &tr);

#endif // TRACK_H
