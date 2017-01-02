#include <gtest/gtest.h>
#include <cucumber-cpp/autodetect.hpp>

#include <vector>
#include <algorithm>

#include <boost/algorithm/string.hpp>


namespace
{
using cucumber::ScenarioScope;

    struct Context {
        int number_1{};
        int number_2{};
        int result{};
    };

    struct Context2 {
        std::vector<int> numbers;
        std::vector<int> results;
    };


    GIVEN("^the numbers (-?\\d+) and (-?\\d+)$") {
        REGEX_PARAM(int, number_1);
        REGEX_PARAM(int, number_2);
        ScenarioScope<Context> context;
        context->number_1 = number_1;
        context->number_2 = number_2;

    }

    GIVEN("^the following numbers:$") {
        ScenarioScope<Context2> context;
        TABLE_PARAM(calculator_params);
        const auto& number_table = calculator_params.hashes();

        for (const auto & table_row : number_table) {
            context->numbers.push_back(std::stoi(table_row.at("number")));
        }
    }


    struct TextContext {
        std::string text;
        unsigned word_count;
    };

    GIVEN("^the following text$") {
        REGEX_PARAM(std::string, text);
        ScenarioScope<TextContext> context;
        context->text = text;
    }


   WHEN("^this numbers are multiplied$") {
        ScenarioScope<Context> context;
        context->result = context->number_1 * context->number_2;
    }

    WHEN("^this numbers are added$") {
        ScenarioScope<Context> context;
        context->result = context->number_1 + context->number_2;
    }

    WHEN("^each number is multiplied by (-?\\d+)$") {
        REGEX_PARAM(int, multiplier);
        ScenarioScope<Context2> context;
        const auto number_container = context->numbers;
        auto& result_container = context->results;
        std::transform(std::begin(number_container),
        std::end(number_container),
        std::back_inserter(result_container),
        [&multiplier](int value) {return value * multiplier;});
    }


    unsigned word_count(const std::string& word, const std::string& phrase)
    {
        std::vector<std::string> strings;

        std::string lower_case_word;
        std::transform(word.cbegin(),
                       word.cend(),
                       std::back_inserter(lower_case_word),
                       [](const char& c) { return std::tolower(c);});

        std::string lower_case_phrase;
        std::transform(phrase.cbegin(),
                       phrase.cend(),
                       std::back_inserter(lower_case_phrase),
                       [](const char& c) { return std::tolower(c);});


        boost::split(strings, lower_case_phrase, boost::is_space());

        unsigned word_count{};
        for(auto& str : strings) {
            if (str.compare(lower_case_word) == 0) {
                word_count++;
            }
        }
        return word_count;
    }

    WHEN("^the word (.+) are counted in the text$") {
        REGEX_PARAM(std::string, word);
        ScenarioScope<TextContext> context;
        context->word_count = word_count(word, context->text);
    }


    THEN("^the result should be (-?\\d+)$") {
        REGEX_PARAM(int, result);
        ScenarioScope<Context> context;
        ASSERT_EQ(result , context->result);
    }

    THEN("^the results should be the following:$") {
        ScenarioScope<Context2> context;
        TABLE_PARAM(calculator_params);
        const auto &number_table = calculator_params.hashes();

        int result_index{};
        for (const auto &table_row : number_table) {
            ASSERT_EQ(std::stoi(table_row.at("result")), context->results.at(result_index));
            result_index++;
        }
    }

    THEN("^the count should be (\\d+)$") {
        REGEX_PARAM(unsigned, result);
        ScenarioScope<TextContext> context;
        ASSERT_EQ(result, context->word_count);
    }

}//namespace
