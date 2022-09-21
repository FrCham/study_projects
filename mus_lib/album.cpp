#include "album.h"

Album::Album()
{

}

void Album::setName(const QString &n)
{
    name_=n;
}

void Album::setYear(int y)
{
    year_=y;
}

void Album::setImage(const QPixmap &img)
{
    image_=img;
}

void Album::setDescription(const QString &d)
{
    description_=d;
}

void Album::setGenre(const QString &g)
{
    genre_=g;
}

int Album::getYear() const
{
    return year_;
}

QString Album::getGenre() const
{
    return genre_;
}

QString Album::getDescription() const
{
    return description_;
}

QPixmap Album::getImage() const
{
    return image_;
}

Album *Album::toAlbum()
{
    return this;
}

void Album::setParent(Item *par)
{
    if(par==0)
        parent_=0;
    else
        if(par->toArtist()!=0)
            parent_=par;
}

void Album::insertChild(Item *ch, int pos)
{
    if(ch->toTrack()!=NULL){
        children_.insert(pos,ch);
        ch->setParent(this);
    }
}

QDataStream &operator <<(QDataStream &stream, const Album &alb)
{
    stream << alb.name()
           << alb.getImage()
           << alb.getGenre()
           << alb.getYear()
           << alb.getDescription();
    stream << alb.childCount();
    for(int i=0; i < alb.childCount(); i++)
    {
        Track *Track = alb.childAt(i)->toTrack();
        if (Track) stream << *Track;
    }
    return stream;
}

QDataStream &operator >>(QDataStream &stream, Album &alb)
{
    QString name;
    QPixmap cover;
    QString genre;
    int year;
    QString description;
    int Track_count;
    Track *sng;

    stream >> name
           >> cover
           >> genre
           >> year
           >> description;
    alb.setName(name);
    alb.setImage(cover);
    alb.setGenre(genre);
    alb.setYear(year);
    alb.setDescription(description);


    stream >> Track_count;
    for (int i =0; i<Track_count; i++)
    {
        sng = new Track();
        stream >> *sng;
        alb.insertChild(sng, i);
    }
    return stream;
}
