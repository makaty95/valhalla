#ifndef VALHALLA_SIF_BICYCLECOST_H_
#define VALHALLA_SIF_BICYCLECOST_H_

#include <valhalla/baldr/rapidjson_fwd.h>
#include <valhalla/proto/options.pb.h>
#include <valhalla/sif/dynamiccost.h>

namespace valhalla {
namespace sif {

/**
 * Parses the bicycle cost options from json and stores values in pbf.
 * @param doc The json request represented as a DOM tree.
 * @param costing_options_key A string representing the location in the DOM tree where the costing
 *                            options are stored.
 * @param pbf_costing         A mutable protocol buffer where the parsed json values will be stored.
 */
void ParseBicycleCostOptions(const rapidjson::Document& doc,
                             const std::string& costing_options_key,
                             Costing* pbf_costing);

/**
 * Create a bicyclecost
 * @param  costing pbf with request options.
 */
cost_ptr_t CreateBicycleCost(const Costing& optcostingions);

} // namespace sif
} // namespace valhalla

#endif // VALHALLA_SIF_BICYCLECOST_H_
