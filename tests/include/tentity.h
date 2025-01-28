#include "doctest/doctest.h"

#include "fsm.h"
#include "entity.h"
#include "message.h"

TEST_SUITE("Entity") {
    using namespace core;
    fsm fsm{};
    
    TEST_CASE("Entity Creation") {
        int id = 0;
        std::string name = "test_entity";
        human h(id, name);

        SUBCASE("id") {
            CHECK_EQ(h.id(), id);
        }
        SUBCASE("name") {
            CHECK_EQ(h.name(), name);
        }
        SUBCASE("Inbox") {
            CHECK_EQ(h.inbox().has_messages(), false);
            CHECK_EQ(h.inbox().messages().size(), 0);
        }

    }

    message_sender ms{};

    TEST_CASE("Entity Manager Creation") {
        human h1{0, "0"}, h2{1, "1"};
        entity_manager em{};
        
        SUBCASE("Empty") {
            
        }
    }

}