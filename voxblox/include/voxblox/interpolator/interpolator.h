#ifndef VOXBLOX_INTERPOLATOR_H_
#define VOXBLOX_INTERPOLATOR_H_

#include <memory>

#include "voxblox/core/common.h"
#include "voxblox/core/layer.h"
#include "voxblox/core/voxel.h"

namespace voxblox {

class Interpolator {
 public:
  typedef std::shared_ptr<Interpolator> Ptr;

  explicit Interpolator(Layer<TsdfVoxel>* tsdf_layer);

  bool getGradient(const Point& pos, Point* grad,
                   const bool interpolate = false) const;

  bool getDistance(const Point& pos, FloatingPoint* distance,
                   bool interpolate = false) const;

  // Without interpolation.
  bool getNearestDistanceAndWeight(const Point& pos, FloatingPoint* distance,
                                   float* weight) const;

 private:
  bool setIndexes(const Point& pos, BlockIndex* block_index,
                  InterpIndexes* voxel_indexes) const;

  void getWeightsVector(const Point& voxel_pos, const Point& pos,
                        InterpVector* weights_vector) const;

  bool getDistancesAndWeights(const BlockIndex& block_index,
                              const InterpIndexes& voxel_indexes,
                              const Point& pos, InterpVector* distances,
                              InterpVector* weights_vector) const;

  bool getInterpDistance(const Point& pos, FloatingPoint* distance) const;

  bool getNearestDistance(const Point& pos, FloatingPoint* distance) const;

  Layer<TsdfVoxel>* tsdf_layer_;
};
}  // namespace voxblox

#endif  // VOXBLOX_INTERPOLATOR_H_