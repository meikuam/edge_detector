#ifndef FULLY_CONNECTED_LAYER_H
#define FULLY_CONNECTED_LAYER_H

#include "layer.h"

namespace danknet {

template <typename Dtype>
class FullyConectedLayer : public Layer<Dtype> {
 public:
  explicit FullyConectedLayer()
      : Layer<Dtype>() {}

    virtual inline layertype type() const {return Fully_Connected_Layer; }
    virtual void Forward(const vector<Data2d<Dtype>*>& bottom, const vector<Data2d<Dtype>*>& top);
    virtual void Backward(const vector<Data2d<Dtype>*>& top, const vector<Data2d<Dtype>*>& bottom);

    virtual void LayerSetUp(const vector<Data2d<Dtype>*>& bottom, const vector<Data2d<Dtype>*>& top);

private:

};

} // namespace danknet

#endif // FULLY_CONNECTED_LAYER_H
