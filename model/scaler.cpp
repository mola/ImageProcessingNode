#include "scaler.h"

#include <QtCore/QEvent>
#include <QtCore/QDir>

#include <nodes/DataModelRegistry>
#include <math.h>
#include <QGridLayout>

#include "PixmapData.hpp"

Scaler::Scaler()
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

    mM1 = new QSpinBox();
    layout->addWidget( mM1 , 0, 0, 1, 1);
    connect( mM1, SIGNAL(valueChanged(int)), SLOT(valueChanged(int)) );
    mM1->setMaximum( 1024 );

    mM2 = new QSpinBox();
    layout->addWidget( mM2 , 0, 1, 1,1);
    connect( mM2, SIGNAL(valueChanged(int)), SLOT(valueChanged(int)) );
    mM2->setMaximum( 1024 );

    layout->addWidget(_label , 1 , 0, 2, 1);


}

unsigned int Scaler::nPorts(PortType portType) const
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

NodeDataType Scaler::dataType(PortType portType, PortIndex portIndex) const
{
    return PixmapData().type();
}

std::shared_ptr<NodeData> Scaler::outData(PortIndex port)
{
    return _nodeData;
}

void Scaler::setInData(std::shared_ptr<NodeData> nodeData, PortIndex port)
{
    _nodeData = nodeData;

    if ( nodeData)
    {
      auto d = std::dynamic_pointer_cast<PixmapData>(_nodeData);

      QImage pix = d->sourceImage();
      QImage res = QImage(pix.width(), pix.height(), pix.format());

      QPixmap pixmap;
      pixmap = pixmap.fromImage(pix.scaled(mM1->value(),mM2->value(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

      res = pixmap.toImage();

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

bool Scaler::eventFilter(QObject *object, QEvent *event)
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

void Scaler::valueChanged(int value)
{
    std::cout <<"DEBUG " << value << std::endl;
    auto d = std::dynamic_pointer_cast<PixmapData>(_nodeData);

    QImage pix = d->sourceImage();
    QImage res = QImage(pix.width(), pix.height(), pix.format());

    QPixmap pixmap;
    pixmap = pixmap.fromImage(pix.scaled(mM1->value(),mM2->value(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

    res = pixmap.toImage();

    d->setImage( res );

    int w = _label->width();
    int h = _label->height();

    _label->setPixmap(d->pixmap().scaled(w, h, Qt::KeepAspectRatio));

    emit dataUpdated(0);
}
