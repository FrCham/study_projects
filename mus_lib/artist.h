#ifndef ARTIST_H
#define ARTIST_H
#pragma once
#include <QString>
#include <QPixmap>
#include <QList>
#include "album.h"

class Artist : public Item
{
    QString country_;
    QPixmap image_;
public:
    Artist();
    QString name() const;
    void setName(const QString &n);
    QString country() const;
    void setCountry(const QString &c);
    QString description() const;
    void setDescription(const QString &d);
    QPixmap image() const;
    void setImage(const QPixmap &img);

    // Item interface
public:
    Artist *toArtist();

    // Item interface
public:
    void insertChild(Item *ch, int pos=0);
};


QDataStream& operator <<(QDataStream&stream, const Artist& artist);

QDataStream& operator >>(QDataStream &stream, Artist &artist);


#endif // ARTIST_H
