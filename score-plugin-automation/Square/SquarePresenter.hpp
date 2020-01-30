#pragma once
#include <Automation/Commands/AutomationCommandFactory.hpp>
#include <Device/Address/AddressSettings.hpp>
#include <Process/LayerPresenter.hpp>

#include <score/model/path/PathSerialization.hpp>

#include <Square/SquareModel.hpp>

namespace Square
{
class ChangeSquare : public score::Command
{
  SCORE_COMMAND_DECL(
      Automation::CommandFactoryName(),
      ChangeSquare,
      "ChangeSquare")
public:
  ChangeSquare(
      const ProcessModel& autom,
      const ossia::nodes::spline_data& newval)
      : m_path{autom}, m_old{autom.spline()}, m_new{newval}
  {
  }

public:
  void undo(const score::DocumentContext& ctx) const override
  {
    m_path.find(ctx).setSquare(m_old);
  }
  void redo(const score::DocumentContext& ctx) const override
  {
    m_path.find(ctx).setSquare(m_new);
  }

protected:
  void serializeImpl(DataStreamInput& s) const override
  {
    s << m_path << m_old << m_new;
  }
  void deserializeImpl(DataStreamOutput& s) override
  {
    s >> m_path >> m_old >> m_new;
  }

private:
  Path<ProcessModel> m_path;
  ossia::nodes::spline_data m_old, m_new;
};

class View;
class Presenter : public Process::LayerPresenter
{
public:
  explicit Presenter(
      const Square::ProcessModel& model,
      Square::View* view,
      const Process::ProcessPresenterContext& ctx,
      QObject* parent);

  void setWidth(qreal width, qreal defaultWidth) override;
  void setHeight(qreal height) override;

  void putToFront() override;
  void putBehind() override;

  void on_zoomRatioChanged(ZoomRatio) override;

  void parentGeometryChanged() override;

  const Square::ProcessModel& model() const override;
  const Id<Process::ProcessModel>& modelId() const override;

private:
  const Square::ProcessModel& m_layer;
  View* m_view{};
  ZoomRatio m_zoomRatio{};
};
}
