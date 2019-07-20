Bitflate
=====================================

What is Bitflate?
----------------

Bitflate is a Bitcoin-based crypto currency. The project is in experimental stage.
The main differentiation of Bitflate is inflation.

The goal is to create a stable crypto currency, stable coin through inflation.

By adding inflation, we can:

- Prevent price from fluctuating wildly.
- Discourage HODL behavior, increase liquidity.

Bitflate is not a Store of Value.

Technical
-------

Bitflate is based on Bitcoin. It has the following differences:

- Proof of Work timespan adjustment is 3.5 days.
- Block time is 2.5 minutes. That means 1-year halving interval.
- For the first four halvings interval, block reward is like Bitcoin (50, 25, 12.5, 6.25). We give incentives to early adopters.
- In subsequent intervals, there's not more halving. Coins inflate 7% per year. At this inflation rate, coin supply doubles - every 10 years.
- You can review block reward code here:

https://github.com/bitflate/bitflate/blob/master/src/validation.cpp#L1007

- And here's the test for block reward:

https://github.com/bitflate/bitflate/blob/master/src/test/validation_tests.cpp#L25

- Block reward schedule:

  - 0: 50
  - 1: 25
  - 2: 12.5
  - 3: 6.25
  - 4: 6.45
  - 5: 6.90
  - 6: 7.39
  - 7: 7.91
  - 8: 8.46
  - 9: 9.05
  - 10: 9.68

FAQ
-------

#### Why do you want to have inflation?

Bitcoin has fixed supply. The currency is deflationary. It causes price to fluctuate wildly. We think it is a good Store of Value (SoV). But for transactions, price fluctuation is a problem.

Existing stable coins are typically implemented through bank ledger. This requires 3rd party centralized banks. We want to create a stable coin through inflation. We think inflation would add liquidity to Bitflate currency.

#### Why Bitflate inflation rate is 7%?

We take the reverse-Bitcoin approach of setting inflation rate fairly high. If we set the rate low, the currency may behave just like Bitcoin.

If this coin ever receives widespread adoption, high inflation can meet market demand.

We pick the rate of 7% from Rule 72. https://en.wikipedia.org/wiki/Rule_of_72

Coin supply doubles every 10 years.

#### What is Bitflate relationship with Bitcoin?

Bitflate started with Bitcoin Core codebase. It has changes in reward schedule and branding. Bitflate chain is separate chain and has no relationship with Bitcoin.

#### Can I use Bitflate for business?

Bitflate is at experimental stage as of July, 2019. We strongly advise you NOT to use it for business. The network is not secure.

License
-------

Bitflate is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Contact
-------

Email: dnprock@gmail.com

Twitter: https://twitter.com/DoPhuoc
