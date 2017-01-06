#ifndef SPATIALFILTER_H
#define SPATIALFILTER_H

#include "node/NodeDataModel.hpp"
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QDoubleSpinBox>

#include <iostream>
#include <nodes/DataModelRegistry>


class SpatialFilter : public NodeDataModel
{
    Q_OBJECT

public:
    SpatialFilter();

    virtual ~SpatialFilter() {}

public:

  QString
  caption() const override
  { return QString("Spatial Filter"); }

  static QString
  name() { return QString("Apply Spatial"); }

public:

  void
  save(Properties &p) const override
  {
    p.put("model_name", SpatialFilter::name());
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

protected:

  bool
  eventFilter(QObject *object, QEvent *event) override;
private slots:
  void valueChanged(double value);
private:

  QLabel * _label;

  std::shared_ptr<NodeData> _nodeData;

  QWidget *_widget;

  QDoubleSpinBox *mM1;
  QDoubleSpinBox *mM2;
  QDoubleSpinBox *mM3;
  QDoubleSpinBox *mM4;
  QDoubleSpinBox *mM5;
  QDoubleSpinBox *mM6;
  QDoubleSpinBox *mM7;
  QDoubleSpinBox *mM8;
  QDoubleSpinBox *mM9;
};

#endif // SPATIALFILTER_H
