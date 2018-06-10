#include "gtest/gtest.h"

#include "unique_inputs_counter.h"


namespace cloud {

class UniqueInputsCounterTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    input1_.set_id("id-1");
    input2_.set_id("id-2");
  }

  UniqueInputsCounter unique_inputs_counter_;
  pb::AnalyzerInput input1_;
  pb::AnalyzerInput input2_;
};

TEST_F(UniqueInputsCounterTest, OneInput) {
  auto result = unique_inputs_counter_.updateAndAnalyze(input1_);

  EXPECT_TRUE(result.new_input_);
  EXPECT_EQ(result.unique_count_, 1);
}

TEST_F(UniqueInputsCounterTest, MultiInput) {
  unique_inputs_counter_.updateAndAnalyze(input1_);

  auto result = unique_inputs_counter_.updateAndAnalyze(input2_);

  EXPECT_TRUE(result.new_input_);
  EXPECT_EQ(result.unique_count_, 2);
}

TEST_F(UniqueInputsCounterTest, DuplicatedInput) {
  unique_inputs_counter_.updateAndAnalyze(input1_);
  input2_.set_id("id-1");

  auto result = unique_inputs_counter_.updateAndAnalyze(input2_);

  EXPECT_TRUE(not result.new_input_);
  EXPECT_EQ(result.unique_count_, 1);
}

} // namespace cloud