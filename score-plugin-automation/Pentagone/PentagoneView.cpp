// This is an open source non-commercial project. Dear PVS-Studio, please check
// it. PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <Process/Style/ScenarioStyle.hpp>

#include <QPainter>

#include <Pentagone/PentagoneView.hpp>
#include <cmath>
// Disclaimer:
// Part of the code comes from splineeditor.cpp from
// the Qt project:
// Copyright (C) 2016 The Qt Company Ltd.
// https://github.com/qt/qtdeclarative/blob/dev/tools/qmleasing/splineeditor.cpp
#include <wobjectimpl.h>
W_OBJECT_IMPL(Pentagone::View)
namespace Pentagone
{
View::View(QGraphicsItem* parent) : LayerView{parent}
{
  static_assert(std::is_same<tinyspline::real, qreal>::value, "");
  this->setFlags(
      QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemClipsToShape);
}

ossia::nodes::spline_point View::mapFromCanvas(const QPointF& point) const
{
  return ossia::nodes::spline_point{(double)point.x() / width(),
                                    1. - point.y() / height()};
}

void View::paint_impl(QPainter* p) const
{
  // TODO optimize painting here
  if (m_spline.points.empty())
    return;

  auto& skin = Process::Style::instance();
  QPainter& painter = *p;

  painter.setRenderHint(QPainter::Antialiasing);

  QPen segmt = skin.skin.Base4.main.pen2;

  QPainterPath path;
  auto p0 = m_spl.evaluate(0).result();
  path.moveTo(mapToCanvas(ossia::nodes::spline_point{p0[0], p0[1]}));
  const constexpr auto N = 500;
  for (std::size_t i = 1U; i < N; i++)
  {
    auto pt = m_spl.evaluate(double(i) / N).result();
    path.lineTo(mapToCanvas(ossia::nodes::spline_point{pt[0], pt[1]}));
  }
  painter.strokePath(path, segmt);

  const auto pts = m_spline.points.size();

  // Handle first point
  auto fp = mapToCanvas(m_spline.points[0]);

  const auto pointSize = 3.;

  if (m_clicked && 0 != *m_clicked)
    painter.setBrush(QColor(170, 220, 20));
  else
      painter.setBrush(QColor(170, 220, 220));

  painter.drawEllipse(QRectF{
      fp.x() - pointSize, fp.y() - pointSize, pointSize * 2., pointSize * 2.});

  // Remaining points
  //for (std::size_t i = 4U; i < pts-3; i++)
  for (std::size_t i = 1U; i < pts; i++)
  {
    painter.setPen(skin.skin.Emphasis3.darker.pen2_dotted_square_miter);
    QPointF p = mapToCanvas(m_spline.points[i]);
    painter.drawLine(fp, p);

      if (i != m_clicked)
        painter.setBrush(QColor(170, 220, 20));
      else
        painter.setBrush(QColor(170, 220, 220));

      painter.setPen(skin.TransparentPen());
      painter.drawEllipse(QRectF{
          p.x() - pointSize, p.y() - pointSize, pointSize * 2., pointSize * 2.});

    fp = p;
  }
}

void View::updatePentagone()
{
  m_spl = tinyspline::BSpline{3, 2, m_spline.points.size(), TS_CLAMPED};
  ts_bspline_set_ctrlp(
      m_spl.data(),
      reinterpret_cast<const tinyspline::real*>(m_spline.points.data()),
      m_spl.data());
}

void View::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
  auto btn = e->button();
  if (btn == Qt::LeftButton)
  {
    if ((m_clicked = findControlPoint(e->pos())))
    {
      mouseMoveEvent(e);
    }
    e->accept();
  }
  else if (btn == Qt::RightButton)
  {
    // Delete

    updatePentagone();
  }
}

void View::mouseMoveEvent(QGraphicsSceneMouseEvent* e)
{
  auto p = mapFromCanvas(e->pos());
  if (!m_clicked)
    return;
  const auto mp = *m_clicked;
  const auto N = m_spline.points.size();
  int j;
  for(j=1;j<20;j++){
    if(j==1 ||j==2 || j==3 || j==17|| j==18|| j==19){
      //m_spline.points[j].setColor(QColor(170, 20, 20));
    }
  }

  if(mp==1 ||mp==2 || mp==3 || mp==17|| mp==18|| mp==19)
  //if (mp < N)
  {
    m_spline.points[mp] = p;
    m_spline.points[mp+1] = p;
    m_spline.points[mp+2] = p;

    double distance;
    double new_dist;
    double new_scale;
    double rotation;
    double angle_sup;
    int i;

    double anglefixe = (2*PI)/5;
    int cmpt_point = 0;
    int num_point = 2;
    new_dist = sqrt(pow(p.x()-0.5,2)+pow(p.y()-0.5,2));
    rotation = acos((p.x()-0.5)/new_dist);
    if(p.y()<0.5){
      angle_sup = rotation;
    }else{
      angle_sup = -rotation;
    }

    for(i=1;i<20;i++){
      if((i<mp) ||(i>mp+2)){
        m_spline.points[i]={cos((num_point-2)*anglefixe-angle_sup)*new_dist+0.5,
                            sin((num_point-2)*anglefixe-angle_sup)*new_dist+0.5};
      }
      cmpt_point++;
      if(cmpt_point==3){
        num_point++;
        cmpt_point = 0;
      }
     }


    updatePentagone();
    update();
  }
}

void View::mouseReleaseEvent(QGraphicsSceneMouseEvent* e)
{
  if (m_clicked)
  {
    changed();
    m_clicked = ossia::none;
  }
  e->accept();
}
/*
void View::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
  const auto newPos = mapFromCanvas(event->pos());
  std::size_t splitIndex = 0;
  const std::size_t N = m_spline.points.size();
  for (std::size_t i = 0; i < N - 1; ++i)
  {
    if (m_spline.points[i].x() <= newPos.x())
    {
      splitIndex = i;
    }
    else
    {
      break;
    }
  }
  m_spline.points.insert(m_spline.points.begin() + splitIndex + 1, newPos);

  updateSpline();
  changed();
  update();
}*/

optional<std::size_t> View::findControlPoint(QPointF point)
{
  int pointIndex = -1;
  qreal distance = -1;

  const auto N = m_spline.points.size();
  for (std::size_t i = 0; i < N; ++i)
  {
    qreal d = QLineF{point, mapToCanvas(m_spline.points.at(i))}.length();
    if ((distance < 0 && d < 10) || d < distance)
    {
      distance = d;
      pointIndex = i;
    }
  }

  if (pointIndex != -1)
    return pointIndex;
  return {};
}
}
