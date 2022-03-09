/*
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 * Modifications Copyright (c) Facebook, Inc.
 */

#pragma once

#include <vector>

#include "lazy_tensor_core/csrc/ir.h"
#include "lazy_tensors/types.h"

namespace torch_lazy_tensors {
namespace ir {
namespace ops {

class Var : public Node {
 public:
  Var(const Value& input, std::vector<int64_t> dimensions, int64_t correction,
      bool keep_reduced_dimensions);

  std::string ToString() const override;

  NodePtr Clone(OpList operands) const override;

  const std::vector<int64_t>& dimensions() const {
    return dimensions_;
  }

  bool keep_reduced_dimensions() const {
    return keep_reduced_dimensions_;
  }

  int64_t correction() const {
    return correction_;
  }

 private:
  std::vector<int64_t> dimensions_;
  int64_t correction_;
  bool keep_reduced_dimensions_;
};

}  // namespace ops
}  // namespace ir
}  // namespace torch_lazy_tensors
