// This is an open source non-commercial project. Dear PVS-Studio, please check
// it. PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <Process/Dataflow/Port.hpp>

#include <ossia/editor/state/destination_qualifiers.hpp>

#include <math.h>
#include <Hexagon/HexagonModel.hpp>
#include <Hexagon/HexagonPresenter.hpp>
#include <wobjectimpl.h>

W_OBJECT_IMPL(Hexagon::ProcessModel)
#define PI 3.14159265359
namespace Hexagon
{
ProcessModel::ProcessModel(
    const TimeVal& duration,
    const Id<Process::ProcessModel>& id,
    QObject* parent)
    : Process::ProcessModel{duration,
                            id,
                            Metadata<ObjectKey_k, ProcessModel>::get(),
                            parent}
    , outlet{Process::make_outlet(Id<Process::Port>(0), this)}
{

  outlet->type = Process::PortType::Message;
  //points p1 =  ({0., 0.});

  //m_spline.points.push_back({0., 0.});

  //double x = 0.4;
  //double y = 0.075;
  double xCenter = 0.5;
  double yCenter = 0.5;
  double longueur = 0.5;
  double angle = 0;
  double anglefixe = (2*PI)/6;
  //"p2" 2->4
  m_spline.points.push_back({xCenter+ cos(angle+4*anglefixe)*longueur,yCenter+ sin(angle+4*anglefixe)*longueur});
  m_spline.points.push_back({xCenter+ cos(angle+4*anglefixe)*longueur,yCenter+ sin(angle+4*anglefixe)*longueur});
  m_spline.points.push_back({xCenter+ cos(angle+4*anglefixe)*longueur,yCenter+ sin(angle+4*anglefixe)*longueur});
  //"p3" 5->7
  m_spline.points.push_back({xCenter+ cos(angle+5*anglefixe)*longueur,yCenter+ sin(angle+5*anglefixe)*longueur});
  m_spline.points.push_back({xCenter+ cos(angle+5*anglefixe)*longueur,yCenter+ sin(angle+5*anglefixe)*longueur});
  m_spline.points.push_back({xCenter+ cos(angle+5*anglefixe)*longueur,yCenter+ sin(angle+5*anglefixe)*longueur});

  m_spline.points.push_back({xCenter+ cos(angle+6*anglefixe)*longueur,yCenter+ sin(angle+6*anglefixe)*longueur});
  m_spline.points.push_back({xCenter+ cos(angle+6*anglefixe)*longueur,yCenter+ sin(angle+6*anglefixe)*longueur});
  m_spline.points.push_back({xCenter+ cos(angle+6*anglefixe)*longueur,yCenter+ sin(angle+6*anglefixe)*longueur});
  //"p4" 8->10
  m_spline.points.push_back({xCenter+ cos(angle+anglefixe)*longueur,yCenter+ sin(angle+anglefixe)*longueur});
  m_spline.points.push_back({xCenter+ cos(angle+anglefixe)*longueur,yCenter+ sin(angle+anglefixe)*longueur});
  m_spline.points.push_back({xCenter+ cos(angle+anglefixe)*longueur,yCenter+ sin(angle+anglefixe)*longueur});
  //"p5" 11->13
  m_spline.points.push_back({xCenter+ cos(angle+2*anglefixe)*longueur,yCenter+ sin(angle+2*anglefixe)*longueur});
  m_spline.points.push_back({xCenter+ cos(angle+2*anglefixe)*longueur,yCenter+ sin(angle+2*anglefixe)*longueur});
  m_spline.points.push_back({xCenter+ cos(angle+2*anglefixe)*longueur,yCenter+ sin(angle+2*anglefixe)*longueur});
  //"p6" 14->16
  m_spline.points.push_back({xCenter+ cos(angle+3*anglefixe)*longueur,yCenter+ sin(angle+3*anglefixe)*longueur});
  m_spline.points.push_back({xCenter+ cos(angle+3*anglefixe)*longueur,yCenter+ sin(angle+3*anglefixe)*longueur});
  m_spline.points.push_back({xCenter+ cos(angle+3*anglefixe)*longueur,yCenter+ sin(angle+3*anglefixe)*longueur});
  //"p7" 17->19
  m_spline.points.push_back({xCenter+ cos(angle+4*anglefixe)*longueur,yCenter+ sin(angle+4*anglefixe)*longueur});
  m_spline.points.push_back({xCenter+ cos(angle+4*anglefixe)*longueur,yCenter+ sin(angle+4*anglefixe)*longueur});
  m_spline.points.push_back({xCenter+ cos(angle+4*anglefixe)*longueur,yCenter+ sin(angle+4*anglefixe)*longueur});

  init();
  metadata().setInstanceName(*this);
}

ProcessModel::~ProcessModel() {}

void ProcessModel::init()
{
  outlet->setCustomData("Out");
  m_outlets.push_back(outlet.get());
  connect(
      outlet.get(),
      &Process::Port::addressChanged,
      this,
      [=](const State::AddressAccessor& arg) {
        addressChanged(arg);
        prettyNameChanged();
        unitChanged(arg.qualifiers.get().unit);
      });
}

QString ProcessModel::prettyName() const noexcept
{
  return address().toString();
}

void ProcessModel::setDurationAndScale(const TimeVal& newDuration) noexcept
{
  // We only need to change the duration.
  setDuration(newDuration);
}

void ProcessModel::setDurationAndGrow(const TimeVal& newDuration) noexcept
{
  setDuration(newDuration);
}

void ProcessModel::setDurationAndShrink(const TimeVal& newDuration) noexcept
{
  setDuration(newDuration);
}

bool ProcessModel::contentHasDuration() const noexcept
{
  return true;
}

TimeVal ProcessModel::contentDuration() const noexcept
{
  return duration();
}

::State::AddressAccessor ProcessModel::address() const
{
  return outlet->address();
}

void ProcessModel::setAddress(const ::State::AddressAccessor& arg)
{
  outlet->setAddress(arg);
}

State::Unit ProcessModel::unit() const
{
  return outlet->address().qualifiers.get().unit;
}

void ProcessModel::setUnit(const State::Unit& u)
{
  if (u != unit())
  {
    auto addr = outlet->address();
    addr.qualifiers.get().unit = u;
    outlet->setAddress(addr);
    prettyNameChanged();
    unitChanged(u);
  }
}
/// Point ///
/*
template <>
void DataStreamReader::read(const ossia::nodes::spline_point& autom)
{
  m_stream << autom.m_x << autom.m_y;
}

template <>
void DataStreamWriter::write(ossia::nodes::spline_point& autom)
{
  m_stream >> autom.m_x >> autom.m_y;
}
template <>
void JSONValueReader::read(const ossia::nodes::spline_point& autom)
{
  val = QJsonArray{autom.x(), autom.y()};
}

template <>
void JSONValueWriter::write(ossia::nodes::spline_point& autom)
{
  auto arr = val.toArray();
  autom.m_x = arr[0].toDouble();
  autom.m_y = arr[1].toDouble();
}

/// Data ///

template <>
void DataStreamReader::read(const ossia::nodes::spline_data& autom)
{
  m_stream << autom.points;
  insertDelimiter();
}

template <>
void DataStreamWriter::write(ossia::nodes::spline_data& autom)
{
  m_stream >> autom.points;
  checkDelimiter();
}
template <>
void JSONValueReader::read(const ossia::nodes::spline_data& autom)
{
  val = toJsonValueArray(autom.points);
}
template <>
void JSONValueWriter::write(ossia::nodes::spline_data& autom)
{
  autom.points = fromJsonValueArray<std::vector<ossia::nodes::spline_point>>(
      val.toArray());
}
*/
}
using namespace Spline;
template <>
void DataStreamReader::read(const Hexagon::ProcessModel& autom)
{
  m_stream << *autom.outlet << autom.m_spline << autom.m_tween;

  insertDelimiter();
}
template <>
void DataStreamWriter::write(Hexagon::ProcessModel& autom)
{
  autom.outlet = Process::make_outlet(*this, &autom);
  m_stream >> autom.m_spline >> autom.m_tween;

  checkDelimiter();
}

template <>
void JSONObjectReader::read(const Hexagon::ProcessModel& autom)
{
  obj["Outlet"] = toJsonObject(*autom.outlet);
  JSONValueReader v{};
  v.readFrom(autom.m_spline);
  obj["Hexagon"] = v.val;
  obj["Tween"] = autom.tween();
}

template <>
void JSONObjectWriter::write(Hexagon::ProcessModel& autom)
{
  JSONObjectWriter writer{obj["Outlet"].toObject()};
  autom.outlet = Process::make_outlet(writer, &autom);
  if (!autom.outlet)
  {
    autom.outlet = Process::make_outlet(Id<Process::Port>(0), &autom);
    autom.outlet->type = Process::PortType::Message;
    autom.outlet->setAddress(fromJsonObject<State::AddressAccessor>(
        obj[strings.Address].toObject()));
  }

  autom.setTween(obj["Tween"].toBool());
  JSONValueWriter v{};
  v.val = obj["Hexagon"];
  v.writeTo(autom.m_spline);
}
