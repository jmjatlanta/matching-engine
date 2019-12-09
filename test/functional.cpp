/***
 * Functional tests for the order book
 */
#define BOOST_TEST_MODULE orderbook
#include <boost/test/included/unit_test.hpp>

#include <book.hpp>

BOOST_AUTO_TEST_CASE( simple_tests )
{
   // two assets
   Asset asset1(1);
   Asset asset2(2);

   Book<int, double> book(asset1, asset2);
   // add something to the order book
   AssetOrder<int, double> order1(1, asset2, asset1, 10, 10);
   book.AddOrder(order1);
   BOOST_TEST( book.bids.size() == 1);
   BOOST_TEST( book.asks.size() == 0);
   // take half of the order
   AssetOrder<int, double> order2(2, asset1, asset2, 5, 10);
   book.AddOrder(order2);
   BOOST_TEST( book.bids.size() == 1);
   BOOST_TEST( book.asks.size() == 0);   
   // take the rest of the order
   AssetOrder<int, double> order3(2, asset1, asset2, 5, 10);
   book.AddOrder(order3);
   BOOST_TEST( book.bids.size() == 0);
   BOOST_TEST( book.asks.size() == 0);
   // now let 2 bids sit on the books and 1 big ask swallow them up
   order1 = AssetOrder<int, double>(1, asset2, asset1, 10, 10);
   book.AddOrder(order1);
   order2 = AssetOrder<int, double>(2, asset2, asset1, 10, 7.5);
   book.AddOrder(order2);
   order3 = AssetOrder<int, double>(3, asset1, asset2, 20, 7.5);
   book.AddOrder(order3);
   BOOST_TEST( book.bids.size() == 0);
   BOOST_TEST( book.asks.size() == 0);
}