#include "boundryextraction.h"

#include <QtCore/QEvent>
#include <QtCore/QDir>
#include <QVBoxLayout>

#include <nodes/DataModelRegistry>

#include "PixmapData.hpp"
#include <math.h>

BoundryExtraction::BoundryExtraction()
    :_label(new QLabel("Image will appear here"))
{

    _nodeData = std::make_shared<PixmapData>();
    _widget = new QWidget();

    QVBoxLayout *layout = new QVBoxLayout(_widget);

    _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    QFont f = _label->font();
    f.setBold(true);
    f.setItalic(true);

    _label->setFont(f);

    _label->installEventFilter(this);

    layout->addWidget(_label);
}

BoundryExtraction::~BoundryExtraction()
{
}

unsigned int BoundryExtraction::nPorts(PortType portType) const
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

NodeDataType BoundryExtraction::dataType(PortType portType, PortIndex portIndex) const
{
    return PixmapData().type();
}

std::shared_ptr<NodeData> BoundryExtraction::outData(PortIndex port)
{
    return _nodeData;
}

void BoundryExtraction::setInData(std::shared_ptr<NodeData> nodeData, PortIndex port)
{
//    _nodeData = nodeData;

    if ( nodeData)
    {
      auto inda = std::dynamic_pointer_cast<PixmapData>(nodeData);
      auto d = std::dynamic_pointer_cast<PixmapData>(_nodeData);

      d->setSourceImage( inda->image() );

      computingStarted();
      QImage pix = inda->image();
      QImage res = inda->image();//QImage(pix.width(), pix.height(), pix.format());
      QImage mini = QImage(pix.width(), pix.height(), pix.format());
      mini.fill(0);

      int boundry[3][3] = {{1,1,1},
                 {1,1,1},
                 {1,1,1}};


      int med = 0 ;
      for (int x=1; x<pix.width()-1; x++)
          for (int y=1; y<pix.height()-1; y++)
          {
              int max = 0 ;
              QColor a;
              for (int x2=-1; x2<=1; x2++)
              {
                  for (int y2=-1; y2<=1; y2++)
                  {
                    if ( boundry[x2+1][y2+1] == 1 )
                    {
                        a = pix.pixelColor( x+x2,y+y2);
                        med = ( (a.red()+a.blue()+a.green())/3 );
                        if ( med  > max  )
                            max = med;
                    }
                  }
              }
                  QColor b ( max, max, max, 255 );
                  mini.setPixel(x, y, b.rgba() );

          }

      for (int x=0; x<pix.width(); x++)
          for (int y=0; y<pix.height(); y++)
          {
            QColor a = pix.pixelColor( x, y);
            QColor b = mini.pixelColor( x, y);
            QRgb c = QRgb( a.rgb() - b.rgb() );
            res.setPixel(x, y, c );
          }

      d->setImage( res );
      computingFinished();

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

bool BoundryExtraction::eventFilter(QObject *object, QEvent *event)
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
