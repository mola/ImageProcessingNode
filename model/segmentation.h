#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include <iostream>

#include <QtCore/QObject>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>

#include <nodes/DataModelRegistry>
#include <nodes/NodeDataModel>

class Segmentation : public NodeDataModel
{
    Q_OBJECT
public:
    Segmentation();

    virtual ~Segmentation();

public:

  QString
  caption() const override
  { return QString("Segmentation"); }

  static QString
  name() { return QString("Segmentation"); }

public:

  void
  save(Properties &p) const override
  {
    p.put("model_name", Segmentation::name());
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

private:

  int fillingNeigbours(QImage *res, int x , int y, QColor parent );
  QWidget *_widget;
  QLabel * _label;

  std::shared_ptr<NodeData> _nodeData;

};

#endif // SEGMENTATION_H
