/***
 * An overly-simplified representation of an asset
 */
class Asset
{
public:
   Asset(int id) : id(id) {}
   int id;
   inline bool operator==(const Asset& in) const
   {
      return in.id == id;
   }
};

template<class Price>
class AssetKey
{
public:
   AssetKey(int id, Price price) : id(id), price(price) {}
   int id;
   Price price;
};

/***
 * A way to sort orders first by high price, then by low id
 */
template<class Price>
class AssetBidKey : public AssetKey<Price>
{
public:
   using AssetKey<Price>::price;
   using AssetKey<Price>::id;
   AssetBidKey(int id, Price price) : AssetKey<Price>(id, price) {}
   inline bool operator<(const AssetKey<Price>& in) const
   {
      if (in.price == price)
         return id < in.id;
      return price > in.price;
   }
};

template<class Price>
class AssetAskKey : public AssetKey<Price>
{
public:
   using AssetKey<Price>::price;
   using AssetKey<Price>::id;
   AssetAskKey(int id, Price price) : AssetKey<Price>(id, price) {}
   inline bool operator<(const AssetKey<Price>& in) const
   {
      if (in.price == price)
         return id < in.id;
      return price < in.price;
   }
};



/***
 * An order that will be possibly stored on the order book.
 * Therefore, it must be sortable by price and ID
 */
template<class Quantity, class Price>
class AssetOrder
{
   public:
      AssetOrder() : id(0), assetToBuy(Asset(0)), assetToSell(Asset(0)), quantity(0), price(0) {}
      AssetOrder(int id, const Asset& toBuy, const Asset& toSell, Quantity qty, Price price) 
            : id(id), assetToBuy(toBuy), assetToSell(toSell), quantity(qty), price(price) {}
      AssetOrder& operator=(const AssetOrder& in)
      {
         id = in.id;
         assetToBuy = in.assetToBuy;
         assetToSell = in.assetToSell;
         quantity = in.quantity;
         price = in.price;
         return *this;
      }
      int id;
      Asset assetToBuy;
      Asset assetToSell;
      Quantity quantity;
      Price price;
};
