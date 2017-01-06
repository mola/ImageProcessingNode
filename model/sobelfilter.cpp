#include "sobelfilter.h"

#include <QtCore/QEvent>
#include <QtCore/QDir>

#include <nodes/DataModelRegistry>
#include <math.h>

#include "PixmapData.hpp"

SobelFilter::SobelFilter()
    :_label(new QLabel("Image will appear here"))
{
    _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    QFont f = _label->font();
    f.setBold(true);
    f.setItalic(true);

    _label->setFont(f);

    _label->setFixedSize(200, 200);

    _label->installEventFilter(this);

}

unsigned int SobelFilter::nPorts(PortType portType) const
{
    unsigned int result = 1;

    switch (portType)
    {
      case PortType::In:
        result = 1;
        break;

      case PortType::Out:
        result = 1;

      default:
        break;
    }

    return result;
}

NodeDataType SobelFilter::dataType(PortType portType, PortIndex portIndex) const
{
    return PixmapData().type();
}

std::shared_ptr<NodeData> SobelFilter::outData(PortIndex port)
{
    return _nodeData;
}

void SobelFilter::setInData(std::shared_ptr<NodeData> nodeData, PortIndex port)
{
    _nodeData = nodeData;

    if ( nodeData)
    {
      auto d = std::dynamic_pointer_cast<PixmapData>(_nodeData);

      QImage pix = d->image();
      QImage res = QImage(pix.width(), pix.height(), pix.format());

      float sobel_x[3][3] = {{-1,0,1},
                 {-2,0,2},
                 {-1,0,1}};

      float sobel_y[3][3] = {{-1,-2,-1},
                 {0,0,0},
                 {1,2,1}};

      for (int x=1; x<pix.width()-1; x++)
          for (int y=1; y<pix.height()-1; y++)
          {

              float pixel_x = 0 ;
              float pixel_y = 0 ;
              int x3 = 0;
              for (int x2=x-1; x2<=x+1; x2++)
              {
                  int y3 = 0;
                  for (int y2=y-1; y2<=y+1; y2++)
                  {
                    QColor a = pix.pixelColor( x2,y2);
                    pixel_x += ( sobel_x[x3][y3] )*( (a.red()+a.blue()+a.green())/3 );
                    pixel_y += ( sobel_y[x3][y3] )*( (a.red()+a.blue()+a.green())/3 );
                    y3++;
                  }
                  x3++;
              }

              float val = sqrt((pixel_x * pixel_x) + (pixel_y * pixel_y));

//              QColor a = pix.pixelColor( x,y);
              int c= val;
              QColor b ( c, c, c, 255 );
              res.setPixel(x, y, b.rgba() );
          }


      d->setImage( res );

      int w = _label->width();
      int h = _label->height();

      _label->setPixmap(d->pixmap().scaled(w, h, Qt::KeepAspectRatio));
    }
    else
    {
      _label->setPixmap(QPixmap());
    }

    emit dataUpdated(0);
}

bool SobelFilter::eventFilter(QObject *object, QEvent *event)
{
    if (object == _label)
    {
      int w = _label->width();
      int h = _label->height();

      if (event->type() == QEvent::Resize)
      {
        auto d = std::dynamic_pointer_cast<PixmapData>(_nodeData);
        if (d)
        {
          _label->setPixmap(d->pixmap().scaled(w, h, Qt::KeepAspectRatio));
        }
      }
    }

    return false;
}
