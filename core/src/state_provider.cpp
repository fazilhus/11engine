#include "state_provider.h"

#include "state.h"
#include "entity.h"

namespace core {

    state_provider* state_provider::s_instance = nullptr;

    state_provider::state_provider() {
        s_instance = this;
    }

} // namespace core