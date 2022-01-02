

// FIBER 1.0.1


// Includes
#include "fiber.hpp"


// Constructor
Fiber::Fiber(Function function, void* data) : _done(false), _data(data), _function(function)
{
   // Check Main Fiber
   if (!_main)
   {
      // Convert Thread to Fiber
      _main = ConvertThreadToFiber(nullptr);

      // Check Address
      if (!_main)
      {
         // Exception
         throw Exception::Internal();
      }
   }

   // Create Fiber
   _address = CreateFiber(0, _dispatch, this);

   // Check Address
   if (!_address)
   {
      // Exception
      throw Exception::Internal();
   }
}


// Dispatcher
void CALLBACK Fiber::_dispatch(void* parameter)
{
   // Get Fiber
   Fiber& fiber = *reinterpret_cast<Fiber*>(parameter);

   // Call Function
   fiber._function(fiber._data);

   // Set Flag
   fiber._done = true;

   // Loop
   for (;;)
   {
      // Return to Main Fiber
      Fiber::suspend();
   }
}


// Variables
void* Fiber::_main = nullptr;
