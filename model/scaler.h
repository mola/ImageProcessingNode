#ifndef SCALER_H
#define SCALER_H

#include <iostream>

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

#include <nodes/DataModelRegistry>
#include <nodes/NodeDataModel>
#include <QSpinBox>

class Scaler : public NodeDataModel
{
    Q_OBJECT
public:
    Scaler();

    virtual ~Scaler() {}

public:

  QString
  caption() const override
  { return QString("Scaler"); }

  static QString
  name() { return QString("Apply Scale"); }

public:

  void
  save(Properties &p) const override
  {
    p.put("model_name", Scaler::name());
  }

public:

  virtual QString
  modelName() const
  { return QString("Scale Image"); }
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
  void valueChanged(int value);

protected:

  bool
  eventFilter(QObject *object, QEvent *event) override;

private:

  QLabel * _label;

  std::shared_ptr<NodeData> _nodeData;

  QWidget *_widget;

  QSpinBox *mM1;
  QSpinBox *mM2;
};

#endif // Scaler_H
