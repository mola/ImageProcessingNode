#pragma once

#include <QtGui/QImage>
#include <QtGui/QPixmap>

#include <nodes/NodeDataModel>

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class PixmapData : public NodeData
{
public:

  PixmapData() {}

  PixmapData(QImage const &pixmap)
    : _pixmap(pixmap), _SourceImage(pixmap)
  {}

  NodeDataType
  type() const override
  {
    //       id      name
    return {"pixmap", "P"};
  }

  QPixmap
  pixmap() const { return QPixmap::fromImage( _pixmap); }

  QImage
  image() const { return _pixmap; }

  QImage
  sourceImage() const { return _SourceImage; }

  void setImage(QImage image) { _pixmap = image; }
  void setSourceImage(QImage image) { _SourceImage = image; }
private:

  QImage _SourceImage;
  QImage _pixmap;
};
