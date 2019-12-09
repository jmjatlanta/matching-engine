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
   // bids are sorted highest price first, then lowest id
   std::map<AssetBidKey<Price>, AssetOrder<Size, Price> > bids;
   // asks are sorted lowest price first, then lowest id
   std::map<AssetAskKey<Price>, AssetOrder<Size, Price>> asks;
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
         auto bestAskItr = asks.begin();
         while (bestAskItr != asks.end() && (*bestAskItr).second.price <= currOrder.price && currOrder.quantity > 0)
         {
            takeAsk( (*bestAskItr).second, currOrder);
            bestAskItr = asks.begin();
         }
         placeOnBook(currOrder);
      }
      else
      {
         auto bestOfferItr = bids.begin();
         while ( bestOfferItr != bids.end() && (*bestOfferItr).second.price >= currOrder.price && currOrder.quantity > 0)
         {
            takeBid( (*bestOfferItr).second, currOrder);
            bestOfferItr = bids.begin();
         }
         // now deal with the leftover
         placeOnBook(currOrder);
      }
   }
private:
   Asset _wantToBuy;
   Asset _wantToSell;
   void adjustQuantities(AssetOrder<Size, Price>& bookItem, AssetOrder<Size, Price>& incomingOrder)
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
   }
   void takeBid(AssetOrder<Size, Price>& bookItem, AssetOrder<Size, Price>& incomingOrder)
   {
      adjustQuantities(bookItem, incomingOrder);
      if (bookItem.quantity == 0)
         bids.erase(AssetBidKey<Price>(bookItem.id, bookItem.price));     
   }
   void takeAsk(AssetOrder<Size, Price>& bookItem, AssetOrder<Size, Price>& incomingOrder)
   {
      adjustQuantities(bookItem, incomingOrder);
      if (bookItem.quantity == 0)
         asks.erase(AssetAskKey<Price>(bookItem.id, bookItem.price));   
   }
   void placeOnBook(AssetOrder<Size, Price>& order)
   {
      if (order.quantity > 0)
      {
         bool buying = (order.assetToBuy == _wantToSell);
         if (buying)
         {
            bids.insert({AssetBidKey<Price>(order.id, order.price), order});
         }
         else
         {
            asks.insert({AssetAskKey<Price>(order.id, order.price), order});
         }
      }
   }
};
