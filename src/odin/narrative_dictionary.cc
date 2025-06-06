#include "odin/narrative_dictionary.h"
#include "midgard/logging.h"

#include <boost/property_tree/ptree.hpp>

namespace {

// Read array and return as a vector
template <typename T>
std::vector<T> as_vector(boost::property_tree::ptree const& pt,
                         boost::property_tree::ptree::key_type const& key) {
  std::vector<T> items;
  for (const auto& item : pt.get_child(key)) {
    items.push_back(item.second.get_value<T>());
  }
  return items;
}

// Read key/values and return as an unordered_map
template <typename K, typename V>
std::unordered_map<K, V> as_unordered_map(boost::property_tree::ptree const& pt,
                                          boost::property_tree::ptree::key_type const& key) {
  std::unordered_map<K, V> items;
  for (const auto& item : pt.get_child(key)) {
    items.emplace(item.first, item.second.get_value<V>());
  }
  return items;
}

} // namespace

namespace valhalla {
namespace odin {

NarrativeDictionary::NarrativeDictionary(const std::string& language_tag,
                                         const boost::property_tree::ptree& narrative_pt) {
  this->language_tag = language_tag;
  Load(narrative_pt);
}

void NarrativeDictionary::Load(const boost::property_tree::ptree& narrative_pt) {

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate posix_locale...");
  // Populate posix locale
  posix_locale = narrative_pt.get<std::string>(kPosixLocaleKey, "en_US.UTF-8");
  try {
    locale = std::locale(posix_locale.c_str());
  } catch (...) {
    LOG_TRACE("Using the default locale because a locale was not found for: " + posix_locale);
  }

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate start_subset...");
  // Populate start_subset
  Load(start_subset, narrative_pt.get_child(kStartKey));

  LOG_TRACE("Populate start_verbal_subset...");
  // Populate start_verbal_subset
  Load(start_verbal_subset, narrative_pt.get_child(kStartVerbalKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate destination_subset...");
  // Populate destination_subset
  Load(destination_subset, narrative_pt.get_child(kDestinationKey));

  LOG_TRACE("Populate destination_verbal_alert_subset...");
  // Populate destination_verbal_alert_subset
  Load(destination_verbal_alert_subset, narrative_pt.get_child(kDestinationVerbalAlertKey));

  LOG_TRACE("Populate destination_verbal_subset...");
  // Populate destination_verbal_subset
  Load(destination_verbal_subset, narrative_pt.get_child(kDestinationVerbalKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate becomes_subset...");
  // Populate becomes_subset
  Load(becomes_subset, narrative_pt.get_child(kBecomesKey));

  LOG_TRACE("Populate becomes_verbal_subset...");
  // Populate becomes_verbal_subset
  Load(becomes_verbal_subset, narrative_pt.get_child(kBecomesVerbalKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate continue_subset...");
  // Populate continue_subset
  Load(continue_subset, narrative_pt.get_child(kContinueKey));

  LOG_TRACE("Populate continue_verbal_alert_subset...");
  // Populate continue_verbal_alert_subset
  Load(continue_verbal_alert_subset, narrative_pt.get_child(kContinueVerbalAlertKey));

  LOG_TRACE("Populate continue_verbal_subset...");
  // Populate continue_verbal_subset
  Load(continue_verbal_subset, narrative_pt.get_child(kContinueVerbalKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate bear_subset...");
  // Populate bear_subset
  Load(bear_subset, narrative_pt.get_child(kBearKey));

  LOG_TRACE("Populate bear_verbal_subset...");
  // Populate bear_verbal_subset
  Load(bear_verbal_subset, narrative_pt.get_child(kBearVerbalKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate turn_subset...");
  // Populate turn_subset
  Load(turn_subset, narrative_pt.get_child(kTurnKey));

  LOG_TRACE("Populate turn_verbal_subset...");
  // Populate turn_verbal_subset
  Load(turn_verbal_subset, narrative_pt.get_child(kTurnVerbalKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate sharp_subset...");
  // Populate sharp_subset
  Load(sharp_subset, narrative_pt.get_child(kSharpKey));

  LOG_TRACE("Populate sharp_verbal_subset...");
  // Populate sharp_verbal_subset
  Load(sharp_verbal_subset, narrative_pt.get_child(kSharpVerbalKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate uturn_subset...");
  // Populate uturn_subset
  Load(uturn_subset, narrative_pt.get_child(kUturnKey));

  LOG_TRACE("Populate uturn_verbal_subset...");
  // Populate uturn_verbal_subset
  Load(uturn_verbal_subset, narrative_pt.get_child(kUturnVerbalKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate ramp_straight_subset...");
  // Populate ramp_straight_subset
  Load(ramp_straight_subset, narrative_pt.get_child(kRampStraightKey));

  LOG_TRACE("Populate ramp_straight_verbal_subset...");
  // Populate ramp_straight_verbal_subset
  Load(ramp_straight_verbal_subset, narrative_pt.get_child(kRampStraightVerbalKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate ramp_subset...");
  // Populate ramp_subset
  Load(ramp_subset, narrative_pt.get_child(kRampKey));

  LOG_TRACE("Populate ramp_verbal_subset...");
  // Populate ramp_verbal_subset
  Load(ramp_verbal_subset, narrative_pt.get_child(kRampVerbalKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate exit_subset...");
  // Populate exit_subset
  Load(exit_subset, narrative_pt.get_child(kExitKey));

  LOG_TRACE("Populate exit_verbal_subset...");
  // Populate exit_verbal_subset
  Load(exit_verbal_subset, narrative_pt.get_child(kExitVerbalKey));

  LOG_TRACE("Populate exit_visual_subset...");
  // Populate exit_visual_subset
  Load(exit_visual_subset, narrative_pt.get_child(kExitVisualKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate keep_subset...");
  // Populate keep_subset
  Load(keep_subset, narrative_pt.get_child(kKeepKey));

  LOG_TRACE("Populate keep_verbal_subset...");
  // Populate keep_verbal_subset
  Load(keep_verbal_subset, narrative_pt.get_child(kKeepVerbalKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate keep_to_stay_on_subset...");
  // Populate keep_to_stay_on_subset
  Load(keep_to_stay_on_subset, narrative_pt.get_child(kKeepToStayOnKey));

  LOG_TRACE("Populate keep_to_stay_on_verbal_subset...");
  // Populate keep_to_stay_on_verbal_subset
  Load(keep_to_stay_on_verbal_subset, narrative_pt.get_child(kKeepToStayOnVerbalKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate merge_subset...");
  // Populate merge_subset
  Load(merge_subset, narrative_pt.get_child(kMergeKey));

  LOG_TRACE("Populate merge_verbal_subset...");
  // Populate merge_verbal_subset
  Load(merge_verbal_subset, narrative_pt.get_child(kMergeVerbalKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate enter_roundabout_subset...");
  // Populate enter_roundabout_subset
  Load(enter_roundabout_subset, narrative_pt.get_child(kEnterRoundaboutKey));

  LOG_TRACE("Populate enter_roundabout_verbal_subset...");
  // Populate enter_roundabout_verbal_subset
  Load(enter_roundabout_verbal_subset, narrative_pt.get_child(kEnterRoundaboutVerbalKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate exit_roundabout_subset...");
  // Populate exit_roundabout_subset
  Load(exit_roundabout_subset, narrative_pt.get_child(kExitRoundaboutKey));

  LOG_TRACE("Populate exit_roundabout_verbal_subset...");
  // Populate exit_roundabout_verbal_subset
  Load(exit_roundabout_verbal_subset, narrative_pt.get_child(kExitRoundaboutVerbalKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate enter_ferry_subset...");
  // Populate enter_ferry_subset
  Load(enter_ferry_subset, narrative_pt.get_child(kEnterFerryKey));

  LOG_TRACE("Populate enter_ferry_verbal_subset...");
  // Populate enter_ferry_verbal_subset
  Load(enter_ferry_verbal_subset, narrative_pt.get_child(kEnterFerryVerbalKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate transit_connection_start_subset...");
  // Populate transit_connection_start_subset
  Load(transit_connection_start_subset, narrative_pt.get_child(kTransitConnectionStartKey));

  LOG_TRACE("Populate transit_connection_start_verbal_subset...");
  // Populate transit_connection_start_verbal_subset
  Load(transit_connection_start_verbal_subset,
       narrative_pt.get_child(kTransitConnectionStartVerbalKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate transit_connection_transfer_subset...");
  // Populate transit_connection_transfer_subset
  Load(transit_connection_transfer_subset, narrative_pt.get_child(kTransitConnectionTransferKey));

  LOG_TRACE("Populate transit_connection_transfer_verbal_subset...");
  // Populate transit_connection_transfer_verbal_subset
  Load(transit_connection_transfer_verbal_subset,
       narrative_pt.get_child(kTransitConnectionTransferVerbalKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate transit_connection_destination_subset...");
  // Populate transit_connection_transfer_subset
  Load(transit_connection_destination_subset,
       narrative_pt.get_child(kTransitConnectionDestinationKey));

  LOG_TRACE("Populate transit_connection_destination_verbal_subset...");
  // Populate transit_connection_transfer_verbal_subset
  Load(transit_connection_destination_verbal_subset,
       narrative_pt.get_child(kTransitConnectionDestinationVerbalKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate depart_subset...");
  // Populate depart_subset
  Load(depart_subset, narrative_pt.get_child(kDepartKey));

  LOG_TRACE("Populate depart_verbal_subset...");
  // Populate depart_verbal_subset
  Load(depart_verbal_subset, narrative_pt.get_child(kDepartVerbalKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate arrive_subset...");
  // Populate arrive_subset
  Load(arrive_subset, narrative_pt.get_child(kArriveKey));

  LOG_TRACE("Populate arrive_verbal_subset...");
  // Populate arrive_verbal_subset
  Load(arrive_verbal_subset, narrative_pt.get_child(kArriveVerbalKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate transit_subset...");
  // Populate transit_subset
  Load(transit_subset, narrative_pt.get_child(kTransitKey));

  LOG_TRACE("Populate transit_verbal_subset...");
  // Populate transit_verbal_subset
  Load(transit_verbal_subset, narrative_pt.get_child(kTransitVerbalKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate transit_remain_on_subset...");
  // Populate transit_remain_on_subset
  Load(transit_remain_on_subset, narrative_pt.get_child(kTransitRemainOnKey));

  LOG_TRACE("Populate transit_remain_on_verbal_subset...");
  // Populate transit_remain_on_verbal_subset
  Load(transit_remain_on_verbal_subset, narrative_pt.get_child(kTransitRemainOnVerbalKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate transit_transfer_subset...");
  // Populate transit_transfer_subset
  Load(transit_transfer_subset, narrative_pt.get_child(kTransitTransferKey));

  LOG_TRACE("Populate transit_transfer_verbal_subset...");
  // Populate transit_transfer_verbal_subset
  Load(transit_transfer_verbal_subset, narrative_pt.get_child(kTransitTransferVerbalKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate post_transition_verbal_subset...");
  // Populate post_transition_verbal_subset
  Load(post_transition_verbal_subset, narrative_pt.get_child(kPostTransitionVerbalKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate post_transition_transit_verbal_subset...");
  // Populate post_transition_transit_verbal_subset
  Load(post_transition_transit_verbal_subset,
       narrative_pt.get_child(kPostTransitTransitionVerbalKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate verbal_multi_cue_subset...");
  // Populate verbal_multi_cue_subset
  Load(verbal_multi_cue_subset, narrative_pt.get_child(kVerbalMultiCueKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate approach_verbal_alert_subset...");
  // Populate approach_verbal_alert_subset
  Load(approach_verbal_alert_subset, narrative_pt.get_child(kApproachVerbalAlertKey));

  /////////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate pass_subset...");
  // Populate pass_subset
  Load(pass_subset, narrative_pt.get_child(kPassKey));
  ///////////////////////////////////////////////////////////////////////////
  LOG_TRACE("Populate elevator_subset");
  // Populate elevator_subset
  Load(elevator_subset, narrative_pt.get_child(kElevatorKey));

  LOG_TRACE("Populate steps_subset");
  // Populate steps_subset
  Load(steps_subset, narrative_pt.get_child(kStepsKey));

  LOG_TRACE("Populate escalator_subset");
  // Populate escalator_subset
  Load(escalator_subset, narrative_pt.get_child(kEscalatorKey));

  LOG_TRACE("Populate enter_building_subset");
  // Populate enter_building_subset
  Load(enter_building_subset, narrative_pt.get_child(kEnterBuildingKey));

  LOG_TRACE("Populate exit_building_subset");
  // Populate exit_building_subset
  Load(exit_building_subset, narrative_pt.get_child(kExitBuildingKey));
}

void NarrativeDictionary::Load(PhraseSet& phrase_handle,
                               const boost::property_tree::ptree& phrase_pt) {

  phrase_handle.phrases = as_unordered_map<std::string, std::string>(phrase_pt, kPhrasesKey);
}

void NarrativeDictionary::Load(StartSubset& start_handle,
                               const boost::property_tree::ptree& start_subset_pt) {

  // Populate phrases
  Load(static_cast<PhraseSet&>(start_handle), start_subset_pt);

  // Populate cardinal_directions
  start_handle.cardinal_directions = as_vector<std::string>(start_subset_pt, kCardinalDirectionsKey);

  // Populate empty_street_name_labels
  start_handle.empty_street_name_labels =
      as_vector<std::string>(start_subset_pt, kEmptyStreetNameLabelsKey);
}

void NarrativeDictionary::Load(StartVerbalSubset& start_verbal_handle,
                               const boost::property_tree::ptree& start_verbal_subset_pt) {

  // Populate start_subset items
  Load(static_cast<StartSubset&>(start_verbal_handle), start_verbal_subset_pt);

  // Populate metric_lengths
  start_verbal_handle.metric_lengths =
      as_vector<std::string>(start_verbal_subset_pt, kMetricLengthsKey);

  // Populate us_customary_lengths
  start_verbal_handle.us_customary_lengths =
      as_vector<std::string>(start_verbal_subset_pt, kUsCustomaryLengthsKey);
}

void NarrativeDictionary::Load(DestinationSubset& destination_handle,
                               const boost::property_tree::ptree& destination_subset_pt) {

  // Populate phrases
  Load(static_cast<PhraseSet&>(destination_handle), destination_subset_pt);

  // Populate relative_directions
  destination_handle.relative_directions =
      as_vector<std::string>(destination_subset_pt, kRelativeDirectionsKey);
}

void NarrativeDictionary::Load(ContinueSubset& continue_handle,
                               const boost::property_tree::ptree& continue_subset_pt) {

  // Populate phrases
  Load(static_cast<PhraseSet&>(continue_handle), continue_subset_pt);

  // Populate empty_street_name_labels
  continue_handle.empty_street_name_labels =
      as_vector<std::string>(continue_subset_pt, kEmptyStreetNameLabelsKey);
}

void NarrativeDictionary::Load(ContinueVerbalSubset& continue_verbal_handle,
                               const boost::property_tree::ptree& continue_verbal_subset_pt) {

  // Populate continue_subset items
  Load(static_cast<ContinueSubset&>(continue_verbal_handle), continue_verbal_subset_pt);

  // Populate metric_lengths
  continue_verbal_handle.metric_lengths =
      as_vector<std::string>(continue_verbal_subset_pt, kMetricLengthsKey);

  // Populate us_customary_lengths
  continue_verbal_handle.us_customary_lengths =
      as_vector<std::string>(continue_verbal_subset_pt, kUsCustomaryLengthsKey);
}

void NarrativeDictionary::Load(TurnSubset& turn_handle,
                               const boost::property_tree::ptree& turn_subset_pt) {

  // Populate phrases
  Load(static_cast<PhraseSet&>(turn_handle), turn_subset_pt);

  // Populate relative_directions
  turn_handle.relative_directions = as_vector<std::string>(turn_subset_pt, kRelativeDirectionsKey);

  // Populate empty_street_name_labels
  turn_handle.empty_street_name_labels =
      as_vector<std::string>(turn_subset_pt, kEmptyStreetNameLabelsKey);
}

void NarrativeDictionary::Load(RampSubset& ramp_handle,
                               const boost::property_tree::ptree& ramp_subset_pt) {

  // Populate phrases
  Load(static_cast<PhraseSet&>(ramp_handle), ramp_subset_pt);

  // Populate relative_directions
  ramp_handle.relative_directions = as_vector<std::string>(ramp_subset_pt, kRelativeDirectionsKey);
}

void NarrativeDictionary::Load(KeepSubset& keep_handle,
                               const boost::property_tree::ptree& keep_subset_pt) {

  // Populate ramp_subset items
  Load(static_cast<RampSubset&>(keep_handle), keep_subset_pt);

  // Populate empty_street_name_labels
  keep_handle.empty_street_name_labels =
      as_vector<std::string>(keep_subset_pt, kEmptyStreetNameLabelsKey);
}

void NarrativeDictionary::Load(EnterRoundaboutSubset& enter_roundabout_handle,
                               const boost::property_tree::ptree& enter_roundabout_subset_pt) {

  // Populate phrases
  Load(static_cast<PhraseSet&>(enter_roundabout_handle), enter_roundabout_subset_pt);

  // Populate ordinal_values
  enter_roundabout_handle.ordinal_values =
      as_vector<std::string>(enter_roundabout_subset_pt, kOrdinalValuesKey);

  // Populate empty_street_name_labels
  enter_roundabout_handle.empty_street_name_labels =
      as_vector<std::string>(enter_roundabout_subset_pt, kEmptyStreetNameLabelsKey);
}

void NarrativeDictionary::Load(EnterFerrySubset& enter_ferry_handle,
                               const boost::property_tree::ptree& enter_ferry_subset_pt) {

  // Populate phrases
  Load(static_cast<PhraseSet&>(enter_ferry_handle), enter_ferry_subset_pt);

  // Populate empty_street_name_labels
  enter_ferry_handle.empty_street_name_labels =
      as_vector<std::string>(enter_ferry_subset_pt, kEmptyStreetNameLabelsKey);

  // Populate ferry_label
  enter_ferry_handle.ferry_label = enter_ferry_subset_pt.get<std::string>(kFerryLabelKey);
}

void NarrativeDictionary::Load(TransitConnectionSubset& transit_connection_handle,
                               const boost::property_tree::ptree& transit_connection_subset_pt) {

  // Populate phrases
  Load(static_cast<PhraseSet&>(transit_connection_handle), transit_connection_subset_pt);

  // Populate station_label
  transit_connection_handle.station_label =
      transit_connection_subset_pt.get<std::string>(kStationLabelKey);
}

void NarrativeDictionary::Load(TransitSubset& transit_handle,
                               const boost::property_tree::ptree& transit_subset_pt) {

  // Populate phrases
  Load(static_cast<PhraseSet&>(transit_handle), transit_subset_pt);

  // Populate transit_count_labels
  transit_handle.empty_transit_name_labels =
      as_vector<std::string>(transit_subset_pt, kEmptyTransitNameLabelsKey);
}

void NarrativeDictionary::Load(TransitStopSubset& transit_stop_handle,
                               const boost::property_tree::ptree& transit_stop_subset_pt) {

  // Populate phrases
  Load(static_cast<TransitSubset&>(transit_stop_handle), transit_stop_subset_pt);

  // Populate transit_stop_count_labels
  transit_stop_handle.transit_stop_count_labels =
      as_unordered_map<std::string, std::string>(transit_stop_subset_pt, kTransitStopCountLabelsKey);
}

void NarrativeDictionary::Load(PostTransitionVerbalSubset& post_transition_verbal_handle,
                               const boost::property_tree::ptree& post_transition_verbal_subset_pt) {

  // Populate phrases
  Load(static_cast<PhraseSet&>(post_transition_verbal_handle), post_transition_verbal_subset_pt);

  // Populate metric_lengths
  post_transition_verbal_handle.metric_lengths =
      as_vector<std::string>(post_transition_verbal_subset_pt, kMetricLengthsKey);

  // Populate us_customary_lengths
  post_transition_verbal_handle.us_customary_lengths =
      as_vector<std::string>(post_transition_verbal_subset_pt, kUsCustomaryLengthsKey);

  // Populate empty_street_name_labels
  post_transition_verbal_handle.empty_street_name_labels =
      as_vector<std::string>(post_transition_verbal_subset_pt, kEmptyStreetNameLabelsKey);
}

void NarrativeDictionary::Load(
    PostTransitionTransitVerbalSubset& post_transition_transit_verbal_handle,
    const boost::property_tree::ptree& post_transition_transit_verbal_subset_pt) {

  // Populate phrases
  Load(static_cast<PhraseSet&>(post_transition_transit_verbal_handle),
       post_transition_transit_verbal_subset_pt);

  // Populate transit_stop_count_labels
  post_transition_transit_verbal_handle.transit_stop_count_labels =
      as_unordered_map<std::string, std::string>(post_transition_transit_verbal_subset_pt,
                                                 kTransitStopCountLabelsKey);
}

void NarrativeDictionary::Load(VerbalMultiCueSubset& verbal_multi_cue_handle,
                               const boost::property_tree::ptree& verbal_multi_cue_subset_pt) {

  // Populate phrases
  Load(static_cast<PhraseSet&>(verbal_multi_cue_handle), verbal_multi_cue_subset_pt);

  // Populate metric_lengths
  verbal_multi_cue_handle.metric_lengths =
      as_vector<std::string>(verbal_multi_cue_subset_pt, kMetricLengthsKey);

  // Populate us_customary_lengths
  verbal_multi_cue_handle.us_customary_lengths =
      as_vector<std::string>(verbal_multi_cue_subset_pt, kUsCustomaryLengthsKey);
}

void NarrativeDictionary::Load(ApproachVerbalAlertSubset& approach_verbal_alert_handle,
                               const boost::property_tree::ptree& approach_verbal_alert_subset_pt) {

  // Populate phrases
  Load(static_cast<PhraseSet&>(approach_verbal_alert_handle), approach_verbal_alert_subset_pt);

  // Populate metric_lengths
  approach_verbal_alert_handle.metric_lengths =
      as_vector<std::string>(approach_verbal_alert_subset_pt, kMetricLengthsKey);

  // Populate us_customary_lengths
  approach_verbal_alert_handle.us_customary_lengths =
      as_vector<std::string>(approach_verbal_alert_subset_pt, kUsCustomaryLengthsKey);
}

void NarrativeDictionary::Load(PassSubset& pass_handle,
                               const boost::property_tree::ptree& pass_subset_pt) {

  // Populate phrases
  Load(static_cast<PhraseSet&>(pass_handle), pass_subset_pt);

  // Populate object_labels
  pass_handle.object_labels = as_vector<std::string>(pass_subset_pt, kObjectLabelsKey);
}

void NarrativeDictionary::Load(EnterBuildingSubset& enter_building_handle,
                               const boost::property_tree::ptree& enter_building_subset_pt) {

  // Populate phrases
  Load(static_cast<PhraseSet&>(enter_building_handle), enter_building_subset_pt);

  // Populate empty_street_name_labels
  enter_building_handle.empty_street_name_labels =
      as_vector<std::string>(enter_building_subset_pt, kEmptyStreetNameLabelsKey);
}

void NarrativeDictionary::Load(ExitBuildingSubset& exit_building_handle,
                               const boost::property_tree::ptree& exit_building_subset_pt) {

  // Populate phrases
  Load(static_cast<PhraseSet&>(exit_building_handle), exit_building_subset_pt);

  // Populate empty_street_name_labels
  exit_building_handle.empty_street_name_labels =
      as_vector<std::string>(exit_building_subset_pt, kEmptyStreetNameLabelsKey);
}

const std::locale& NarrativeDictionary::GetLocale() const {
  return locale;
}

const std::string& NarrativeDictionary::GetLanguageTag() const {
  return language_tag;
}

} // namespace odin
} // namespace valhalla
