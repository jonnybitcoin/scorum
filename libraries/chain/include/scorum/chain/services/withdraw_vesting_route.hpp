#pragma once

#include <scorum/chain/services/dbs_base.hpp>

namespace scorum {
namespace chain {

class withdraw_vesting_route_object;

struct withdraw_vesting_route_service_i
{
    virtual bool is_exists(account_id_type from, account_id_type to) const = 0;

    virtual const withdraw_vesting_route_object& get(account_id_type from, account_id_type to) const = 0;

    virtual void remove(const withdraw_vesting_route_object& obj) = 0;

    virtual void create(account_id_type from, account_id_type to, uint16_t percent, bool auto_vest) = 0;

    virtual void update(const withdraw_vesting_route_object& obj,
                        account_id_type from,
                        account_id_type to,
                        uint16_t percent,
                        bool auto_vest)
        = 0;

    virtual uint16_t total_percent(account_id_type from) const = 0;
};

class dbs_withdraw_vesting_route : public dbs_base, public withdraw_vesting_route_service_i
{
    friend class dbservice_dbs_factory;

protected:
    explicit dbs_withdraw_vesting_route(database& db);

public:
    virtual bool is_exists(account_id_type from, account_id_type to) const override;

    virtual const withdraw_vesting_route_object& get(account_id_type from, account_id_type to) const override;

    virtual void remove(const withdraw_vesting_route_object& obj) override;

    virtual void create(account_id_type from, account_id_type to, uint16_t percent, bool auto_vest) override;

    virtual void update(const withdraw_vesting_route_object& obj,
                        account_id_type from,
                        account_id_type to,
                        uint16_t percent,
                        bool auto_vest) override;

    virtual uint16_t total_percent(account_id_type from) const override;
};

} // namespace chain
} // namespace scorum
