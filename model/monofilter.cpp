#include "monofilter.h"

#include <QtCore/QEvent>
#include <QtCore/QDir>

#include <nodes/DataModelRegistry>

#include "PixmapData.hpp"

MonoFilter::MonoFilter()
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

unsigned int MonoFilter::nPorts(PortType portType) const
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

NodeDataType MonoFilter::dataType(PortType portType, PortIndex portIndex) const
{
    return PixmapData().type();
}

std::shared_ptr<NodeData> MonoFilter::outData(PortIndex port)
{
    return _nodeData;
}

void MonoFilter::setInData(std::shared_ptr<NodeData> nodeData, PortIndex port)
{
    _nodeData = nodeData;

    if ( nodeData)
    {
      auto d = std::dynamic_pointer_cast<PixmapData>(_nodeData);

      QImage pix = d->image();
      QImage res = QImage(pix.width(), pix.height(), pix.format());

      for (int x=0; x<pix.width(); x++)
          for (int y=0; y<pix.height(); y++)
          {
              QColor a = pix.pixelColor( x,y);
              int c= (a.red()+a.blue()+a.green())/3;
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

bool MonoFilter::eventFilter(QObject *object, QEvent *event)
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
