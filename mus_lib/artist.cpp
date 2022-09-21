#include "artist.h"
#include "album.h"
Artist::Artist()
{

}

QString Artist::name() const
{
    return name_;
}

void Artist::setName(const QString &n)
{
    name_=n;
}

QString Artist::country() const
{
    return country_;
}

void Artist::setCountry(const QString &c)
{
    country_=c;
}

QString Artist::description() const
{
    return description_;
}

void Artist::setDescription(const QString &d)
{
    description_=d;
}

QPixmap Artist::image() const
{
    return image_;
}

void Artist::setImage(const QPixmap &img)
{
    image_=img;
}

Artist *Artist::toArtist()
{
    return this;
}

void Artist::insertChild(Item *ch, int pos)
{
    if(ch->toAlbum()!=NULL){
        children_.insert(pos,ch);
        ch->setParent(this);
    }
}

QDataStream &operator <<(QDataStream &stream, const Artist &artist)
{
    stream << artist.name()
           << artist.image()
           << artist.country()
           << artist.description();
    stream << artist.childCount();
    for(int i=0; i < artist.childCount(); i++)
    {
        Album const* album = artist.childAt(i)->toAlbum();
        if (album) stream << *album;
    }
    return stream;
}

QDataStream &operator >>(QDataStream &stream, Artist &artist)
{
    QString name;
    QPixmap image;
    QString description;
    QString country;
    int album_count;
    Album *a;

    stream >> name
           >> image
           >> country
           >> description;
    artist.setName(name);
    artist.setCountry(country);
    artist.setImage(image);
    artist.setDescription(description);

    stream >> album_count;
    for (int i =0; i<album_count; i++)
    {
        a = new Album();
        stream >> *a;
        artist.insertChild(a,i);
    }
    return stream;
}
