/*
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 * Modifications Copyright (c) Facebook, Inc.
 */

#include "lazy_tensor_core/csrc/ops/adaptive_avg_pool3d.h"

#include "lazy_tensor_core/csrc/compiler/node_lowering.h"
#include "lazy_tensors/computation_client/debug_macros.h"
#include "lazy_tensors/computation_client/util.h"

namespace torch_lazy_tensors {
namespace ir {
namespace ops {

AdaptiveAvgPool3d::AdaptiveAvgPool3d(const Value& input, std::vector<int64_t> output_size)
    : Node(ir::OpKind(at::aten::adaptive_avg_pool3d), {input},
           /*num_outputs=*/1, lazy_tensors::util::MHash(output_size)),
      output_size_(std::move(output_size)) {
  SetShapeDeferred([&]() { return compiler::NodeLowering::Get()->Infer(this); });
}

NodePtr AdaptiveAvgPool3d::Clone(OpList operands) const {
  return MakeNode<AdaptiveAvgPool3d>(operands.at(0), output_size_);
}

std::string AdaptiveAvgPool3d::ToString() const {
  std::stringstream ss;
  ss << Node::ToString() << ", output_size=(" << absl::StrJoin(output_size_, ", ") << ")";
  return ss.str();
}

}  // namespace ops
}  // namespace ir
}  // namespace torch_lazy_tensors
