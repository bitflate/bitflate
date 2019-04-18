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

    CAmount nPreviousSubsidy = nInitialSubsidy * 2; // for height == 0
    BOOST_CHECK_EQUAL(nPreviousSubsidy, nInitialSubsidy * 2);
    for (int nHalvings = 0; nHalvings < maxHalvings; nHalvings++) {
        int nHeight = nHalvings * consensusParams.nSubsidyHalvingInterval;
        CAmount nSubsidy = GetBlockSubsidy(nHeight, consensusParams);
        switch (nHalvings) {
            case 0: BOOST_CHECK_EQUAL(nSubsidy, nInitialSubsidy); break;
            case 1: BOOST_CHECK_EQUAL(nSubsidy, 3.5 * COIN); break;
            case 2: BOOST_CHECK_EQUAL(nSubsidy, 3.74 * COIN); break;
            case 3: BOOST_CHECK_EQUAL(nSubsidy, 4.01 * COIN); break;
            case 4: BOOST_CHECK_EQUAL(nSubsidy, 4.29 * COIN); break;
            case 5: BOOST_CHECK_EQUAL(nSubsidy, 4.59 * COIN); break;
            case 6: BOOST_CHECK_EQUAL(nSubsidy, 4.91 * COIN); break;
            case 7: BOOST_CHECK_EQUAL(nSubsidy, 5.25 * COIN); break;
            case 8: BOOST_CHECK_EQUAL(nSubsidy, 5.62 * COIN); break;
            case 9: BOOST_CHECK_EQUAL(nSubsidy, 6.01 * COIN); break;
            case 10: BOOST_CHECK_EQUAL(nSubsidy, 6.43 * COIN); break;
        }
        nPreviousSubsidy = nSubsidy;
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
    BOOST_CHECK_EQUAL(nSum, CAmount{89318249998810000});
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
