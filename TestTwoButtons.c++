// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "TwoButtons.h"

using namespace std;

// -----------
// TestTwoButtons
// -----------

// ----
// read
// ----

TEST(TwoButtonsFixture, read) {
    string s("1 10\n");
    const pair<int, int> p = twobuttons_read(s);
    ASSERT_EQ( 1, p.first);
    ASSERT_EQ(10, p.second);}

// ----
// eval
// ----

TEST(TwoButtonsFixture, eval_1) {
    const int v = twobuttons_eval(1, 10);
    ASSERT_EQ(6, v);}

TEST(TwoButtonsFixture, eval_2) {
    const int v = twobuttons_eval(10, 1);
    ASSERT_EQ(9, v);}

TEST(TwoButtonsFixture, eval_3) {
    const int v = twobuttons_eval(500, 501);
    ASSERT_EQ(251, v);}

TEST(TwoButtonsFixture, eval_4) {
    const int v = twobuttons_eval(501, 500);
    ASSERT_EQ(1, v);}

TEST(TwoButtonsFixture, eval_5) {
    const int v = twobuttons_eval(666, 6666);
    ASSERT_EQ(255, v);}

// -----
// print
// -----

// TEST(TwoButtonsFixture, print) {
//     ostringstream w;
//     twobuttons_print(w, 1, 10, 20);
//     ASSERT_EQ("1 10 20\n", w.str());}


