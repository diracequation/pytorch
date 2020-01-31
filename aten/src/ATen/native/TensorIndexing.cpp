#include <ATen/native/TensorIndexing.h>

namespace at {
namespace indexing {

const Tensor undefined_tensor = Tensor();
const EllipsisIndexType Ellipsis = EllipsisIndexType();

std::ostream& operator<<(std::ostream& stream, const Slice& slice) {
  stream << slice.start() << ":" << slice.stop() << ":" << slice.step();
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const TensorIndex& tensor_index) {
  if (tensor_index.is_none()) {
    stream << "None";
  } else if (tensor_index.is_ellipsis()) {
    stream << "...";
  } else if (tensor_index.is_integer()) {
    stream << tensor_index.integer();
  } else if (tensor_index.is_boolean()) {
    stream << std::boolalpha << tensor_index.boolean();
  } else if (tensor_index.is_slice()) {
    stream << tensor_index.slice();
  } else if (tensor_index.is_tensor()) {
    stream << tensor_index.tensor();
  }
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const std::vector<TensorIndex>& tensor_indices) {
  stream << "(";
  for (size_t i = 0; i < tensor_indices.size(); i++) {
    stream << tensor_indices[i];
    if (i < tensor_indices.size() - 1) stream << ", ";
  }
  stream << ")";
  return stream;
}

} // namespace indexing

Tensor Tensor::index(const ArrayRef<TensorIndex>& indices) const {
  return at::indexing::get_item(*this, indices);
}
Tensor Tensor::index(std::initializer_list<TensorIndex> indices) const {
  return index(ArrayRef<TensorIndex>(indices));
}

Tensor & Tensor::index_put_(const ArrayRef<TensorIndex>& indices, Tensor const & rhs) {
  at::indexing::set_item(*this, indices, rhs);
  return *this;
}
Tensor & Tensor::index_put_(const ArrayRef<TensorIndex>& indices, Tensor && rhs) {
  at::indexing::set_item(*this, indices, rhs);
  return *this;
}
Tensor & Tensor::index_put_(const ArrayRef<TensorIndex>& indices, Scalar v) {
  at::indexing::set_item(*this, indices, v);
  return *this;
}
Tensor & Tensor::index_put_(std::initializer_list<TensorIndex> indices, Tensor const & rhs) {
  return index_put_(ArrayRef<TensorIndex>(indices), rhs);
}
Tensor & Tensor::index_put_(std::initializer_list<TensorIndex> indices, Tensor && rhs) {
  return index_put_(ArrayRef<TensorIndex>(indices), rhs);
}
Tensor & Tensor::index_put_(std::initializer_list<TensorIndex> indices, Scalar v) {
  return index_put_(ArrayRef<TensorIndex>(indices), v);
}

} // namespace at
