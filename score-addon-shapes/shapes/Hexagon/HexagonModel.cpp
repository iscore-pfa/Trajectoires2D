// This is an open source non-commercial project. Dear PVS-Studio, please check
// it. PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <Process/Dataflow/Port.hpp>

#include <ossia/editor/state/destination_qualifiers.hpp>

#include <math.h>
#include <shapes/Hexagon/HexagonModel.hpp>
#include <shapes/Hexagon/HexagonPresenter.hpp>
#include <wobjectimpl.h>

W_OBJECT_IMPL(Hexagon::ProcessModel)
#define PI 3.14159265359
namespace Hexagon
{
ProcessModel::ProcessModel(
    const TimeVal& duration,
    const Id<Process::ProcessModel>& id,
    QObject* parent)
    : Shapes::ProcessModel{duration,
                            id,
                            Metadata<ObjectKey_k, ProcessModel>::get(),
                            parent}
{

  metadata().setInstanceName(*this);
}

  ProcessModel::~ProcessModel()
  {

  }
  }

  template <>
  void DataStreamReader::read(const Hexagon::ProcessModel& autom)
  {
    read((Shapes::ProcessModel&)autom);
  }

  template <>
  void DataStreamWriter::write(Hexagon::ProcessModel& autom)
  {
    write((Shapes::ProcessModel&)autom);
  }

  template <>
  void JSONObjectReader::read(const Hexagon::ProcessModel& autom)
  {
    read((Shapes::ProcessModel&)autom);
  }

  template <>
  void JSONObjectWriter::write(Hexagon::ProcessModel& autom)
  {
    write((Shapes::ProcessModel&)autom);
  }