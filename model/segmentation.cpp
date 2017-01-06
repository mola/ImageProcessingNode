#include "segmentation.h"

#include <QtCore/QEvent>
#include <QtCore/QDir>
#include <QVBoxLayout>

#include <nodes/DataModelRegistry>

#include "PixmapData.hpp"

Segmentation::Segmentation()
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

Segmentation::~Segmentation()
{
}

unsigned int Segmentation::nPorts(PortType portType) const
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

NodeDataType Segmentation::dataType(PortType portType, PortIndex portIndex) const
{
    return PixmapData().type();
}

std::shared_ptr<NodeData> Segmentation::outData(PortIndex port)
{
    return _nodeData;
}

int Segmentation::fillingNeigbours(QImage *res,int x, int y, QColor parent)
{
    for (int x2=-1; x2<=1; x2++)
    {
        if ( (x+x2) < 0 || (x+x2) > res->width() )
            continue;

        for (int y2=-1; y2<=1; y2++)
        {
            if ( (y+y2) < 0 || (y+y2) > res->height() )
                continue;

            if (x2 ==0 && y2 ==0 )
                continue;

            QColor a = res->pixelColor( x+x2, y+y2);
            if ( (a.value() != 0)  && (a != parent))
            {
                res->setPixelColor( x+x2, y+y2, parent );
                fillingNeigbours( res , x+x2, y+y2 , parent);
            }
        }
    }

    return 0;

}

void Segmentation::setInData(std::shared_ptr<NodeData> nodeData, PortIndex port)
{
//    _nodeData = nodeData;

    if ( nodeData)
    {
      auto inda = std::dynamic_pointer_cast<PixmapData>(nodeData);
      auto d = std::dynamic_pointer_cast<PixmapData>(_nodeData);

      d->setSourceImage( inda->image() );

      computingStarted();
      QImage pix = inda->image();
      QImage res = QImage(pix.width(), pix.height(), pix.format());
      res.fill( 0 );

      QColor colours[10] = {QColor("cyan"), QColor("magenta"), QColor("red"),
                            QColor("darkRed"), QColor("darkCyan"), QColor("darkMagenta"),
                            QColor("green"), QColor("darkGreen"), QColor("yellow"),
                            QColor("blue")};

      int label = 0;
      QColor parentColor;
      for (int x=0; x<pix.width(); x++)
          for (int y=0; y<pix.height(); y++)
          {
              QColor a = pix.pixelColor( x,y);

              if ( a.value() == 0 )
                  continue;

              if (res.pixelColor( x, y).value() !=0 )
                  continue;

              if ( label > 9 )
                  label = 0;

              res.setPixel(x, y, colours[label].rgb() );
              fillingNeigbours ( &res, x , y , colours[label]);
              label ++;

//              int parent = 0;
//              parentColor.setRgb( 0, 0, 0);

//              for (int x2=-1; x2<=1; x2++)
//              {
//                  if ( (x+x2) < 0 || (x+x2) > res.width() )
//                      continue;

//                  for (int y2=-1; y2<=1; y2++)
//                  {
//                      if ( (y+y2) < 0 || (y+y2) > res.height() )
//                          continue;

//                      if (x2 ==0 && y2 ==0 )
//                          continue;

//                      if ( res.pixelColor( x+x2, y+y2).value() != 0 )
//                          if (parentColor.value() == 0 )
//                            parentColor = res.pixelColor( x+x2, y+y2 );
//                  }
//              }

//              if (parentColor.value() != 0 )
//                  res.setPixel(x, y, parentColor.rgb() );
//              else {
//                  label ++;
//                  if ( label > 9 )
//                      label = 0;
//                  res.setPixel(x, y, colours[label].rgb() );
//              }

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

bool Segmentation::eventFilter(QObject *object, QEvent *event)
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
