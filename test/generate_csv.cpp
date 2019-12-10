#include <iostream>
#include <cstdlib>

int main(int argc, char** argv)
{
   if (argc < 2)
   {
      std::cerr << "Syntax: " << argv[0] << " num_transactions\n";
   }
   long num_transactions = strtol(argv[1], nullptr, 10);
   int avg_price = 1000;
   int avg_quantity = 1000;
   for(long i = 0; i < num_transactions; ++i)
   {
      // will this be a buy or sell?
      bool buy = rand() % 2 == 0;
      // quantity?
      bool neg_qty = rand() % 2 == 0;
      int qty = 10 + (rand() % 10) * (neg_qty ? -1 : 1);
      // price?
      bool neg_price = rand() % 2 == 0;
      long price = avg_quantity + (rand() % 5 * (neg_price ? -1 : 1));
      std::cout << std::to_string(buy ? 1 : 2) << "," 
            << std::to_string(buy ? 2 : 1) << "," 
            << std::to_string(qty) << "," 
            << std::to_string(price) << '\n';
   }
}