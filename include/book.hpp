#include <set>
#include <asset.hpp>

/***
 * A representation of an order book
 */
template<class Size, class Price>
class Book
{
public:
   Book(const Asset buying, const Asset selling) : _wantToBuy(buying), _wantToSell(selling) {}
   std::map<Price, AssetOrder<Size, Price>> bids;
   std::map<Price, AssetOrder<Size, Price>> asks;
private:
   auto getBestOffer()
   {
      return bids.rbegin();
   }
   auto getBestAsk()
   {
      return asks.begin();
   }
public:
   /***
    * Add an order to the book
    * @param order the order
    * @returns true if there was at least one fill
    */
   bool AddOrder(const AssetOrder<Size, Price>& order)
   {
      AssetOrder<Size, Price> currOrder = order;
      // From the book's point of view, is this order buying what we're selling?
      bool buying = (order.assetToBuy == _wantToSell);
      if (buying)
      {
         auto bestAskItr = getBestAsk();
         while (bestAskItr != asks.end() && (*bestAskItr).second.price <= currOrder.price && currOrder.quantity > 0)
         {
            take(asks, (*bestAskItr).second, currOrder);
            bestAskItr = getBestAsk();
         }
         placeOnBook(currOrder);
      }
      else
      {
         auto bestOfferItr = getBestOffer();
         while ( bestOfferItr != bids.rend() && (*bestOfferItr).second.price >= currOrder.price && currOrder.quantity > 0)
         {
            take(bids, (*bestOfferItr).second, currOrder);
            bestOfferItr = getBestOffer();
         }
         // now deal with the leftover
         placeOnBook(currOrder);
      }
   }
private:
   Asset _wantToBuy;
   Asset _wantToSell;
   void take(std::map<Price, AssetOrder<Size, Price>>& collection, AssetOrder<Size, Price>& bookItem, AssetOrder<Size, Price>& incomingOrder)
   {
      if (bookItem.quantity > incomingOrder.quantity)
      {
         bookItem.quantity -= incomingOrder.quantity;
         incomingOrder.quantity = 0;
      }
      else
      {
         incomingOrder.quantity -= bookItem.quantity;
         bookItem.quantity = 0;
      }
      if (bookItem.quantity == 0)
      {
         collection.erase(bookItem.price);
      }      
   }
   void placeOnBook(AssetOrder<Size, Price>& order)
   {
      if (order.quantity > 0)
      {
         bool buying = (order.assetToBuy == _wantToSell);
         if (buying)
         {
            bids.insert({order.price, order});
         }
         else
         {
            asks.insert({order.price, order});
         }
      }
   }
};
