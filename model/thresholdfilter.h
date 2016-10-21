#ifndef THRESHOLDFILTER_H
#define THRESHOLDFILTER_H

#include <iostream>

#include <QtCore/QObject>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>

#include <nodes/DataModelRegistry>
#include <nodes/NodeDataModel>

class ThresholdFilter : public NodeDataModel
{
    Q_OBJECT
public:
    ThresholdFilter();

    virtual ~ThresholdFilter();

public:

  QString
  caption() const override
  { return QString("Threshold Filter"); }

  static QString
  name() { return QString("Apply Threshold"); }

public:

  void
  save(Properties &p) const override
  {
    p.put("model_name", ThresholdFilter::name());
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


  std::shared_ptr<NodeData> _nodeData;

};

#endif // THRESHOLDFILTER_H
