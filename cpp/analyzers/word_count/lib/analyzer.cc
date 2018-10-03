#include "analyzer.h"

#include <sstream>
#include <string>
#include <unordered_map>


namespace cloud {

grpc::Status WordCountAnalyzer::analyze(const pb::AnalyzerInput& input,
                                        pb::AnalyzerOutput& output) {
  // Read all words and calculate their count
  std::unordered_map<std::string, size_t> map_of_words;
  auto word_count = 0.;
  std::stringstream stream(input.text());
  for (auto it = std::istream_iterator<std::string>(stream),
            end = std::istream_iterator<std::string>(); it != end; ++it) {
    ++map_of_words[*it];
    ++word_count;
  }

  // Store to vector and sort by word counts
  std::vector<std::pair<size_t, std::string>> vector_of_word_count;
  vector_of_word_count.reserve(map_of_words.size());
  for (const auto& pair : map_of_words) {
    vector_of_word_count.push_back(std::make_pair(pair.second, pair.first));
  }
  std::sort(vector_of_word_count.begin(), vector_of_word_count.end(),
    std::greater<std::pair<size_t, std::string>>());

  // Produce result to output data
  for (const auto& pair : vector_of_word_count) {
    auto add_ptr = output.add_categories();
    add_ptr->set_name(pair.second);
    add_ptr->set_score(pair.first);
    add_ptr->set_normed_score(pair.first / word_count);
  }

  return grpc::Status::OK;
}

} // namespace cloud
