#pragma once
#include <string>
#include <string_view>
#include "olang/runtime/agents/Capability.h"

namespace olang::runtime {

enum class AgentKind : uint8_t { VIRTUAL, PHYSICAL, ATOMIC };

class Agent {
public:
  Agent(std::string name, AgentKind kind, Capability caps) noexcept
      : name_(std::move(name)), kind_(kind), caps_(caps) {}
  virtual ~Agent() = default;
  Agent(const Agent&) = delete; Agent& operator=(const Agent&) = delete;
  Agent(Agent&&) = default;     Agent& operator=(Agent&&) = default;

  [[nodiscard]] std::string_view name()  const noexcept { return name_; }
  [[nodiscard]] AgentKind        kind()  const noexcept { return kind_; }
  [[nodiscard]] Capability       caps()  const noexcept { return caps_; }

  virtual void initialize()    = 0;
  virtual void shutdown() noexcept = 0;

  void require(Capability cap, std::string_view op) const {
    requireCapability(caps_, cap, op);
  }

protected:
  std::string name_; AgentKind kind_; Capability caps_;
};

} // namespace olang::runtime
