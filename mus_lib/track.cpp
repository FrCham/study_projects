#include "track.h"

Track::Track()
{

}

QString Track::name() const
{
    return name_;
}

void Track::setName(const QString &n)
{
    name_=n;
}

QTime Track::last() const
{
    return last_;
}

void Track::setLast(const QTime &l)
{
    last_=l;
}

int Track::rating() const
{
    return rating_;
}

void Track::setRating(int r)
{
    rating_=r;
}

QString Track::description() const
{
    return description_;
}

void Track::setDescription(const QString &d)
{
    description_=d;
}

Track *Track::toTrack()
{
    return this;
}

void Track::setParent(Item *par)
{
    if(par==0)
        parent_=0;
    else
        if(par->toAlbum()!=0)
            parent_=par;
}

QDataStream &operator <<(QDataStream &stream, const Track &tr)
{
    stream << tr.name()
           << tr.last()
           << tr.rating()
           << tr.description();
    return stream;
}

QDataStream &operator >>(QDataStream &stream, Track &tr)
{
    QString name;
    QTime last;
    QString description;
    int rating;

    stream >> name
           >> last
           >> rating
           >> description;
    tr.setName(name);
    tr.setLast(last);
    tr.setRating(rating);
    tr.setDescription(description);
    return stream;
}
