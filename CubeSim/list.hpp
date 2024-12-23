

// CUBESIM - LIST


// Copyright (c) 2022 Bernhard Seifert
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sub-license, and / or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
// Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
// OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


// Includes
#include <map>
#include <string>


// Preprocessor Directives
#pragma once


// Namespace CubeSim
namespace CubeSim
{
   // Class List
   template <typename T> class List;
}


// Class List
template <typename T> class CubeSim::List
{
public:

   // Class Item
   class Item;

   // Constructor
   List(void);

   // Copy Constructor
   List(const List& list);

   // Destructor
   ~List(void);

   // Assign
   List& operator =(const List& list);

   // Clear
   void clear(void);

   // Clone and insert Item
   T& insert(const std::string& name, const T& item);

   // Get Item
   const std::map<std::string, T*>& item(void) const;
   T* item(const std::string& name) const;

protected:

   // Remove and destroy Item
   virtual void _remove(const T& item);

private:

   // Variables
   std::map<std::string, T*> _item;
};


// Class Item
template <typename T> class CubeSim::List<T>::Item
{
public:

   // Constructor
   Item(void);

   // Clone
   virtual T* clone(void) const;

   // Remove and destroy
   void remove(void);

private:

   // Clone
   T* _clone(std::true_type) const;
   T* _clone(std::false_type) const;

   // Variables
   List<T>* _list;

   // Friends
   friend List;
};


// Constructor
template <typename T> inline CubeSim::List<T>::List(void)
{
   // Check Type
   static_assert(std::is_base_of<Item, T>::value, "T must be derived from CubeSim::List::Item");
}


// Copy Constructor
template <typename T> inline CubeSim::List<T>::List(const List& list)
{
   // Assign List
   *this = list;
}


// Destructor
template <typename T> inline CubeSim::List<T>::~List(void)
{
   // Clear
   clear();
}


// Assign
template <typename T> CubeSim::List<T>& CubeSim::List<T>::operator =(const List& list)
{
   // Check List
   if (this != &list)
   {
      // Clear
      clear();

      // Parse List
      for (auto item = list._item.begin(); item != list._item.end(); ++item)
      {
         // Clone Item and set List
         T* item_ = item->second->clone();
         item_->_list = this;

         // Insert Item into List
         _item.insert(std::pair<std::string, T*>(item->first, item_));
      }
   }

   // Return Reference
   return *this;
}


// Clear
template <typename T> void CubeSim::List<T>::clear(void)
{
   // Parse List
   for (auto item = _item.begin(); item != _item.end(); ++item)
   {
      // Destroy Item
      delete item->second;
   }

   // Clear List
   _item.clear();
}


// Clone and insert Item
template <typename T> T& CubeSim::List<T>::insert(const std::string& name, const T& item)
{
   // Clone Item and set List
   T* item_ = item.clone();
   item_->_list = this;

   // Find Item
   auto pos = _item.find(name);

   // Check Position
   if (pos == _item.end())
   {
      // Insert Item into List
      _item.insert(std::pair<std::string, T*>(name, item_));
   }
   else
   {
      // Overwrite Item
      pos->second = item_;
   }

   // Return Item
   return *item_;
}


// Get Item List
template <typename T> inline const std::map<std::string, T*>& CubeSim::List<T>::item(void) const
{
   // Return Item List
   return _item;
}


// Get Item
template <typename T> inline T* CubeSim::List<T>::item(const std::string& name) const
{
   // Find Item
   auto item = _item.find(name);

   // Return Item
   return ((item == _item.end()) ? nullptr : item->second);
}


// Remove and destroy Item
template <typename T> void CubeSim::List<T>::_remove(const T& item)
{
   // Parse List
   for (auto item_ = _item.begin(); item_ != _item.end(); ++item_)
   {
      // Check Item
      if (item_->second == &item)
      {
         // Remove Item from List
         _item.erase(item_);

         // Destroy Item
         delete &item;

         // Return
         return;
      }
   }
}


// Constructor
template <typename T> inline CubeSim::List<T>::Item::Item(void) : _list()
{
}


// Clone
template <typename T> inline T* CubeSim::List<T>::Item::clone(void) const
{
   // Clone and return Object
   return _clone(std::is_abstract<T>());
}


// Remove and destroy
template <typename T> inline void CubeSim::List<T>::Item::remove(void)
{
   // Remove and destroy
   _list->_remove(dynamic_cast<T&>(*this));
}


// Clone (abstract Class)
template <typename T> inline T* CubeSim::List<T>::Item::_clone(std::true_type) const
{
   // Return
   return nullptr;
}


// Clone (non-abstract Class)
template <typename T> inline T* CubeSim::List<T>::Item::_clone(std::false_type) const
{
   // Clone and return Object
   return new T(dynamic_cast<const T&>(*this));
}
