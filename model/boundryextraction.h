#ifndef BOUNDRYEXTRACTION_H
#define BOUNDRYEXTRACTION_H

#include <iostream>

#include <QtCore/QObject>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>

#include <nodes/DataModelRegistry>
#include <nodes/NodeDataModel>

class BoundryExtraction : public NodeDataModel
{
    Q_OBJECT
public:
    BoundryExtraction();

    virtual ~BoundryExtraction();

public:

  QString
  caption() const override
  { return QString("Boundry Extraction"); }

  static QString
  name() { return QString("Do Boundry Extraction"); }

public:

  void
  save(Properties &p) const override
  {
    p.put("model_name", BoundryExtraction::name());
  }

public:

  virtual QString
  modelName() const
  { return QString("Boundry Extraction"); }
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

  QWidget *_widget;
  QLabel * _label;

  std::shared_ptr<NodeData> _nodeData;

};

#endif // BOUNDRYEXTRACTION_H
