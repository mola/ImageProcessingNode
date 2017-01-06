#include "histogram.h"

#include <QtCore/QEvent>
#include <QtCore/QDir>
#include <QVBoxLayout>

#include <nodes/DataModelRegistry>

#include "PixmapData.hpp"

Histogram::Histogram()
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

    _slider = new QSlider(Qt::Horizontal);
    _slider->setMinimum( 0 );
    _slider->setMaximum( 255 );
    _slider->setValue( 128);
    connect( _slider, SIGNAL(valueChanged(int)), SLOT(onSliderChange(int)));

    layout->addWidget(_label);
    layout->addWidget(_slider);
}

Histogram::~Histogram()
{
}

unsigned int Histogram::nPorts(PortType portType) const
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

NodeDataType Histogram::dataType(PortType portType, PortIndex portIndex) const
{
    return PixmapData().type();
}

std::shared_ptr<NodeData> Histogram::outData(PortIndex port)
{
    return _nodeData;
}

void Histogram::setInData(std::shared_ptr<NodeData> nodeData, PortIndex port)
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

      uint TotalPixel = pix.width() * pix.height();

      for (int x=0; x<pix.width(); x++)
          for (int y=0; y<pix.height(); y++)
          {
              QColor a = pix.pixelColor( x,y);
              if (mColorCounter.contains( a.value() ))
                  mColorCounter[a.value()] += 1;
              else
                  mColorCounter[a.value()] = 1;
          }


      QHashIterator<int, int> i( mColorCounter );
       while (i.hasNext()) {
           mProbabilitydistribution[i.key()] = (double)TotalPixel/(double)i.value();
           i.next();
       }


      for (int x=0; x<pix.width(); x++)
          for (int y=0; y<pix.height(); y++)
          {
              QColor a = pix.pixelColor( x,y);
              if (a.red() < _slider->value() )
                  a.setRed(_slider->value() );
              if (a.green() < _slider->value() )
                  a.setGreen(_slider->value() );
              if (a.blue() < _slider->value() )
                  a.setBlue( _slider->value() );

              QColor b ( a.red(), a.green(), a.blue(), 255 );
              res.setPixel(x, y, b.rgba() );
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

void Histogram::onSliderChange(int value)
{
    auto d = std::dynamic_pointer_cast<PixmapData>(_nodeData);
    QImage pix = d->sourceImage();
    QImage res = QImage(pix.width(), pix.height(), pix.format());

    for (int x=0; x<pix.width(); x++)
        for (int y=0; y<pix.height(); y++)
        {
            QColor a = pix.pixelColor( x,y);
            if (a.red() < value )
                a.setRed( value );
            if (a.green() < value )
                a.setGreen( value );
            if (a.blue() < value )
                a.setBlue( value );

            QColor b ( a.red(), a.green(), a.blue(), 255 );
            res.setPixel(x, y, b.rgba() );
        }


    d->setImage( res );

    int w = _label->width();
    int h = _label->height();

    _label->setPixmap(d->pixmap().scaled(w, h, Qt::KeepAspectRatio));

    emit dataUpdated(0);

}

bool Histogram::eventFilter(QObject *object, QEvent *event)
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
