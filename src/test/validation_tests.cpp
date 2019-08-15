// Copyright (c) 2014-2019 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>
#include <net.h>
#include <validation.h>

#include <test/setup_common.h>

#include <boost/signals2/signal.hpp>
#include <boost/test/unit_test.hpp>

BOOST_FIXTURE_TEST_SUITE(validation_tests, TestingSetup)

static void TestBlockSubsidyHalvings(const Consensus::Params& consensusParams)
{
    int maxHalvings = 64;
    CAmount nInitialSubsidy = 50 * COIN;

    for (int nHalvings = 0; nHalvings < maxHalvings; nHalvings++) {
        int nHeight = nHalvings * consensusParams.nSubsidyHalvingInterval;
        CAmount nSubsidy = GetBlockSubsidy(nHeight, consensusParams);
        switch (nHalvings) {
            case 0: BOOST_CHECK_EQUAL(nSubsidy, nInitialSubsidy); break;
            case 1: BOOST_CHECK_EQUAL(nSubsidy, 25 * COIN); break;
            case 2: BOOST_CHECK_EQUAL(nSubsidy, round(12.5 * COIN)); break;
            case 3: BOOST_CHECK_EQUAL(nSubsidy, round(6.25 * COIN)); break;
            case 4: BOOST_CHECK_EQUAL(nSubsidy, round(6.56 * COIN)); break;
            case 5: BOOST_CHECK_EQUAL(nSubsidy, round(7.02 * COIN)); break;
            case 6: BOOST_CHECK_EQUAL(nSubsidy, round(7.51 * COIN)); break;
            case 7: BOOST_CHECK_EQUAL(nSubsidy, round(8.04 * COIN)); break;
            case 8: BOOST_CHECK_EQUAL(nSubsidy, round(8.6 * COIN)); break;
            case 9: BOOST_CHECK_EQUAL(nSubsidy, round(9.2 * COIN)); break;
            case 10: BOOST_CHECK_EQUAL(nSubsidy, round(9.85 * COIN)); break;
            case 11: BOOST_CHECK_EQUAL(nSubsidy, round(10.54 * COIN)); break;
            case 12: BOOST_CHECK_EQUAL(nSubsidy, round(11.28 * COIN)); break;
            case 13: BOOST_CHECK_EQUAL(nSubsidy, round(12.06 * COIN)); break;
            case 14: BOOST_CHECK_EQUAL(nSubsidy, round(12.91 * COIN)); break;
            case 15: BOOST_CHECK_EQUAL(nSubsidy, round(13.81 * COIN)); break;
            case 16: BOOST_CHECK_EQUAL(nSubsidy, round(14.78 * COIN)); break;
            case 17: BOOST_CHECK_EQUAL(nSubsidy, round(15.81 * COIN)); break;
            case 18: BOOST_CHECK_EQUAL(nSubsidy, round(16.92 * COIN)); break;
            case 19: BOOST_CHECK_EQUAL(nSubsidy, round(18.11 * COIN)); break;
            case 20: BOOST_CHECK_EQUAL(nSubsidy, round(19.37 * COIN)); break;
        }
    }
}

BOOST_AUTO_TEST_CASE(block_subsidy_test)
{
    const auto chainParams = CreateChainParams(CBaseChainParams::MAIN);
    TestBlockSubsidyHalvings(chainParams->GetConsensus()); // As in main
}

BOOST_AUTO_TEST_CASE(subsidy_limit_test)
{
    const auto chainParams = CreateChainParams(CBaseChainParams::MAIN);
    CAmount nSum = 0;
    for (int nHeight = 0; nHeight < 14000000; nHeight += 1000) {
        CAmount nSubsidy = GetBlockSubsidy(nHeight, chainParams->GetConsensus());
        nSum += nSubsidy * 1000;
        BOOST_CHECK(MoneyRange(nSum));
    }
    BOOST_CHECK_EQUAL(nSum, CAmount{136707550000000000});
}

static bool ReturnFalse() { return false; }
static bool ReturnTrue() { return true; }

BOOST_AUTO_TEST_CASE(test_combiner_all)
{
    boost::signals2::signal<bool (), CombinerAll> Test;
    BOOST_CHECK(Test());
    Test.connect(&ReturnFalse);
    BOOST_CHECK(!Test());
    Test.connect(&ReturnTrue);
    BOOST_CHECK(!Test());
    Test.disconnect(&ReturnFalse);
    BOOST_CHECK(Test());
    Test.disconnect(&ReturnTrue);
    BOOST_CHECK(Test());
}
BOOST_AUTO_TEST_SUITE_END()
