
#include <scorum/app/api_context.hpp>
#include <scorum/app/application.hpp>

#include <scorum/protocol/authority.hpp>
#include <scorum/protocol/sign_state.hpp>

#include <scorum/chain/schema/account_objects.hpp>
#include <scorum/chain/database.hpp>

#include <scorum/plugins/auth_util/auth_util_api.hpp>
#include <scorum/plugins/auth_util/auth_util_plugin.hpp>

#include <fc/container/flat.hpp>

namespace scorum {
namespace plugin {
namespace auth_util {

using boost::container::flat_set;

namespace detail {

class auth_util_api_impl
{
public:
    auth_util_api_impl(scorum::app::application& _app);
    void check_authority_signature(const check_authority_signature_params& args,
                                   check_authority_signature_result& result);

    std::shared_ptr<scorum::plugin::auth_util::auth_util_plugin> get_plugin();

    scorum::app::application& app;
};

auth_util_api_impl::auth_util_api_impl(scorum::app::application& _app)
    : app(_app)
{
}

std::shared_ptr<scorum::plugin::auth_util::auth_util_plugin> auth_util_api_impl::get_plugin()
{
    return app.get_plugin<auth_util_plugin>("auth_util");
}

void auth_util_api_impl::check_authority_signature(const check_authority_signature_params& args,
                                                   check_authority_signature_result& result)
{
    std::shared_ptr<chain::database> db = app.chain_database();
    const chain::account_authority_object& acct
        = db->get<chain::account_authority_object, chain::by_account>(args.account_name);
    protocol::authority auth;
    if ((args.level == "posting") || (args.level == "p"))
    {
        auth = protocol::authority(acct.posting);
    }
    else if ((args.level == "active") || (args.level == "a") || (args.level == ""))
    {
        auth = protocol::authority(acct.active);
    }
    else if ((args.level == "owner") || (args.level == "o"))
    {
        auth = protocol::authority(acct.owner);
    }
    else
    {
        FC_ASSERT(false, "invalid level specified");
    }
    flat_set<protocol::public_key_type> signing_keys;
    for (const protocol::signature_type& sig : args.sigs)
    {
        result.keys.emplace_back(fc::ecc::public_key(sig, args.dig, true));
        signing_keys.insert(result.keys.back());
    }

    flat_set<protocol::public_key_type> avail;
    protocol::sign_state ss(signing_keys,
                            [&db](const std::string& account_name) -> const protocol::authority {
                                return protocol::authority(
                                    db->get<chain::account_authority_object, chain::by_account>(account_name).active);
                            },
                            avail);

    bool has_authority = ss.check_authority(auth);
    FC_ASSERT(has_authority);

    return;
}

} // detail

auth_util_api::auth_util_api(const scorum::app::api_context& ctx)
{
    my = std::make_shared<detail::auth_util_api_impl>(ctx.app);
}

void auth_util_api::on_api_startup()
{
}

check_authority_signature_result auth_util_api::check_authority_signature(check_authority_signature_params args)
{
    check_authority_signature_result result;
    my->check_authority_signature(args, result);
    return result;
}
}
}
} // scorum::plugin::auth_util
