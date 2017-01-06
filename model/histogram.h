#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <iostream>

#include <QtCore/QObject>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>

#include <nodes/DataModelRegistry>
#include <nodes/NodeDataModel>

class Histogram : public NodeDataModel
{
    Q_OBJECT
public:
    Histogram();

    virtual ~Histogram();

public:

  QString
  caption() const override
  { return QString("Histogram Filter"); }

  static QString
  name() { return QString("Apply Histogram"); }

public:

  void
  save(Properties &p) const override
  {
    p.put("model_name", Histogram::name());
  }

public:

  virtual QString
  modelName() const
  { return QString("Filter Image"); }
  unsigned int
  nPorts(PortType portType) const override;

  NodeDataType
  dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData>
  outData(PortIndex port) override;

  void
  setInData(std::shared_ptr<NodeData> nodeData, PortIndex port) override;

  QWidget *
  embeddedWidget() override { return _widget; }

  bool
  resizable() const override { return true; }

private slots:
  void onSliderChange( int value );

protected:

  bool
  eventFilter(QObject *object, QEvent *event) override;

private:

  QWidget *_widget;
  QLabel * _label;
  QSlider * _slider;


  QHash< int, int> mColorCounter;
  QHash< int, double> mProbabilitydistribution;
  std::shared_ptr<NodeData> _nodeData;

};

#endif // HISTOGRAM_H
