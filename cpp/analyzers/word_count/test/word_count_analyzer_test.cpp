#include "gtest/gtest.h"

#include "word_count_analyzer.h"


namespace cloud {

class WordCountAnalyzerTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    input.set_id("id");
    input.set_timestamp(1);
  }

  WordCountAnalyzer  word_count_analyzer;
  pb::AnalyzerInput  input;
  pb::AnalyzerOutput output;
};

TEST_F(WordCountAnalyzerTest, EmptyText) {
  auto status = word_count_analyzer.analyze(input, output);

  EXPECT_TRUE(status.ok());
  EXPECT_EQ(output.categories().size(), 0);
}

TEST_F(WordCountAnalyzerTest, OneWord) {
  input.set_text("word1");

  auto status = word_count_analyzer.analyze(input, output);

  EXPECT_TRUE(status.ok());
  EXPECT_EQ(output.categories().size(), 1);
  EXPECT_EQ(output.categories(0).name(), "word1");
  EXPECT_EQ(output.categories(0).score(), 1);
  EXPECT_EQ(output.categories(0).normed_score(), 1);
}

TEST_F(WordCountAnalyzerTest, OneWordWithSpaces) {
  input.set_text(" word1 ");

  auto status = word_count_analyzer.analyze(input, output);

  EXPECT_TRUE(status.ok());
  EXPECT_EQ(output.categories().size(), 1);
  EXPECT_EQ(output.categories(0).name(), "word1");
  EXPECT_EQ(output.categories(0).score(), 1);
  EXPECT_EQ(output.categories(0).normed_score(), 1);
}

TEST_F(WordCountAnalyzerTest, MultipleWord) {
  input.set_text(" word1  word2    word1  ");

  auto status = word_count_analyzer.analyze(input, output);

  EXPECT_TRUE(status.ok());
  EXPECT_EQ(output.categories().size(), 2);
  EXPECT_EQ(output.categories(0).name(), "word1");
  EXPECT_EQ(output.categories(0).score(), 2);
  EXPECT_EQ(output.categories(0).normed_score(), 2. / 3.);
  EXPECT_EQ(output.categories(1).name(), "word2");
  EXPECT_EQ(output.categories(1).score(), 1);
  EXPECT_EQ(output.categories(1).normed_score(), 1. / 3.);
}

} // namespace cloud
