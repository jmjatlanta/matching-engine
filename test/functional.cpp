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

BOOST_AUTO_TEST_CASE( multiple_order_same_price )
{
   // Two assets
   Asset a1(1);
   Asset a2(2);

   Book<int, int> book(a1, a2);
   AssetOrder<int, int> order1(1, a2, a1, 10, 10);
   AssetOrder<int, int> order2(2, a2, a1, 10, 10);
   book.AddOrder(order2);
   book.AddOrder(order1);
   BOOST_TEST( book.bids.size() == 2);
   // Even though I added them in the wrong order, they should come out in the correct order
   auto bidItr = book.bids.begin();
   auto bidKey = (*bidItr).first;
   BOOST_TEST(bidKey.id == 1);
   // If I add one at a higher price, it should become the first
   AssetOrder<int, int> order3(3, a2, a1, 10, 11);
   book.AddOrder(order3);
   BOOST_TEST( (*book.bids.begin()).first.id == 3 );

   // now check the asks
   order1 = AssetOrder<int, int>(1, a1, a2, 10, 20);
   order2 = AssetOrder<int, int>(2, a1, a2, 10, 20);
   order3 = AssetOrder<int, int>(3, a1, a2, 10, 19);
   book.AddOrder(order2);
   book.AddOrder(order1);
   BOOST_TEST( book.asks.size() == 2);
   BOOST_TEST( (*book.asks.begin()).first.id == 1);
   book.AddOrder(order3);
   BOOST_TEST( (*book.asks.begin()).first.id == 3);
   
}