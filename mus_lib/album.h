#ifndef ALBUM_H
#define ALBUM_H
#pragma once
#include<QString>
#include<QPixmap>
#include <QList>
#include "track.h"

class Album : public Item
{
    QString genre_;
    QPixmap image_;
    int year_;
public:
    Album();

    void setName(const QString &n);
    void setYear(int y);
    void setImage(const QPixmap &img);
    void setDescription(const QString &d);
    void setGenre(const QString &g);

    int getYear() const;
    QString getGenre() const;
    QString getDescription() const;
    QPixmap getImage() const;


    // Item interface
public:
    Album *toAlbum();

    // Item interface
public:
    void setParent(Item *par);
    void insertChild(Item *ch, int pos=0);
};


QDataStream& operator <<(QDataStream&stream, const Album& alb);
QDataStream& operator >>(QDataStream &stream, Album &alb);


#endif // ALBUM_H
