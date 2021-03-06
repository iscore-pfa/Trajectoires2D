#pragma once
#include <shapes/Circle/CircleMetadata.hpp>
#include <shapes/ShapeModel.hpp>
namespace Circle
{
class ProcessModel
    : public Shapes::ProcessModel
{
  SCORE_SERIALIZE_FRIENDS
  PROCESS_METADATA_IMPL(Circle::ProcessModel)

  W_OBJECT(ProcessModel)

public:
  ProcessModel(
      const TimeVal& duration,
      const Id<Process::ProcessModel>& id,
      QObject* parent);

  using Shapes::ProcessModel::ProcessModel;
  ~ProcessModel() override;
};
}
