/***
 * Performance tests for the order book
 */
#define BOOST_TEST_MODULE orderbook
#include <boost/test/included/unit_test.hpp>

#include <book.hpp>
#define CSV_IO_NO_THREAD
#include <csv.hpp>

void summarizeBook(const Book<int, int>& book)
{
   std::cout << "Number of bids: " << std::to_string(book.bids.size()) + "\n"
         << "Best bid: " << std::to_string( (*book.bids.begin()).second.price ) << "\n"
         << "Number of asks: " << std::to_string(book.asks.size() ) + "\n"
         << "Best ask: " << std::to_string( (*book.asks.begin()).second.price ) << "\n";
}

BOOST_AUTO_TEST_CASE( full_file )
{
   // csv file
   io::CSVReader<4> reader("test.csv");
   int a1, a2, qty, price;
   // book
   Asset asset1(1);
   Asset asset2(2);
   Book<int, int> book(asset1, asset2);
   int id = 0;
   while( reader.read_row(a1, a2, qty, price))
   {
      book.AddOrder(AssetOrder<int, int>(id++, Asset(a1), Asset(a2), qty, price));
   }
   summarizeBook(book);
}