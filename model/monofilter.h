#ifndef MONOFILTER_H
#define MONOFILTER_H

#include <iostream>

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

#include <nodes/DataModelRegistry>
#include <nodes/NodeDataModel>

class MonoFilter : public NodeDataModel
{
    Q_OBJECT
public:
    MonoFilter();

    virtual ~MonoFilter() {}

public:

  QString
  caption() const override
  { return QString("Mono Filter"); }

  static QString
  name() { return QString("Apply Mono"); }

public:

  void
  save(Properties &p) const override
  {
    p.put("model_name", MonoFilter::name());
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
  embeddedWidget() override { return _label; }

  bool
  resizable() const override { return true; }

protected:

  bool
  eventFilter(QObject *object, QEvent *event) override;

private:

  QLabel * _label;

  std::shared_ptr<NodeData> _nodeData;

};

#endif // MONOFILTER_H
