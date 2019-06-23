// Created By: Rahil Agrawal
// Implementation of tests for GetPaths Function

/*

  == Explanation and rational of testing ==

  Test Case 1 : Ladder Length = 0
                End word is not reachable from the start word (They are both words in the lexicon)
                There are no ladders
                cat -> xyz is not reachable via any ladder of words in our lexicon

  Test Case 2 : Ladder Length = 2
                Test for correctness in getting the shortest ladder
                Start word is exactly one letter away from end word.
                There should be exactly one ladder.
                work -> pork
                Note that this ensures that another ladder of longer length will be discarded
                work -> fork -> pork

  Test Case 3 : Ladder Length > 2
                Test for equality of length of all ladders
                In accordance with Test Case 2, this test also ensures that they will all be
                of the shortest length.

  Test Case 4 : Ladder Length > 2
                Test for ladders being in alphabetical order

  - Cannot test "Press RETURN to quit" with empty string because the program exits with code 0

  - Initially, test cases were written to test words that are invalid with respect to the
    definition of valid input in the assignment specification. These are now commented out
    at the bottom of this file.
*/

#include "assignments/wl/word_ladder.h"
#include "catch.h"

std::unordered_set<std::string> lexicon = {"word", "ford", "form", "farm", "fard", "warm",
                                           "worm", "ward", "cat",  "cog",  "dog",  "cot",
                                           "dot",  "xyz",  "work", "pork", "fork"};

SCENARIO("Start word and end word are different but have no ladders") {
  GIVEN("Both words are in the lexicon") {
    auto start = "cat";
    auto end = "xyz";
    REQUIRE(lexicon.count(start) > 0);
    REQUIRE(lexicon.count(end) > 0);
    WHEN("Ladders are searched for") {
      auto paths = GetPaths(start, end, lexicon);
      THEN("Then there is no ladder") { REQUIRE(paths.size() == 0); }
    }
  }
}

SCENARIO("Start word is exactly one letter away from end word - Exactly one path of length 2") {
  GIVEN("Start word is work") {
    auto start = "work";
    REQUIRE(lexicon.count(start) > 0);
    AND_GIVEN("End word is pork") {
      auto end = "pork";
      REQUIRE(lexicon.count(end) > 0);
      WHEN("Ladders are searched for") {
        auto paths = GetPaths(start, end, lexicon);
        THEN("There is exactly one ladder") {
          REQUIRE(paths.size() == 1);
          AND_THEN("The ladder length is 2") {
            auto path = paths[0];
            REQUIRE(path.size() == 2);
            AND_THEN("The ladder is: awake aware") {
              REQUIRE(path[0].compare("work") == 0);
              REQUIRE(path[1].compare("pork") == 0);
            }
          }
        }
      }
    }
  }
}

SCENARIO("All ladders are of same length") {
  GIVEN("Start word is word") {
    auto start = "word";
    REQUIRE(lexicon.count(start) > 0);
    AND_GIVEN("End word is farm") {
      auto end = "farm";
      REQUIRE(lexicon.count(end) > 0);
      WHEN("Ladders are searched for") {
        auto paths = GetPaths(start, end, lexicon);
        THEN("There are 2 or more ladders") {
          REQUIRE(paths.size() >= 2);
          auto same_size = true;
          for (auto it = paths.begin() + 1; it != paths.end(); ++it)
            same_size = same_size && ((*it).size() == (*(it - 1)).size());
          AND_THEN("All ladders are the same size") { REQUIRE(same_size); }
        }
      }
    }
  }
}

SCENARIO("Ladders are in alphabetical order") {
  GIVEN("Start word is cat") {
    auto start = "cat";
    REQUIRE(lexicon.count(start) > 0);
    AND_GIVEN("End word is dog") {
      auto end = "dog";
      REQUIRE(lexicon.count(end) > 0);
      WHEN("Ladders are checked") {
        auto paths = GetPaths(start, end, lexicon);
        THEN("There are exactly 2 ladders") {
          REQUIRE(paths.size() == 2);
          AND_THEN("First ladder is : cat cot cog dog") {
            auto path = paths[0];
            REQUIRE(path[0].compare("cat") == 0);
            REQUIRE(path[1].compare("cot") == 0);
            REQUIRE(path[2].compare("cog") == 0);
            REQUIRE(path[3].compare("dog") == 0);
            AND_THEN("Second ladder is : cat cot dot dog") {
              path = paths[1];
              REQUIRE(path[0].compare("cat") == 0);
              REQUIRE(path[1].compare("cot") == 0);
              REQUIRE(path[2].compare("dot") == 0);
              REQUIRE(path[3].compare("dog") == 0);
            }
          }
        }
      }
    }
  }
}
/*
 * These test cases were written for edge cases involving invalid input.
 * The spec had since been changed to allow for input that only takes words from the lexicon
 * and does not allow for start and end word to be the same
 * The test cases have, hereby, been omitted.
 */
/*
SCENARIO("End word not in Lexicon") {
  GIVEN("Start word is in Lexicon but end word is not") {
    auto start = "word";
    auto end = "play";
    REQUIRE(lexicon.count(start) > 0);
    REQUIRE(lexicon.count(end) == 0);
    WHEN("Ladders are searched for") {
      auto paths = GetPaths(start, end, lexicon);
      THEN("Then there is no ladder") { REQUIRE(paths.size() == 0); }
    }
  }
}
SCENARIO("Start word not in Lexicon") {
  GIVEN("Start word is not in Lexicon but end word is") {
    auto start = "play";
    auto end = "word";
    REQUIRE(lexicon.count(end) > 0);
    REQUIRE(lexicon.count(start) == 0);
    WHEN("Ladders are searched for") {
      auto paths = GetPaths(start, end, lexicon);
      THEN("Then there is no ladder") { REQUIRE(paths.size() == 0); }
    }
  }
}
SCENARIO("Both words different and not in Lexicon") {
  GIVEN("Both words are not in lexicon") {
    auto start = "play";
    auto end = "work";
    REQUIRE(lexicon.count(start) == 0);
    REQUIRE(lexicon.count(end) == 0);
    WHEN("Ladders are searched for") {
      auto paths = GetPaths(start, end, lexicon);
      THEN("Then there is no ladder") { REQUIRE(paths.size() == 0); }
    }
  }
}
SCENARIO("Start word and end word are same") {
  GIVEN("The word is not included in the lexicon") {
    auto start = "play";
    auto end = start;
    REQUIRE(lexicon.count(start) == 0);
    WHEN("Ladders are searched for") {
      auto paths = GetPaths(start, end, lexicon);
      THEN("Then there is no ladder") { REQUIRE(paths.size() == 0); }
    }
  }
  GIVEN("The word is included in the lexicon") {
    auto start = "word";
    auto end = start;
    REQUIRE(lexicon.count(start) > 0);
    WHEN("Ladders are searched for") {
      auto paths = GetPaths(start, end, lexicon);
      THEN("Then there is one ladder") { REQUIRE(paths.size() == 1); }
      AND_THEN("The ladder contains one word") { REQUIRE(paths.front().size() == 1); }
      AND_THEN("The word is the starting word") {
        REQUIRE(paths.front().front().compare(start) == 0);
      }
    }
  }
}
*/
