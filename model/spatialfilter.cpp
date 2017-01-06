#include "spatialfilter.h"

#include "PixmapData.hpp"
#include <iostream>

#include <QEvent>
#include <QGridLayout>

SpatialFilter::SpatialFilter()
{
    _nodeData = std::make_shared<PixmapData>();

    _widget = new QWidget();

    QGridLayout *layout = new QGridLayout(_widget);

    _label = new QLabel("Spatial Filter");
    _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    QFont f = _label->font();
    f.setBold(true);
    f.setItalic(true);

    _label->setFont(f);

    _label->installEventFilter(this);


    mM1 = new QDoubleSpinBox();
    mM1->setMinimum( -100 );
    mM1->setMaximum( 100 );
    layout->addWidget( mM1 , 0, 0, 1, 1);
    connect( mM1, SIGNAL(valueChanged(double)), SLOT(valueChanged(double)) );


    mM2 = new QDoubleSpinBox();
    mM2->setMinimum( -100 );
    mM2->setMaximum( 100 );
    layout->addWidget( mM2 , 0, 1, 1,1);
    connect( mM2, SIGNAL(valueChanged(double)), SLOT(valueChanged(double)) );

    mM3 = new QDoubleSpinBox();
    mM3->setMinimum( -100 );
    mM3->setMaximum( 100 );
    layout->addWidget( mM3 , 0, 2, 1,1);
    connect( mM3, SIGNAL(valueChanged(double)), SLOT(valueChanged(double)) );

    mM4 = new QDoubleSpinBox();
    mM4->setMinimum( -100 );
    mM4->setMaximum( 100 );
    layout->addWidget( mM4 , 1, 0, 1,1);
    connect( mM4, SIGNAL(valueChanged(double)), SLOT(valueChanged(double)) );

    mM5 = new QDoubleSpinBox();
    mM5->setMinimum( -100 );
    mM5->setMaximum( 100 );
    layout->addWidget( mM5 , 1, 1,1,1);
    connect( mM5, SIGNAL(valueChanged(double)), SLOT(valueChanged(double)) );

    mM6 = new QDoubleSpinBox();
    mM6->setMinimum( -100 );
    mM6->setMaximum( 100 );
    layout->addWidget( mM6 , 1, 2, 1,1);
    connect( mM6, SIGNAL(valueChanged(double)), SLOT(valueChanged(double)) );

    mM7 = new QDoubleSpinBox();
    mM7->setMinimum( -100 );
    mM7->setMaximum( 100 );
    layout->addWidget( mM7 , 2, 0, 1,1);
    connect( mM7, SIGNAL(valueChanged(double)), SLOT(valueChanged(double)) );

    mM8 = new QDoubleSpinBox();
    mM8->setMinimum( -100 );
    mM8->setMaximum( 100 );
    layout->addWidget( mM8 , 2, 1, 1,1);
    connect( mM8, SIGNAL(valueChanged(double)), SLOT(valueChanged(double)) );

    mM9 = new QDoubleSpinBox();
    mM9->setMinimum( -100 );
    mM9->setMaximum( 100 );
    layout->addWidget( mM9 , 2, 2 ,1 ,1);
    connect( mM9, SIGNAL(valueChanged(double)), SLOT(valueChanged(double)) );

    layout->addWidget(_label , 3 , 0, 3, 3);


}

unsigned int SpatialFilter::nPorts(PortType portType) const
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

NodeDataType SpatialFilter::dataType(PortType portType, PortIndex portIndex) const
{
    return PixmapData().type();
}

std::shared_ptr<NodeData> SpatialFilter::outData(PortIndex port)
{
    return _nodeData;
}

void SpatialFilter::setInData(std::shared_ptr<NodeData> nodeData, PortIndex port)
{
    _nodeData = nodeData;

    if ( nodeData)
    {
      auto d = std::dynamic_pointer_cast<PixmapData>(_nodeData);

      double cor[3][3];
      cor[0][0] = mM1->value();
      cor[0][1] = mM2->value();
      cor[0][2] = mM3->value();
      cor[1][0] = mM4->value();
      cor[1][1] = mM5->value();
      cor[1][2] = mM6->value();
      cor[2][0] = mM7->value();
      cor[2][1] = mM8->value();
      cor[2][2] = mM9->value();
      QImage pix = d->image();
      QImage res = QImage(pix.width(), pix.height(), pix.format());

      for (int x=1; x<pix.width()-1; x++)
          for (int y=1; y<pix.height()-1; y++)
          {
              double med = 0 ;
              int x3 = 0;
              for (int x2=x-1; x2<=x+1; x2++)
              {
                  int y3 = 0;
                  for (int y2=y-1; y2<=y+1; y2++)
                  {
                    QColor a = pix.pixelColor( x2,y2);
                    med += ( (a.red()+a.blue()+a.green())/3 ) * cor[x3][y3];
                    y3++;
                  }
                  x3++;
              }

              int c = med;
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

bool SpatialFilter::eventFilter(QObject *object, QEvent *event)
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

void SpatialFilter::valueChanged(double value)
{
    std::cout <<"DEBUG " << value << std::endl;
    auto d = std::dynamic_pointer_cast<PixmapData>(_nodeData);

    double cor[3][3];
    cor[0][0] = mM1->value();
    cor[0][1] = mM2->value();
    cor[0][2] = mM3->value();
    cor[1][0] = mM4->value();
    cor[1][1] = mM5->value();
    cor[1][2] = mM6->value();
    cor[2][0] = mM7->value();
    cor[2][1] = mM8->value();
    cor[2][2] = mM9->value();

    QImage pix = d->sourceImage();
    QImage res = QImage(pix.width(), pix.height(), pix.format());

    for (int x=1; x<pix.width()-1; x++)
        for (int y=1; y<pix.height()-1; y++)
        {
            double med = 0 ;
            int x3 = 0;
            for (int x2=x-1; x2<=x+1; x2++)
            {
                int y3 = 0;
                for (int y2=y-1; y2<=y+1; y2++)
                {
                  QColor a = pix.pixelColor( x2,y2);
                  med += ( (a.red()+a.blue()+a.green())/3 ) * cor[x3][y3];
                  y3++;
                }
                x3++;
            }

            int c = med;
            QColor b ( c, c, c, 255 );
            res.setPixel(x, y, b.rgba() );
        }

    d->setImage( res );

    int w = _label->width();
    int h = _label->height();

    _label->setPixmap(d->pixmap().scaled(w, h, Qt::KeepAspectRatio));

    emit dataUpdated(0);
}
